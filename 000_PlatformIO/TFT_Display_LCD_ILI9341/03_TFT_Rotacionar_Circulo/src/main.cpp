
#include "SPI.h"
#include "TFT_eSPI.h"


  int teste = 1;
// Use hardware SPI
TFT_eSPI tft = TFT_eSPI();

//============--- Protótipo das Funções ---====================

void printRotacionaLinha();

float calculaAngulo_x(float x1, float x2, float y1, float y2, float ang);
float calculaAngulo_y(float x1, float x2, float y1, float y2, float ang);

//====================--- Setup---============================
void setup()
{
  tft.begin();

  tft.setRotation(1);

  
}

//====================--- Loop ---============================
void loop()
{
  printRotacionaLinha();
}

//====================--- FUNÇÕES---============================


void printRotacionaLinha()
{
  
  tft.fillScreen(TFT_BLACK);

  //Definição das coordenadas
  int x1 = 160,
      y1 = 120,
      x2 = 160,
      y2 = 240;

  for(int ang = 0; ang <= 360; ang++)
  {
    //Apaga a esfera e linha anterior
    if(ang > 2)
    {
      //Recebe 2 angulos anteriores e apaga
      int x_anterior = calculaAngulo_x(x1, x2, y1, y2, ang-3);
      int y_anterior = calculaAngulo_y(x1, x2, y1, y2, ang-3);

      tft.fillCircle(x_anterior, y_anterior, 10, TFT_BLACK);
      tft.drawLine(x1, y1, x_anterior, y_anterior, TFT_BLACK);
    }

    //Recebe o angulo atual
    int x2_rot = calculaAngulo_x(x1, x2, y1, y2, ang); 
    int y2_rot = calculaAngulo_y(x1, x2, y1, y2, ang);

    tft.drawLine(x1, y1, x2_rot, y2_rot, TFT_BLUE);
    tft.fillCircle(x2_rot, y2_rot, 10, TFT_BLUE);

    delay(15);
  } 
}

float calculaAngulo_x(float x1, float x2, float y1, float y2, float angulo)
{
  //Converte graus em radianos
  float anguloRad   = angulo * PI / 180.0;

  //É necessário trabalharmos com coordenadas relativas,
  //Pois não estamos trabalhando na origem (x = 0, y = 0)
  float coordRelativa_x = x2 - x1;
  float coordRelativa_y = y2 - y1;

  //São as equações que de fato calculam  a rotação
  //São baseadas na generalização da matriz de rotação
  float x2_rot = x1 + (coordRelativa_x * cos(anguloRad) - coordRelativa_y * sin(anguloRad));
  return(x2_rot);

}
float calculaAngulo_y(float x1, float x2, float y1, float y2, float angulo)
{
  //Converte graus em radianos
  float anguloRad   = angulo * PI / 180.0;

  //É necessário trabalharmos com coordenadas relativas,
  //Pois não estamos trabalhando na origem (x = 0, y = 0)
  float coordRelativa_x = x2 - x1;
  float coordRelativa_y = y2 - y1;

  //São as equações que de fato calculam  a rotação
  //São baseadas na generalização da matriz de rotação
  float y2_rot = y1 + (coordRelativa_x * sin(anguloRad) + coordRelativa_y * cos(anguloRad));

  return(y2_rot);

}
