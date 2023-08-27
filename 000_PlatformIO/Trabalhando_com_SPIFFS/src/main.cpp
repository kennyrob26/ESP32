#include <Arduino.h>
#include "SPIFFS.h"

void setup() {
  //Definição da taxa serial utilizada
  Serial.begin(9600);

  //faz a montagem do sistema de arquivos, e verifica se a montagem foi bem sucedida
  if(!SPIFFS.begin(true))
  {
    Serial.println("Ocorreu um erro ao tentar montar o sistema de arquivos SPIFFS");
    return;
  }

  //Verifica se o arquivo existe/pode ser aberto
  File arquivo = SPIFFS.open("/text.txt");
  if(!arquivo)
  {
    Serial.println("Falha ao tentar abrir/ler o arquivo");
  }

    //De fato faz a leitura do arquivo
  while(arquivo.available())
  {
    Serial.write(arquivo.read());
  }
  arquivo.close();


}

void loop() {

}

