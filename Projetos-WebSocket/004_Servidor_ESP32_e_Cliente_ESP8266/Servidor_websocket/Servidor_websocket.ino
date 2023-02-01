/*
 * É o nosso servidor web socket, ele é extremamente simples, apenas envia ON e OFF no intervalo de 1S,
 * e o nosso cliente vai tratar a mensagem da maneira que desejar
 */

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>

//Credenciais do WI-FI
const char* ssid = "Valdirene";
const char* senha = "wifi@@@@";

unsigned long tempo     = millis();




//Esses dois dados são muito importantes para a configuração do cliente
//80 é a porta que vamos adicionar no código do cliente
//e /ws é o caminho do servidor websocket, ou seja, ATENCAO ele não está no caminho / e sim /ws
AsyncWebServer server(80);
AsyncWebSocket ws ("/ws");

//=========================//  SETUP   // =======================

void setup() {
  Serial.begin(115200);



  //Conectando ao Wi-Fi
  WiFi.begin(ssid, senha);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando..");
  }

  //Exibe o IP fornecido pelo DHCP
  Serial.println(WiFi.localIP());

  //Inicializa de fato o servidor Web SoCket
  initWebSocket();
  
  server.begin();


}

//=========================//  LOOP  // =======================

void loop() {
  
  //Como estamos trabalhando com a biblioteca de servidor assincrono, é sempre bom evitar delays
  //Muito simples, se o tempo estiver em 0 segundos enviamos ON
  //se o tempo for igual a 1 segundo enviamos OFF
  //Quando o tempo chega a 2 segundos resetamos o tempo
  if((millis() - tempo) == 0){
    notificaCliente("ON");
  }else if((millis() - tempo) == 1000){
    notificaCliente("OFF");

  }else if((millis() - tempo) == 2000){
    tempo = millis();
  }


}

//Função responsável por enviar as mensagens ao servidor
void notificaCliente(String mensagem){
  ws.textAll(mensagem);
}
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len){

  //Verifica a integridade dos dados
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT){
    data[len] = 0;
  }
}

//É a callback dos eventos, de acordo com o tipo de evento "toma uma decisão"
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len){
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("O cliente #%u se conectou, seu IP é: %s\n", client->id(), client->remoteIP().toString().c_str());
      break; 
    case WS_EVT_DISCONNECT:
      Serial.printf("O cliente #%u desconectou\n", client->id());
      break;
    case WS_EVT_DATA:
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

//Inicia o nosso websocket chamando oNEvent e addHandler
void initWebSocket(){
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}










