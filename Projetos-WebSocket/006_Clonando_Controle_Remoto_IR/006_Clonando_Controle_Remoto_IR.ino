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

//============================ Códigos Raw de cada tecla clonada ================================

//onOff
uint16_t       onOff[67] = {9120, 4418,  632, 518,  612, 518,  612, 1638,  612, 520,  612, 
                            518,  614, 516,  612, 520,  612, 518,  612, 1638,  586, 1662,  
                            586, 544,  612, 1638,  610, 1638,  610, 1638,  610, 1640,  610, 
                            1638,  612, 520,  612, 518,  612, 518,  614, 1636,  584, 546,  
                            612, 518,  614, 518,  614, 518,  612, 1638,  610, 1638,  610, 
                            1638,  610, 520,  614, 1636,  610, 1638,  586, 1666,  608, 1640,  
                            612};

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

//mute
uint16_t        mute[71] = {9108, 4390,  634, 496,  662, 466,  664, 1584,  664, 466,  666, 
                            466,  664, 468,  690, 440,  664, 466,  664, 1584,  666, 1586,  
                            662, 466,  664, 1586,  664, 1584,  662, 1588,  662, 1584,  666, 
                            1584,  664, 1586,  664, 466,  664, 466,  666, 1584,  664, 466,  
                            664, 468,  662, 468,  662, 468,  664, 466,  664, 1584,  664, 1586,  
                            664, 468,  662, 1586,  664, 1584,  664, 1584,  690, 1560,  664, 
                            39782,  9112, 2154,  634};

//menu
uint16_t        menu[67] = { 9106, 4396, 632, 498, 658, 472, 660, 1588, 664, 468, 688, 
                            444, 660, 470, 660, 470, 660, 470, 660, 1590, 660, 1590, 662, 
                            468, 662, 1588, 662, 1588, 660, 1590, 660, 1586, 662, 1588, 
                            662, 470, 660, 470, 660, 1590, 662, 1588, 662, 1588, 660, 1588, 
                            662, 1588, 660, 472, 660, 1588, 662, 1588, 660, 472, 660, 470, 
                            664, 468, 664, 470, 660, 470, 660, 1588, 662 };

//input
uint16_t       input[71] = {9110, 4390,  664, 466,  664, 468,  664, 1584,  664, 468,  666, 
                            466,  690, 440,  664, 466,  664, 466,  664, 1588,  662, 1588,  
                            662, 468,  686, 1562,  664, 1588,  662, 1586,  666, 1584,  666, 
                            1586,  664, 1586,  664, 1586,  664, 466,  664, 1586,  664, 466,  
                            664, 466,  664, 466,  664, 466,  666, 464,  666, 466,  664, 
                            1586,  664, 466,  664, 1586,  666, 1584,  666, 1582,  664, 1586,  
                            664, 39784,  9114, 2150,  664};

//avançar canal
uint16_t         cmais[71] = {9110, 4388,  636, 494,  662, 468,  664, 1586,  664, 466,  664, 
                            466,  666, 466,  662, 468,  662, 468,  664, 1586,  664, 1586,  
                            660, 468,  662, 1588,  662, 1584,  664, 1584,  666, 1586,  664, 
                            1584,  664, 468,  664, 466,  690, 440,  690, 440,  666, 466,  
                            664, 468,  664, 464,  666, 466,  666, 1584,  664, 1586,  664, 
                            1586,  662, 1586,  664, 1584,  664, 1586,  664, 1584,  664, 
                            1584,  666, 39778,  9108, 2154,  634};

//Voltar canal
uint16_t         cmenos[71] = {9106, 4390,  636, 496,  662, 466,  664, 1584,  664, 466,  
                            666, 468,  662, 468,  690, 440,  664, 466,  664, 1584,  666, 
                            1586,  664, 466,  664, 1586,  662, 1586,  664, 1586,  664, 
                            1584,  664, 1584,  664, 1586,  664, 468,  664, 468,  662, 468,  
                            664, 468,  664, 466,  690, 442,  664, 466,  664, 466,  664, 
                            1584,  664, 1586,  664, 1584,  664, 1586,  664, 1586,  664, 
                            1586,  664, 1586,  662, 39740,  9136, 2126,  636};

//Seta cima
uint16_t           cima[71] = {9110, 4388,  662, 468,  664, 468,  666, 1584,  640, 492,  
                              664, 466,  664, 468,  662, 466,  666, 466,  666, 1584,  664, 
                              1586,  664, 466,  664, 1584,  664, 1586,  664, 1586,  662, 
                              1586,  664, 1588,  662, 468,  664, 468,  664, 466,  664, 466,  
                              664, 468,  664, 466,  664, 1586,  662, 468,  664, 1584,  666, 
                              1586,  664, 1584,  664, 1586,  664, 1584,  664, 1586,  664, 466,  
                              664, 1584,  666, 39782,  9112, 2152,  634};

