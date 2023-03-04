#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "index_html.h"

#include <Arduino.h>
//IRremote é a bibliteca resposável por enviar e receber comandos via IR
#include <IRremoteESP8266.h>
//IRsend é o "módulo" que envia dados
#include <IRsend.h>



//Credenciais da rede
const char *ssid = "Valdirene";
const char *password = "wifi@@@@";


const uint16_t kIrLed = 4;  //Led IR está na GPIO 4
IRsend irsend(kIrLed);

//Códigos Raw de cada tecla clonada

//Volume mais
uint16_t volumenMais[71] = { 9130, 4372, 630, 500, 658, 470, 660, 1590, 664, 466,
                             662, 468, 662, 470, 664, 468, 662, 470, 662, 1588, 664,
                             1586, 662, 468, 664, 1586, 662, 1588, 664, 1586, 662,
                             1590, 660, 1588, 662, 470, 660, 1588, 662, 470, 662,
                             470, 660, 470, 662, 470, 662, 468, 662, 468, 662, 1588,
                             662, 470, 664, 1586, 664, 1586, 662, 1586, 662, 1588, 660,
                             1590, 662, 1588, 664, 39754, 9108, 2160, 630 };

//Volume menos
uint16_t volumeMenos[67] = { 9108, 4396, 632, 492, 664, 466, 638, 1612, 638, 494, 638,
                             492, 640, 490, 640, 492, 662, 468, 638, 1612, 638, 1610, 
                             662, 468, 640, 1610, 664, 1586, 640, 1612, 660, 1588, 638, 
                             1612, 640, 1612, 636, 1612, 664, 468, 638, 492, 662, 470, 
                             638, 494, 640, 492, 662, 470, 638, 492, 638, 494, 662, 1588, 
                             638, 1612, 638, 1612, 664, 1588, 638, 1612, 638, 1610, 640 };

//menu
uint16_t        menu[67] = { 9106, 4396, 632, 498, 658, 472, 660, 1588, 664, 468, 688, 
                            444, 660, 470, 660, 470, 660, 470, 660, 1590, 660, 1590, 662, 
                            468, 662, 1588, 662, 1588, 660, 1590, 660, 1586, 662, 1588, 
                            662, 470, 660, 470, 660, 1590, 662, 1588, 662, 1588, 660, 1588, 
                            662, 1588, 660, 472, 660, 1588, 662, 1588, 660, 472, 660, 470, 
                            664, 468, 664, 470, 660, 470, 660, 1588, 662 };


//Inicia o Servidor http e websocket
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");



//==========================  SETUP  ========================================



void setup() {

  Serial.begin(115200, SERIAL_8N1);

  irsend.begin();


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
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", index_html);
  });

  //Inicializa o servidor na porta 80
  server.begin();
}



//==========================  LOOP  ==========================================



void loop() {
  //A função cleanupClients() desconecta clientes antigos se o servidor ficar sobrecarregado
  ws.cleanupClients();
}



//==========================  Funções ========================================



//Função responsável por notificar todos os clientes

//Trata as menagens que chegam ao servidor
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {

  //Verifica a integridade dos dados
  AwsFrameInfo *info = (AwsFrameInfo *)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;

    irsend.sendNEC(0x00FFE01FUL);
    Serial.print("Comando recebido: ");

    //Verifica se data corresponde a um comnado esperado


    if (strcmp((char *)data, "vmais") == 0) 
    {
      irsend.sendRaw(volumenMais, 71, 38);
      Serial.println("vmais");
    } 
    else if (strcmp((char *)data, "vmenos") == 0)
    {
      irsend.sendRaw(volumeMenos, 67, 38);
      Serial.println("vmenos");
    }
    else if (strcmp((char *)data, "menu") == 0)
    {
      irsend.sendRaw(menu, 67, 38);
      Serial.println("menu");
    }
  }
}

//É quem escuta o cliente e recebe os eventos, ele executa alguma ação dependendo do tipo de evento
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      //Apenas exibe informações do cliente que se conectou
      Serial.printf("O cliente #%u se conectou, seu IP é: %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("O cliente #%u desconectou\n", client->id());
      break;
    case WS_EVT_DATA:
      //chama a função abaixo sempre que recebe uma nova mensagem
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

//A função que inicia o nosso webSocket
void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}
