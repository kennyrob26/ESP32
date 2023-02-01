/*
 *Aqui está o nosso cliente, que nesse caso é um ESP8266
 *Nesse exemplo o nosso servidor nos envia ON ou OFF no intervalor de 1s
 *Ou seja, é algo como um blink
 *O que vamos fazer aqui é conectar ao wifi e ao servidor
 *E depois tratar a mensagem enviada pelo servidor
 *Nesse caso quando ON ligamos o led e quando OFF desligamos o led
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ArduinoWebsockets.h>

//Credenciais da rede
const char* ssid = "Valdirene"; 
const char* senha = "wifi@@@@";


const char* websockets_server_host    = "10.0.0.126"; //IP do servidor
const uint16_t websockets_server_port = 80; //porta do servidor

//Sem ele não conseguimos utilizar a classe WebsocketsClient
using namespace websockets;

//Definindo o objeto client da classe WebsocketsClient
WebsocketsClient client;

//GPIO do led
const int led = 2;

//========================= SETUP ===============================

void setup() {
  Serial.begin(115200);
  //Definindo led como saída
  pinMode(led, OUTPUT);

  //configurações do wifi
  WiFi.begin(ssid, senha);

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(1000);
  }

  Serial.println("Conectado ao WiFi, tentando conexão com o servidor");

  //Tentando conectar ao servidor
  bool connected = client.connect(websockets_server_host, websockets_server_port, "/ws");

  if(connected){
    Serial.println("Conectado ao servidor");
    client.send("Hello Server");
  }else{
    Serial.println("Não foi possível conectar ao servidor");
  }

  //Recepção das mensagens
  client.onMessage([&](WebsocketsMessage message){

    //Printa a mensagem no terminal
    Serial.print("Recebi a mensagem: ");
    Serial.println(message.data());

    //Se mensagem é "ON" led = HIGH
    //Se mensagem é "OFF" led = LOW
    if(message.data().equalsIgnoreCase("ON")){
      digitalWrite(led, HIGH);
    }else if(message.data().equalsIgnoreCase("OFF")){
      digitalWrite(led, LOW);
    }
  });

}

//========================= Loop  =============================================

void loop() {
  if(client.available()){
    client.poll();
    delay(1);
  }
}
