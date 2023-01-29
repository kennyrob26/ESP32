#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "index_html.h"

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

  //Rotas
  server.on("/", HTTP_GET, [] (AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", index_html);
  });

  server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage1;
    String inputMessage2;

    if(request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)){
      inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
      inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
      digitalWrite(inputMessage1.toInt(), inputMessage2.toInt());
    }else{
      inputMessage1 = "No message";
      inputMessage2 = "No message";
    }
    Serial.print("GPIO: ");
    Serial.print(inputMessage1);
    Serial.print(" - Set to: ");
    Serial.println(inputMessage2);
    request->send(200, "text/plain", "OK");
  });

  server.begin();

}

void loop() {
  // put your main code here, to run repeatedly:

}
