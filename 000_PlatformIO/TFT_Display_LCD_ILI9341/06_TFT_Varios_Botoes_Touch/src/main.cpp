/*===========================================================
    Exemplo Simples de como trabalhar com um botão touch screen
  no display TFT. Para mais informações ler README.md
=============================================================*/

//================== --- Bibliotecas --- =====================
#include "FS.h"
#include <Arduino.h>
#include <SPI.h>
#include "TFT_eSPI.h"

//============== --- Instância de Classe --- ==================

TFT_eSPI tft = TFT_eSPI();

TFT_eSPI_Button botao[5]; //Onde 5 é a quantidade de botões

//============== --- Configurações Touch --- ==================

//Cria um arquivo no SPIFFS que armazena a ultima calibração do touch
#define CALIBRATION_FILE "/TouchCalData1"

//Define se a calibração deve ser realizada a cada reinicialização
    //false -> calibra toda vez ou touch
    // true -> calibra uma única vez e salva no SPIFFS
#define REPEAT_CAL false

//============== --- Configurações Botoes --- ==================
//Trabalhar com arrays facilita pois conseguimos utilizar o laço for

char botaoNome[5][2] = {"1", "2", "3", "4", "5"};

uint16_t botaoCor[5] = {TFT_RED, TFT_BLUE, TFT_GREEN, TFT_DARKCYAN, TFT_ORANGE};

//=============== --- Prototipos Funções --- ===================

void touch_calibrate();

void criarBotoes();

//====================== --- Setup --- =========================
void setup()
{
  Serial.begin(115200);

  //Inicia a tela TFT
  tft.init();

  //Define a rotação da tela
  tft.setRotation(0);

  //Chama a função de calibragem do touch
  touch_calibrate();

  //Derfine a cor de fundo
  tft.fillScreen(TFT_BLACK);

  //Centraliza o conteúdo
  tft.setTextDatum(MC_DATUM);

  //Configura e exibe texto na tela
  tft.setTextColor(TFT_ORANGE);
  tft.setFreeFont(&FreeSansBold12pt7b);
  tft.drawString("Teste Botoes", 120, 40);

  criarBotoes();
}

//====================== --- Loop --- =========================

void loop()
{
  //Armazena qual a cordenada foi tocada
  uint16_t t_x = 0,
           t_y = 0;
  
  //Salva a tecla pressionada
  uint8_t teclaPressionada;

  //Verfica se houve um toque na tela e qual suas coordenadas
  bool botaoPress = tft.getTouch(&t_x, &t_y);

  for(uint8_t btn = 0; btn < 5; btn++)
  {
    //Identifica qual botão foi pressionado
    if(botaoPress && botao[btn].contains(t_x, t_y))
      botao[btn].press(true);
    else
      botao[btn].press(false);
    
    //Verifica se o botão foi pressionado recentemente
    if(botao[btn].justPressed())
    {
      botao[btn].drawButton(true);
      teclaPressionada = botaoNome[btn][0];
      Serial.printf("Pressionou a tecla: %c \n", teclaPressionada);
      delay(50);
    }
    //Verifica se o usuário soltou o botão
    if(botao[btn].justReleased())
      botao[btn].drawButton();

    
  }

  /*
  //Identificando se o o botão foi pressionado
  if(botaoPress && botao.contains(t_x, t_y))
  {
    botao.press(true); //A tecla foi pressionada

    //justPresset() verifica se o botão foi pressionado recentemente
    if(botao.justPressed())
    {
      //Inverte a cor do botão, para indicar que ele foi pressionado
      botao.drawButton(true);
    }

    Serial.println("O botao foi pressionado!");

    //Cor e fonte do texto
    tft.setTextColor(TFT_RED);
    tft.setFreeFont(&FreeSans9pt7b);

    //Imprime na tela que o botão foi pressionado
    tft.drawString("O botao foi pressionado!", 120, 200);

    delay(2000);

    //Apaga o texto
    tft.fillRect(0, 195, 240, 205, TFT_BLACK);
  }
  else
    //Houve um toque na tela mas não foi no botão
    botao.press(false);

  //justRealesed() verifica se o botão foi "despressionado"
  if(botao.justReleased())
  {
    //Retorna o botão para a cor original
    botao.drawButton();
  }
  */
}

//====================== --- Funções --- =========================

void criarBotoes()
{
  //Centraliza os botões
  tft.setTextDatum(MC_DATUM);

  //Determina a coordenada y do primeiro botão
  uint16_t distancia = 110;

  for(uint8_t l = 0; l < 5; l++)
  {
    botao[l].initButton(&tft, 120, distancia, 60, 40, TFT_WHITE, botaoCor[l], TFT_WHITE, botaoNome[l], 1);

    botao[l].drawButton();

    //Aumenta 45 para distanciar os botões
    distancia += 45;
  }
}

//Esta é uma função da pópria biblioteca responsável por calibrar o touch
void touch_calibrate()
{
  uint16_t calData[5];
  uint8_t calDataOK = 0;

  // check file system exists
  if (!SPIFFS.begin()) {
    Serial.println("formatting file system");
    SPIFFS.format();
    SPIFFS.begin();
  }

  // check if calibration file exists and size is correct
  if (SPIFFS.exists(CALIBRATION_FILE)) {
    if (REPEAT_CAL)
    {
      // Delete if we want to re-calibrate
      SPIFFS.remove(CALIBRATION_FILE);
    }
    else
    {
      File f = SPIFFS.open(CALIBRATION_FILE, "r");
      if (f) {
        if (f.readBytes((char *)calData, 14) == 14)
          calDataOK = 1;
        f.close();
      }
    }
  }

  if (calDataOK && !REPEAT_CAL) {
    // calibration data valid
    tft.setTouch(calData);
  } else {
    // data not valid so recalibrate
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(20, 0);
    tft.setTextFont(2);
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.println("Touch corners as indicated");

    tft.setTextFont(1);
    tft.println();

    if (REPEAT_CAL) {
      tft.setTextColor(TFT_RED, TFT_BLACK);
      tft.println("Set REPEAT_CAL to false to stop this running again!");
    }

    tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.println("Calibration complete!");

    // store data
    File f = SPIFFS.open(CALIBRATION_FILE, "w");
    if (f) {
      f.write((const unsigned char *)calData, 14);
      f.close();
    }
  }
}

//====================== --- FIM --- =========================