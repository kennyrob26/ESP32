#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "index_html.h"

//informações do wifi
const char* ssid = "Valdirene";
const char* password = "wifi@@@@";

//pinos GPIO
int ledR = 2;   //vermelho
int ledG = 4;   //verde  
int ledB = 16;  //azul

//Parâmetros do PWM
const int freq = 5000;
const int canalR = 0; //canal do vermelho
const int canalG = 1; //canal do verde
const int canalB = 2; //canal do azul
const int ciclo = 8;  //Definir o ciclo de trabahlo como 8 bits (0-255)

//Parâmetros passados pela a URL
const char* PARAM_INPUT_1 = "canal"; //Canal pwm que o led está utilizando
const char* PARAM_INPUT_2 = "brilho"; //valor de 0 a 255

//Criando o servidor na porta 80
AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);

  //Configurações do pwm
  //Cor vermelha
  ledcSetup(canalR, freq, ciclo);
  ledcAttachPin(ledR, canalR);

  //cor verde
  ledcSetup(canalG, freq, ciclo); 
  ledcAttachPin(ledG, canalG);

  //cor azul
  ledcSetup(canalB, freq, ciclo);
  ledcAttachPin(ledB, canalB);

   //Conectando a rede Wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println("Conectando ao wifi ... ");
  }

  //Exibe o ip fornecido pelo DHCP
  Serial.println(WiFi.localIP());

  //Rotas
  server.on("/", HTTP_GET, [] (AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, htmlDinamico);
  });
  
  server.on("/led", HTTP_GET, [] (AsyncWebServerRequest *request){
    String nCanal;
    String vBrilho;

    if(request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)){
      nCanal = request->getParam(PARAM_INPUT_1)->value();
      vBrilho = request->getParam(PARAM_INPUT_2)->value();
      ledcWrite(nCanal.toInt(), vBrilho.toInt());
    }else{
      nCanal = "Não há mensagem";
      vBrilho = "Não há mensagem";
    }
    Serial.print("Canal: ");
    Serial.print(nCanal);
    Serial.print(" está com o brilho em: ");
    Serial.println(vBrilho);
    request->send(200,"text/plain", "OK");


  });//Fechamento do server on "/"

  server.begin();
  
}

void loop() {


}

String htmlDinamico(const String& var){
  if(var == "CONTEUDO_DINAMICO"){
    String barra = "";
    barra += "<p>R <input id=\"0\" type=\"range\" onchange=\"atualiza(this)\" min=\"0\" max=\"255\"></p>";
    barra += "<p>G <input id=\"1\" type=\"range\" onchange=\"atualiza(this)\" min=\"0\" max=\"255\"></p>";
    barra += "<p>B <input id=\"2\" type=\"range\" onchange=\"atualiza(this)\" min=\"0\" max=\"255\"></p>";
    return barra;
  }
  return String();
}
















