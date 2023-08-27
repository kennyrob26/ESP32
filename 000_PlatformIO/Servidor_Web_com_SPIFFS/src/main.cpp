
/*===================---Bibliotecas---=====================*/
#include <Arduino.h>
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

/*==============---Variáveis e constantes---===============*/

// Credenciais da rede WiFi
const char* rede  = "Valdirene";
const char* senha = "wifi@@@@"; 

// Definição das GPIOs
const int led = 2;
// Exibe o status do led na pagina
String statusLed;

// Instância o objeto server
AsyncWebServer server(80);

/*==================--atualizaStatus---====================*/

String atualizaStatus(const String& var)
{
  Serial.println(var);
  if(var == "ESTADO")
  {
    if(digitalRead(led))
    {
      statusLed = "ON";
    }/*end if*/
    else
    {
      statusLed = "OFF";
    }/*end else*/
  
    return statusLed;
  }
  return String();
}/*end function*/

/*======================---Setup---========================*/

void setup()
{
  Serial.begin(115200);
  
  //Definição de INPUT e OUTPUTS
  pinMode(led, OUTPUT);

  //Inicializando SPIFFS
  if(!SPIFFS.begin(true))
  {
    Serial.println("Ocorreu um erro na montagem do sistema de arquivos");
    return;
  }/*end if*/

  // Conectando ao WiFI
  WiFi.begin(rede, senha);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Conectando ao Wifi...");
  }/*end while*/

  //Exibe o IP que o ESP recebeu
  Serial.println(WiFi.localIP());

  //Definindo as rotas do Servidor Assincrono

  //Define a pagina inicial "/"
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, atualizaStatus);
  });

  //O html vai solicitar o css, então é necessário esse roteamento
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text.css");
  });

  //Liga o led
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(led, HIGH);
    request->send(SPIFFS, "/index.html", String(), false, atualizaStatus);
  });
  
  //Apaga o led
  server.on("/off", HTTP_GET, [] (AsyncWebServerRequest *request){
    digitalWrite(led, LOW);
    request->send(SPIFFS, "/index.html", String(), false, atualizaStatus);
  });

  //Inicia o servidor
  server.begin();

}

/*======================---Loop---========================*/

void loop() 
{
  //Sem conteúdo
}




