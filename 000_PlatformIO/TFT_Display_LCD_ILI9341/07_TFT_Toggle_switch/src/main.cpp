//====================== --- Bibliotecas --- =============================

#include "FS.h"

#include <SPI.h>

#include <TFT_eSPI.h> 

#include <Toggle_Switch.h>

//================== --- Instâncias de Classe --- ==========================

TFT_eSPI tft = TFT_eSPI();      

Toggle_Switch toggle[5];

//====================== --- Confg. Touch --- =============================

#define CALIBRATION_FILE "/TouchCalData4"

#define REPEAT_CAL false

//==================== --- Protótipo Funções --- ===========================

void touch_calibrate();


//======================= ---||  SETUP  ||--- =============================

void setup(void)
{
  Serial.begin(115200);
  tft.init();

  tft.setRotation(0);

  touch_calibrate();

  tft.fillScreen(TFT_BLACK);
  uint8_t estilo  = 1;
  uint8_t tamanho =  3; 
  uint8_t x      = 30;
  uint8_t y      =  50;

  for(uint8_t i = 0; i < 5; i++)
  {
    toggle[i].initToggle(&tft, x, y, 2, i+1, TFT_LIGHTGREY, TFT_BLUE, TFT_DARKGREY, TFT_WHITE);
    toggle[i].drawToggle();

    y += 50;
  }

}

//======================== ---|| LOOP  ||--- =============================

void loop()
{
  uint16_t t_x = 0,
           t_y = 0;
  
  bool botaoPress = tft.getTouch(&t_x, &t_y);

  for(uint8_t i = 0; i<5; i++)
  {
    if(botaoPress && toggle[i].contains(t_x, t_y))
    {
      toggle[i].pressed();
      Serial.printf("Botão %d = %s\n", i+1 ,(toggle[i].returnStatus()?"Ligado":"Desligado"));

    }
  }

}

//====================== ---|| Funções ||--- =============================

void touch_calibrate()
{
  uint16_t calData[5];
  uint8_t calDataOK = 0;

  // check file system exists
  if (!SPIFFS.begin()) {
    Serial.println("Formatting file system");
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


//====================== ---|| FIM ||--- =============================