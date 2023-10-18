/*
  Código simples para verificar a porcentagem de uma bateria
  Autor: Kenny Robert
  Data: 20/08/2023
*/

/*=================--- Bibliotecas ---=========================*/
#include <Arduino.h>

/*=================--- Variáveis ---=========================*/

const unsigned int pinoBat    = 4  ;
float              leituraBat = 0.0,
                   tensaoBat  = 0.0;
unsigned int       porcentBat = 0  ;
                   



/*====================--- Setup ---============================*/
void setup() 
{
  pinMode(pinoBat, INPUT);
  Serial.begin(115200);

}

/*====================--- Loop ---=========================*/
void loop() 
{
  leituraBat = analogRead(pinoBat);
  Serial.println(leituraBat);

  tensaoBat = map(leituraBat, 0, 4095, 0, 5450) / 1000.00;
  Serial.println(tensaoBat);

  if(tensaoBat <= 2.7)
  {
    porcentBat = 0;
  }
  else if(tensaoBat <= 4.2)
  {
    int tensao = tensaoBat * 1000;
    porcentBat = map(tensao, 2700, 4200 , 0, 100);
  }
  else {
    porcentBat = 100;
  }

  printf("%d%% \n", porcentBat);
  delay(500);

}
