
/*===================---Bibliotecas---=====================*/
#include <Arduino.h>
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

/*==============---Variáveis e constantes---===============*/

// Credenciais da rede WiFi
const char* rede  = "Valdirene";
const char* senha = "wifi@@@@"; 

// Vamos trabalhar com formulários e input1 .. inputN.. é o nome do input no formulário html
// Ou seja, é a maneira de identificarmos qual formulário foi preenchido pelo usuário
// se input1, foi o primeiro, se input2 o segundo...

const char* PARAMETRO_RECEBIDO_1 = "input1";
const char* PARAMETRO_RECEBIDO_2 = "input2";
const char* PARAMETRO_RECEBIDO_3 = "input3";


// Instância o objeto server
AsyncWebServer server(80);


/*======================---Setup---========================*/

void setup()
{
  Serial.begin(115200);
  
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
    request->send(SPIFFS, "/index.html", String(), false);
  });

  //O html vai solicitar o css, então é necessário esse roteamento
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text.css");
  });

  /*
    quando o usuário clicar em submit no formulário, será enviado a mensagem via /get
    Algo do tipo:
    
    IP_ESP/get?input1=Conteudo_da_mensagem

    Então nós vamos identificar em qual input foi inserida a mensagem
    E qual o conteúdo da mensagem

  */
  server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request){
    String mensagemRecebida;
    String parametroRecebido;

    //Verifica se a mensagem é do formulário input1
    if(request->hasParam(PARAMETRO_RECEBIDO_1))
    {
      mensagemRecebida  = request->getParam(PARAMETRO_RECEBIDO_1)->value();
      parametroRecebido = PARAMETRO_RECEBIDO_1;
    }
    //Verifica se a mensagem é do formulário input2
    else if(request->hasParam(PARAMETRO_RECEBIDO_2))
    {
      mensagemRecebida  = request->getParam(PARAMETRO_RECEBIDO_2)->value();
      parametroRecebido = PARAMETRO_RECEBIDO_2;
    }
    //Verifica se a mensagem é do formulário input3
    else if(request->hasParam(PARAMETRO_RECEBIDO_3))
    {
      mensagemRecebida  = request->getParam(PARAMETRO_RECEBIDO_3)->value();
      parametroRecebido = PARAMETRO_RECEBIDO_3;
    }
    else
    {
      mensagemRecebida  = "Não há mensagem";
      parametroRecebido = "vazio"; 
    }

    Serial.println(mensagemRecebida);
    request->send(SPIFFS, "/index.html", String(), false);

  });

  //Inicia o servidor
  server.begin();

}

/*======================---Loop---========================*/

void loop() 
{
  //Sem conteúdo
}




