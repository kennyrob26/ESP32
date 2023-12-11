#include "FS.h"
#include <Arduino.h>
#include <SPI.h>
#include "TFT_eSPI.h"

//============== --- Instância de Objeto --- ==================

TFT_eSPI tft = TFT_eSPI();

TFT_eSPI_Button botao;

//============== --- Configurações Touch --- ==================

//Cria um arquivo no SPIFFS que armazena a ultima calibração do touch
#define CALIBRATION_FILE "/TouchCalData1"

//Define se a calibração deve ser realizada a cada reinicialização
    //false -> calibra toda vez ou touch
    // true -> calibra uma única vez e salva no SPIFFS
#define REPEAT_CAL false

//=============== --- Prototipos Funções --- ===================

void touch_calibrate();

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
  tft.drawString("Teste Botao", 120, 50);

  //Cria o botão
  botao.initButton(&tft, 120, 130, 100, 60, TFT_WHITE, TFT_BLUE, TFT_WHITE, "TESTE", 1);
  botao.drawButton();

}

//====================== --- Loop --- =========================

void loop()
{
  //Armazena qual a cordenada foi tocada
  uint16_t t_x = 0,
           t_y = 0;

  //booleano pressionado recebe true se detectar um toque na tela
    //A função getTouch também "retorna" as coordenadas x e y
    //onde o toque ocorreu
    //(modifica a variável apontada t_x e t_y neste caso)
  bool botaoPress = tft.getTouch(&t_x, &t_y);

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
}

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