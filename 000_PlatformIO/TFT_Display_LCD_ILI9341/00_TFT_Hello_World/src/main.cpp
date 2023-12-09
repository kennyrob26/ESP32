#include <Arduino.h>
#include "TFT_eSPI.h"
#include "mundo.h"

//============--- Protópipo de Funções ---==================

void helloWorld();

//============--- Instanciando Objeto---==================

TFT_eSPI tft = TFT_eSPI();

//====================--- Setup---============================

void setup()
{
  //Inicia o TFT
  tft.begin();


  tft.setRotation(1);

  //Muito importante sempre que trabalhamos com exibição de imagens
  //Este método garante a ordem das cores (R -> R, G -> G, B -> B)
  //Sem ele pode ser que as cores sejam trocadas (R -> G por exemplo)
  tft.setSwapBytes(true);

  helloWorld();

}

//===================--- LOOP ---=================================

void loop()
{

}

//============--- Funções---==================


void helloWorld()
{
    //o texto será centralizado
  tft.setTextDatum(MC_DATUM);

    //O Texto será branco com fundo preto
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  //Define o fundo da tela como BLACK
  tft.fillScreen(TFT_BLACK);

  //Borda (retangulo Laranja)
  tft.drawRect(5,5,310, 230, TFT_ORANGE);

  delay(1000);

  //Escreve Hello World na tela
  tft.setTextColor(TFT_ORANGE);
  tft.setFreeFont(&FreeMonoBold18pt7b);
  tft.drawString("HELLO WORLD!", 160, 30);

  delay(2000);

  //Escreve a frase na tela
  tft.setFreeFont(&FreeMono9pt7b);
  tft.drawString("Primeiro texto na tela!", 160, 70);

  //Imprime a imagem presente em "mundo.h"
  tft.pushImage(80, 110, MUNDO_WIDTH, MUNDO_HEIGHT, mundo);

}