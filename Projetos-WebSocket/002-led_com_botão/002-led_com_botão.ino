#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "index_html.h"


//Credenciais da rede
const char* ssid = "Valdirene";
const char* password = "wifi@@@@";


bool ledStatus          = 0; //Se o led está em nivel alto ou baixo
bool ledStatusAnterior  = 1;
const int pinLed        = 2; //GPIO 2
const int botao         = 4; //GPIO 4
unsigned long tempo     = millis();


AsyncWebServer server(80);
AsyncWebSocket ws ("/ws");



//==========================  SETUP  ========================================



void setup() {
  Serial.begin(115200);

  //Configuração do led
  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed, LOW);

  //Configurações do botão
  pinMode(botao, INPUT);

//Configurações da conexão com o WI-FI 
 WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando..");
  }

  //Exibe o IP fornecido pelo DHCP
  Serial.println(WiFi.localIP());

  //Inicializa de fato o servidor Web SoCket
  initWebSocket();

  //A home page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  //Inicializa o servidor na porta 80
  server.begin();

}



//==========================  LOOP  ==========================================



void loop() {
  //A função cleanupClients() desconecta clientes antigos se o servidor ficar sobrecarregado
  ws.cleanupClients();
  //O estado do led varia conforme LedStatus também varia
  int pressionado = digitalRead(botao);

  //O tempo de 300 milis visa garantir que não haverá toques involuntários
  if(pressionado == 1 && ((millis() - tempo) >= 300)){
    ledStatus = !ledStatus;
    tempo = millis();
  }

  if(ledStatusAnterior != ledStatus){
    notificaClientes();
    ledStatusAnterior = ledStatus;
  }

  digitalWrite(pinLed, ledStatus); 

}



//==========================  Funções ========================================



//Função responsável por notificar todos os clientes
void notificaClientes(){
  ws.textAll(String(ledStatus));
}

//Trata as menagens que chegam ao servidor
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len){

  //Verifica a integridade dos dados
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT){
    data[len] = 0;

    //Resumindo, se existe uma mensagem "pressionou" o led troca de estado
    if (strcmp((char*)data, "pressionou") == 0){
      ledStatus = !ledStatus;
      //notificaClientes();
    }
  }
}

//É quem escuta o cliente e recebe os eventos, ele executa alguma ação dependendo do tipo de evento
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len){
  switch (type){
    case WS_EVT_CONNECT:
      //Adicionei essa linha para atualizar o estado assim que o cliente conectar
      ws.text(client->id(), String(ledStatus));
      Serial.printf("O cliente #%u se conectou, seu IP é: %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("O cliente #%u desconectou\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

//A função que inicia o nosso webSocket
void initWebSocket(){
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}
























