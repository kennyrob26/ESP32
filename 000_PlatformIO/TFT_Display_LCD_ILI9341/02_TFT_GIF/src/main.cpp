/*==================--- Bibliotecas ---======================*/

#include "SPI.h"
#include "TFT_eSPI.h"

/*====================--- Imagens ---======================*/

#include "bob1.h"
#include "bob2.h"
#include "bob3.h"
#include "bob4.h"
#include "bob5.h"
#include "bob6.h"

//============--- Instanciando Objeto ---=====================

TFT_eSPI tft = TFT_eSPI();

//====================--- Setup---============================
void setup()
{
  //Inicia o TFT
  tft.begin();

  tft.setRotation(1);
  
  //Garante as cores corretas de exibição
  tft.setSwapBytes(true);

}

//====================--- Loop ---============================

/*    Basicamente nós temos um GIF do Bob Esponja que foi dividido em 4 imagens
  As 4 imagens reproduzidas em um intervalode de 100 milis nos passa uma sensação
  de movimento
*/

void loop()
{
  //Intervalo entre as imagens
  short int tempo = 100;

  tft.pushImage(0, 0, BOB1_WIDTH, BOB1_HEIGHT, bob1);           //Imprime Imagem 1   
  delay(tempo);

  tft.pushImage(0, 0, BOB2_WIDTH, BOB2_HEIGHT, bob2);           //Imprime Imagem 2
  delay(tempo);

  tft.pushImage(0, 0, BOB3_WIDTH, BOB3_HEIGHT, bob3);           //Imprime Imagem 3
  delay(tempo);

  tft.pushImage(0, 0, BOB4_WIDTH, BOB4_HEIGHT, bob4);           //Imprime Imagem 4
  delay(tempo);

  tft.pushImage(0, 0, BOB5_WIDTH, BOB5_HEIGHT, bob5);           //Imprime Imagem 5
  delay(tempo);

  tft.pushImage(0, 0, BOB6_WIDTH, BOB6_HEIGHT, bob6);           //Imprime Imagem 6
  delay(tempo);
}