//seta esquerda
uint16_t       esquerda[71] = {9112, 4390,  634, 498,  662, 466,  690, 1558,  664, 466,  
                              716, 418,  664, 466,  662, 466,  664, 466,  664, 1584,  664, 
                              1584,  690, 442,  664, 1586,  664, 1584,  664, 1586,  664, 
                              1586,  666, 1584,  664, 1586,  666, 1582,  690, 1562,  664, 
                              466,  664, 466,  664, 466,  688, 442,  666, 466,  664, 468,  
                              664, 466,  664, 466,  664, 1584,  666, 1584,  664, 1586,  
                              688, 1558,  664, 1586,  664, 39784,  9110, 2152,  664};    

//seta baixo
uint16_t          baixo[67] = {9112, 4390,  662, 466,  664, 468,  666, 1584,  666, 466,  666, 
                              466,  666, 466,  664, 466,  664, 468,  662, 1584,  664, 1586,  
                              664, 468,  662, 1586,  664, 1586,  666, 1582,  664, 1586,  664, 
                              1586,  664, 1584,  664, 466,  664, 466,  664, 466,  664, 466,  
                              666, 466,  664, 1584,  664, 466,  666, 468,  662, 1584,  664, 
                              1586,  664, 1586,  664, 1586,  664, 1586,  666, 466,  664, 1586,  
                              664};

//seta direita
uint16_t        direita[71] = {9110, 4392,  660, 468,  662, 466,  664, 1586,  664, 466,  664, 
                              466,  664, 466,  664, 468,  664, 466,  664, 1584,  664, 1586,  
                              664, 466,  664, 1586,  664, 1584,  664, 1586,  664, 1584,  664, 
                              1586,  664, 468,  664, 1584,  664, 1584,  666, 466,  664, 466,  
                              664, 468,  666, 464,  666, 464,  666, 1584,  664, 466,  668, 
                              464,  664, 1586,  664, 1584,  666, 1584,  664, 1586,  662, 1586,  
                              664, 39744,  9112, 2150,  636};
            
//ok
uint16_t             ok[71] = {9114, 4390,  744, 386,  662, 468,  664, 1584,  664, 466,  664, 
                              466,  666, 468,  662, 468,  662, 470,  662, 1586,  662, 1586,  
                              664, 466,  666, 1586,  690, 1560,  664, 1584,  664, 1586,  664, 
                              1584,  690, 440,  666, 466,  664, 1584,  664, 466,  664, 468,  
                              664, 466,  666, 1586,  662, 468,  664, 1584,  664, 1586,  662, 
                              468,  664, 1586,  664, 1584,  662, 1586,  664, 468,  664, 1586,  
                              662, 39748,  9112, 2152,  634};

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

    if (strcmp((char *)data, "onOff") == 0) 
    {
      irsend.sendRaw(onOff, 67, 38);
      Serial.println("onOff");
    }
    else if (strcmp((char *)data, "input") == 0) 
    {
      irsend.sendRaw(input, 71, 38);
      Serial.println("input");
    } 
    else if (strcmp((char *)data, "vmais") == 0) 
    {
      irsend.sendRaw(volumenMais, 71, 38);
      Serial.println("vmais");
    } 
    else if (strcmp((char *)data, "vmenos") == 0)
    {
      irsend.sendRaw(volumeMenos, 67, 38);
      Serial.println("vmenos");
    }
    else if (strcmp((char *)data, "cmais") == 0) 
    {
      irsend.sendRaw(cmais, 71, 38);
      Serial.println("cmais");
    }
    else if (strcmp((char *)data, "cmenos") == 0) 
    {
      irsend.sendRaw(cmenos, 71, 38);
      Serial.println("cmenos");
    }
    else if (strcmp((char *)data, "menu") == 0)
    {
      irsend.sendRaw(menu, 67, 38);
      Serial.println("menu");
    }
    else if (strcmp((char *)data, "cima") == 0) 
    {
      irsend.sendRaw(cima, 71, 38);
      Serial.println("cima");
    }
    else if (strcmp((char *)data, "esquerda") == 0) 
    {
      irsend.sendRaw(esquerda, 71, 38);
      Serial.println("esquerda");
    }
    else if (strcmp((char *)data, "baixo") == 0) 
    {
      irsend.sendRaw(baixo, 67, 38);
      Serial.println("baixo");
    }
    else if (strcmp((char *)data, "direita") == 0) 
    {
      irsend.sendRaw(direita, 71, 38);
      Serial.println("direita");
    }
    else if (strcmp((char *)data, "mute") == 0) 
    {
      irsend.sendRaw(mute, 71, 38);
      Serial.println("mute");
    }
    else if (strcmp((char *)data, "ok") == 0) 
    {
      irsend.sendRaw(ok, 71, 38);
      Serial.println("ok");
    }
    else{
      Serial.println("desconhecido");
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
