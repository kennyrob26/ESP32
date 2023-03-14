/*
  Este código utiliza como base o projeto https://randomnerdtutorials.com/esp32-mqtt-publish-subscribe-arduino-ide/
  Basicamente vamos utilizar a biblioteca PubSubClient para conseguirmos utilizar o protocolo MQTT
  O Broker utilizado é o Mosquitto
  Além de utilizarmos também a plataforma Node-red
*/



#include <WiFi.h>
#include <PubSubClient.h>

//nome e senha da rede utilizada pelo ESP32
const char* ssid = "Valdirene";
const char* senha = "wifi@@@@";

//Aqui colocamos o IP do nosso Broker
//No linux pode ser obtido com o comando "hostname -I"
const char* mqtt_server = "10.0.0.146";

//Código padrão para pubsub
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

//Leds nos pinos 2 e 4
const int led1 = 2;
const int led2 = 4;

//==================== SETUP ====================================

void setup() {
  Serial.begin(115200);

  //É uma função que configura/conecta ao wifi, criada logo abaixo
  setup_wifi();
  //Ou seja, é o IP do broker e a porta utilizada
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

//===================== LOOP =====================================

void loop() {
  if(!client.connected()){
    reconnect();
  }
  client.loop();

}


//===================== FUNÇÕES ===================================


//----------------- SETUP_WIFI()-----------------------------------

//Função responsável pela configuração do wifi
//Ela é muito comum em qualquer projeto que utilize WiFi

void setup_wifi(){
  delay(10);
  Serial.print("Tentado conectar a rede: ");
  Serial.println(ssid);

  WiFi.begin(ssid, senha);

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Conectado ao WiFi");
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());

}

//---------------- CALLBACK() --------------------------------------

//Essa função é muito IMPORTANTE
//Ela trata de todos os callback

void callback(char* topic, byte* message, unsigned int length){
  Serial.print("Uma nova mensagem do tópico: ");
  Serial.print(topic);
  Serial.print(". Mensagem: ");

  //É quem armazena o conteúdo da mensagem, algo como um buffer
  String messageTemp;

  //apenas coloca a informação de message dentro de messageTemp
  for (int i = 0; i < length; i++){
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  //Aqui vamos fazer a leitura da mensagem
  //De acordo com o valor da mensagem 
  //acendemos ou apegamos um dos leds

  if(String(topic) == "esp32/leds"){
    Serial.print("Recebemos a mensagem:");

    //Apaga o acende o led 1
    if(messageTemp == "led1_on"){
      Serial.println("led1_on");
      digitalWrite(led1, HIGH);
    }
    else if(messageTemp == "led1_off"){
      Serial.println("led1_off");
      digitalWrite(led1, LOW);
    }

    //apaga ou acende o led 2
    else if(messageTemp == "led2_on"){
      Serial.println("led2_on");
      digitalWrite(led2, HIGH);
    }
    else if(messageTemp == "led2_off"){
      Serial.println("led2_off");
      digitalWrite(led2, LOW);
    }
    
  }
}

//-------------- RECONNECT() --------------------------

//Função responsável por conetar ao MQTT
//é Aqui quem definimos as subscrições
void reconnect(){
  while(!client.connected()){
      Serial.println("conexão MQTT em andamento...");
    if(client.connect("ESP8266Client")){
      Serial.println("conectado");

      //Tópico que vamos nos increver
      client.subscribe("esp32/leds");
    }else{
      Serial.print("Algo deu errado, ");
      Serial.println("tentaresmo reconectar em 5 segundos ");
      delay(5000);
    }

  }

}
































