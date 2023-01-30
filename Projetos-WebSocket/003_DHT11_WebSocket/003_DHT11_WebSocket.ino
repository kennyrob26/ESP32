#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <DHT.h>
#include "index_html.h"

#define PINODHT 4
#define TIPODHT DHT11

//Credenciais do WI-FI
const char* ssid = "Valdirene";
const char* senha = "wifi@@@@";

float humidade;
float temperatura;
float humidadeAnterior;
float temperaturaAnterior;

//objeto DHT11
DHT dht(PINODHT, TIPODHT);

//Servidor HTTP e websocket
AsyncWebServer server(80);
AsyncWebSocket ws ("/ws");

//=========================//  SETUP   // =======================

void setup() {
  Serial.begin(115200);

  //inicia o DHT
  dht.begin();

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

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });
  
  server.begin();


}

//=========================//  LOOP  // =======================

void loop() {
  //Recebe a humidade e a temperatura do sensor DHT
  humidade = dht.readHumidity();
  temperatura = dht.readTemperature();
  
  //Os dois ifs a baixo atualizam respectivamente temperatura e humidade
  //Resumindo, se o estado da temperatura ou humidade alterar
  //eles serão atualizados individualmente
  if(temperaturaAnterior != temperatura){
    //t é o parâmetro que passamos na mensagem e representa a temperatura
    String mensagem = "t?" + String(temperatura); 
    notificaCliente(mensagem);
    temperaturaAnterior =temperatura;
  }

  if(humidadeAnterior != humidade){
    //h é o parâmetro que é passado pela mensagem que representa a humidade
    String mensagem = "h?" + String(humidade);
    notificaCliente(mensagem);
    humidadeAnterior = humidade;
  }
}

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

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len){
  switch (type) {
    case WS_EVT_CONNECT:
      //Assim que o cliente se conecta ele já é atualizado
      //A mensagem recebida pelo cliente será algo como t?00.00 ou h?00.00
      ws.text(client->id(), ("t?" + String(temperatura)));
      ws.text(client->id(), ("h?" + String(humidade)));
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

void initWebSocket(){
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}










