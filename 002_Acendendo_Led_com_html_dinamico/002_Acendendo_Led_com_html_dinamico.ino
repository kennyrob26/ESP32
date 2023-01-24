/*
 * Utilizando as bibliotecas AsyncTCP e ESPAsyncWebServer
 */

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "index_html.h"

//Credenciais do Wifi
const char*  ssid = "Valdirene";
const char*  password = "wifi@@@@";

//São os parâmetros da URL, que veremos mais a frente
const char* PARAM_INPUT_1 = "output";
const char* PARAM_INPUT_2 = "state";


//Criando o servidor na porta 80
AsyncWebServer server(80);
void setup() {
  Serial.begin(115200);
  //Definição dos pinos
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

  //Conectando a rede Wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println("Conectando ao wifi ... ");
  }

  //Exibe o ip fornecido pelo DHCP
  Serial.println(WiFi.localIP());

  //===================  Rotas  =========================================

  //processor é a funçao que gera conteúdo dinâmico em HTML
  server.on("/", HTTP_GET, [] (AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", index_html, processor);
  });

  /*
   * Basicamente funciona da seguinte forma, quando um botão é pressionado
   * ele "gera" um output e um state que será enviado via GET, 
   * o output é o pino do led (aqui é a GPIO2),
   * enquanto o state é o estado do led que pode ser 1 ou 2
   * Resumindo, a solicitação HTTP GET pode assumir dois estados:
   * 
   * LIGADO         /update?output=2&state=1
   * 
   * OU
   * 
   * DESLIGADO     /update?output=2&state=0
   */

   

  server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage1;
    String inputMessage2;
    //Verifica se existe algum parâmetro na requisição
    //E os converte para inteiro com o ".toInt"
    
    if(request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2))
    {
      inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
      inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
      digitalWrite(inputMessage1.toInt(), inputMessage2.toInt());
    }
    else
    {
      inputMessage1 = "No message";
      inputMessage2 = "No message";
     
    }
    //Apenas feedback no monitor
    Serial.print("GPIO: ");
    Serial.print(inputMessage1);
    Serial.print(" Nivel Lógico: ");
    Serial.println(inputMessage2);
    request->send(200, "text/plain", "OK");
  });
  
  

  //================= Inicia o Servidor ==========================
  server.begin();

}

void loop() {
  // put your main code here, to run repeatedly:

}

//====================  FUNÇÕES ==================================

String processor(const String& var){
  if(var == "CONTEUDO_DINAMICO"){
    String hello = "";
    hello += "<p> Olá </p>";
    hello += "<p><button id=\"acender\" onclick=\"acender()\" >ON</button></p>";
    hello += "<p><button id=\"apagar\" onclick=\"apagar()\" >OFF</button></p>";
    return hello;
  }
  return String();
}

//===========================================================================
