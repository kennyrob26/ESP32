#include <WiFi.h>
#include <WebServer.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>
#include "hPage.h"

#define NOME "Valdirene"
#define SENHA "wifi@@@@"

WebServer server(80);
void setup() {
  // put your setup code here, to run once:
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

  server.on("/home", HTTP_GET, homePage);

  server.onNotFound(onNotFound);

  server.begin();
  Serial.println("O servidor foi iniciado");
  

}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}

void homePage(){
  server.send(200, "text/html", hPage);
}

void onNotFound()
{
  server.send(404, "text/plain", "Not Found");    
}
