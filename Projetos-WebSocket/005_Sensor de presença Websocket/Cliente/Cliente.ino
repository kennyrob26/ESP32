#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ArduinoWebsockets.h>

const char* ssid = "Valdirene";
const char* senha = "wifi@@@@";

const char* websockets_server_host  = "10.0.0.126";
const uint16_t websockets_server_port = 80;

//namespace da classe WebsocketsClient
using namespace websockets;
//Defininfo o objeto client da classe WebsocketsClient
WebsocketsClient client;

//GPIO2 recebe o sensor de presença
const int sensorPresenca = 2;
bool movimento = 0;
bool movimentoAnterior = 1;

void setup() {
  Serial.begin(115200);
  pinMode(sensorPresenca, INPUT);

  WiFi.begin(ssid, senha);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print("Conectando...");
    delay(1000);
  }

  Serial.println("Conexão estabelecida com o WiFi");
  Serial.println("Tentando conectar ao servidor Websocket");

  bool connected = client.connect(websockets_server_host, websockets_server_port, "/ws");

  if(connected){
    Serial.println("Conectado ao WebSocket");
    client.send("OFF");
  }else{
    Serial.println("Não foi possível conectar ao servidor");
  }

  client.onMessage([&](WebsocketsMessage mensagem){
    Serial.print("Recebi a mensagem: ");
    Serial.println(mensagem.data());
  });

}

void loop() {
  if(client.available()){
    client.poll();
    delay(1);
  }

  movimento = digitalRead(sensorPresenca);

  if(movimentoAnterior != movimento){
    if(movimento == 1){
      client.send("ON");
    }else if(movimento == 0){
      client.send("OFF");
    }
    movimentoAnterior = movimento;
  }



}













