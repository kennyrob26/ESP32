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
#define POT 35
int leitura = 0;

WebServer server(80);

//=================== SETUP ====================================


void setup() {
  //================= Definição dos Pinos ======================

  //Sem pinos a definir

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
  server.on("/leitura", HTTP_GET, leituraPot);

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

//Faz a leitura do potenciometro

void leituraPot(){
  //Lê o pino
  int p = (analogRead(POT));
  //Cria um json que será enviado para a página "ip/leitura"
  String json = "{\"leitura\":"+String(p)+"}";
  server.send(200, "application/json", json);
}
void onNotFound()
{
  server.send(404, "text/plain", "Not Found");    
}
