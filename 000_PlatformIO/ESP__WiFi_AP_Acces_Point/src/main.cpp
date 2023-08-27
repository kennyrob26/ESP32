/*===================--- Bibliotecas ---=======================*/

#include <Arduino.h>
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

/*=============--- Variáveis e constantes ---==================*/

//Definindo credenciais do ponto de acesso ESP32

const char* nome   = "ESP32_AP";
const char* senha  = "12345678";

//GPIOs utilizadas
const int led = 2;

//Definindo um servidor na porta 80
AsyncWebServer server(80);

/*======================--- Setup ---==========================*/

void setup() 
{
  Serial.begin(115200);

  //Montando sistema de arquivos SPIFFS
  if(!SPIFFS.begin(true))
  {
    Serial.println("ERRO! Não foi possível montar o sistema de arquivos.");
    return;
  }/*end if*/

  //Definição dos INPUTS e OUTPUTS
  pinMode(led, OUTPUT);

  //Definindo os parâmetros do AP, a senha não é obrigatória
  Serial.println("Definindo AP");
  WiFi.softAP(nome, senha);

  //Verifica o IP do ESP, e imprime no terminal
  IPAddress IP = WiFi.softAPIP();
  Serial.print("O IP do AP é: ");
  Serial.println(IP);

  //Abrindo a página inicial do ESP32
  server.on("/", HTTP_GET, [] (AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false);
  });


  server.begin();

}/*end setup*/

void loop() 
{

}

