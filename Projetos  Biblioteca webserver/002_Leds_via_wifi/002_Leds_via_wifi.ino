/*
 * Conectando ESP 32 a internet
 * Os metodos são os mesmos utilizados no esp826 o que muda são as bibliotecas
 */

#include <WiFi.h>
#include <WebServer.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>
#include "hPage.h"

#define NOME "Valdirene"
#define SENHA "wifi@@@@"
#define LED1 2
#define LED2 4
#define LED3 16
#define LED4 17
#define LED5 5
#define LED6 18

WebServer server(80);

//=================== SETUP ====================================


void setup() {
  //================= Definição dos Pinos ======================
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);

  //================= Configurações do WiFi =====================
  
  Serial.begin(115200);
  WiFi.begin(NOME, SENHA);
  Serial.print("Conectando");
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  
  //Configuração do IP fixo, deve ser congigurado com base na rede utilizada
  IPAddress ip(10, 0, 0, 125);
  IPAddress gateway(10, 0, 0, 1);
  IPAddress subnet(255, 255, 255, 0);
  Serial.print("Configurando IP fixo para: ");
  Serial.println(ip);

  //enviamos todas as informações que configuramos
  WiFi.config(ip, gateway, subnet);

  //Feedback
  Serial.println("");
  Serial.println("Connectado");
  Serial.print ("IP: ");
  Serial.println(WiFi.localIP());

  //=================== Páginas =========================

  //Página inicial
  server.on("/home", HTTP_GET, homePage);

  //Endereço para acender cada um dos leds
  server.on("/led1oN", HTTP_GET, acendeLed1);
  server.on("/led2oN", HTTP_GET, acendeLed2);
  server.on("/led3oN", HTTP_GET, acendeLed3);
  server.on("/led4oN", HTTP_GET, acendeLed4);
  server.on("/led5oN", HTTP_GET, acendeLed5);
  server.on("/led6oN", HTTP_GET, acendeLed6);

  server.on("/led1oFF", HTTP_GET, apagaLed1);
  server.on("/led2oFF", HTTP_GET, apagaLed2);
  server.on("/led3oFF", HTTP_GET, apagaLed3);
  server.on("/led4oFF", HTTP_GET, apagaLed4);
  server.on("/led5oFF", HTTP_GET, apagaLed5);
  server.on("/led6oFF", HTTP_GET, apagaLed6);


  //Página não existe
  server.onNotFound(onNotFound);

  //Iniciando o servidor
  server.begin();
  Serial.println("O servidor foi iniciado");
  

}

//======================= LOOP ==========================

void loop() {
  // put your main code here, to run repeatedly:
  //Responde as requisições do usuário
  server.handleClient();
}

//=============== Funções das Requisições ===============

void homePage(){
  server.send(200, "text/html", hPage);
}

//Acende LED

void acendeLed1(){
  digitalWrite(LED1, HIGH);
}

void acendeLed2(){
  digitalWrite(LED2, HIGH);
}

void acendeLed3(){
  digitalWrite(LED3, HIGH);
}

void acendeLed4(){
  digitalWrite(LED4, HIGH);
}
void acendeLed5(){
  digitalWrite(LED5, HIGH);
}
void acendeLed6(){
  digitalWrite(LED6, HIGH);
}

//Apaga os leds

void apagaLed1(){
  digitalWrite(LED1, LOW);
}

void apagaLed2(){
  digitalWrite(LED2, LOW);
}

void apagaLed3(){
  digitalWrite(LED3, LOW);
}

void apagaLed4(){
  digitalWrite(LED4, LOW);
}
void apagaLed5(){
  digitalWrite(LED5, LOW);
}
void apagaLed6(){
  digitalWrite(LED6, LOW);
}
void onNotFound()
{
  server.send(404, "text/plain", "Not Found");    
}
