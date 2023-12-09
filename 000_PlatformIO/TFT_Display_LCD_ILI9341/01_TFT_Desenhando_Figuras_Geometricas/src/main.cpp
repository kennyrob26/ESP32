
#include "SPI.h"
#include "TFT_eSPI.h"
#include "mundo.h"


  int teste = 1;
// Use hardware SPI
TFT_eSPI tft = TFT_eSPI();

//============--- Protótipo das Funções ---====================

void printBadeiraDoBrasil();
void printFaixasDeslizantes();
void printCirculosCrescente();
void printRotacionaTriangulo();

//====================--- Setup---============================
void setup()
{
  tft.begin();

  tft.setRotation(1);

  
}

//====================--- Loop ---============================
void loop()
{
  //printBadeiraDoBrasil();
  //printFaixasDeslizantes();
  //printCirculosCrescente();
}

//====================--- FUNÇÕES---============================


//======---------- Desenha a Bandeira do Brasil -----------==========

void printBadeiraDoBrasil()
{
   //o texto está centralizado
  tft.setTextDatum(MC_DATUM);

  //Fundo verde
  tft.fillScreen(TFT_DARKGREEN);

  delay(500);

  //Dois triangulos que formam o losangolo
  tft.fillTriangle(0, 120, 160, 0, 320, 120, TFT_YELLOW);
  tft.fillTriangle(0, 120, 160, 240, 320, 120, TFT_YELLOW);
  delay(500);

  //Circulo central
  tft.fillCircle(160, 120, 80, TFT_BLUE);

  tft.drawArc(160, 120, 80, 80, 0, -1, TFT_WHITE, TFT_WHITE);
  delay(500);

  //imprime a faixa branca
  for(int i = 115; i <= 125; i++)
    tft.drawFastHLine(80, i, 160, TFT_WHITE);

  delay(5000);
}


void printFaixasDeslizantes()
{
  //É a velocidade com que as faixas se movimentam
  int tempo = 1;

  //Troca a cor a cada iteração
  for(int c = 0; c<= 65000; c += 20)
  {
    //Movimenta as faixas da esquerda para a direita
    for(int i = 0; i <= 319; i++)
    {
      //Desenha os pixels na linha x coluna com a cor c
      for(int j = 0; j <= 239; j++)
      {
        tft.drawPixel(i, j, c);
        delayMicroseconds(tempo);
      }
    }
    //Movimenta as faixas da direita para a esquerda
    for(int i = 320; i >= 1; i--)
    {
      //Desenha os pixels na linha x coluna com a cor c
      for(int j = 240; j >= 0; j--)
      {
        tft.drawPixel(i, j, c + 10);
        delayMicroseconds(tempo);
      }
    }
  }

}

void printCirculosCrescente()
{
  tft.fillScreen(TFT_BLACK);
  int cor = rand() % 65000;
  for(int r = 0; r <= 160; r++)
  {
    tft.drawCircle(160, 120, r, cor);
    tft.drawCircle(160, 120, r+1, cor);
    tft.drawCircle(160, 120, r+2, cor);
    tft.drawCircle(160, 120, r, TFT_BLACK);

  }
  
}

void printRotacionaTriangulo()
{
  tft.fillScreen(TFT_BLACK);

  //Definindo os pontos iniciais do triangulo
  int x1 =  60,
      y1 = 200,
      x2 = 160,
      y2 =  27,
      x3 = 260,
      y3 = 200;

  for(int i = 0; i <= 50; i++)
  {
    x1 += 2;
    y1 -= 1;
    y2 += 3;
    x3 -= 2;
    y3 -= 1;

    tft.drawTriangle(x1, y1, x2, y2, x3, y3, TFT_BLUE);

    delay(300);
  }
  
}