#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include "index_html.h"

const char* ssid  = "Valdirene";
const char* senha = "wifi@@@@";

const int led = 2;
bool ledStatus = 0;

//É a porta e o caminho que vamos inserir no cliente
AsyncWebServer server(80);
AsyncWebSocket ws ("/ws");

//===================== SETUP ========================================

void setup() {
  Serial.begin(115200);

  //Configuração do led
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  //Configurações do WiFi
  WiFi.begin(ssid, senha);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Conectando...");
  }

  Serial.println(WiFi.localIP());

  //Inicia o servidor websocket
  initWebSocket();

  //Páginas
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  //Inicia o servidor HTTP
  server.begin();


}

void loop() {
  ws.cleanupClients();

  digitalWrite(led, ledStatus);


}

//responsável pelo envio das mensagens para todos os clientes
void notificaClientes(String mensagem){
  ws.textAll(mensagem);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len){

  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if(info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT){
    data[len] = 0;

    if(strcmp((char*)data, "ON") == 0){
      ledStatus = 1;
      notificaClientes("movimento");
    }else if(strcmp((char*)data, "OFF") == 0){
      ledStatus = 0;
      notificaClientes("!movimento");
    }
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len){
  switch (type) {
    case WS_EVT_CONNECT:
      ws.text(client->id(), "!movimento");
      Serial.printf("Cliente #%u se conectou, seu IP é %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("O cliente #%d se desconectou \n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void initWebSocket(){
  ws.onEvent(onEvent);
  server.addHandler(&ws);  
}

























