/*
  Este código utiliza o Sono profundo do ESP,
  Quando este está em sono profundo as únicas coisas que funcionarão serão:
  Controlador RTC, periféricos RTC e memórias RTC
*/

#include <Arduino.h>

//#define BUTTON_PIN_BITMASK 0x200000000 // 2^33 in hex
#define SEGUNDO_PARA_MICROSSEGUNDOS 1000000  //Para converter segundos em microssegundos
#define TEMPO_DE_SONO 10
#define LED 2

int tempoAnterior = 0;
String pino = "GPIO_NUM_4";

//Significa que é uma variável que será armazenada no RTC
//Isso é importante pois somente aquilo que está na memória RTC
//Poderá ser recuperado quando o ESP for bootado novamente
RTC_DATA_ATTR int bootCount = 0; 


//Função simples que apenas printa qual a causa do despertar

void print_motivo_despertou()
{
  esp_sleep_wakeup_cause_t motivo_despertou;
   motivo_despertou = esp_sleep_get_wakeup_cause();

  //Verifica as causas possiveis e imprime qual aconteceu
  switch (motivo_despertou)
  {
    case ESP_SLEEP_WAKEUP_EXT0 :
      Serial.println("Despertado por um sinal externo usando RTC_IO");
      break;
    case ESP_SLEEP_WAKEUP_EXT1:
      Serial.println("Despertado por um sinal externo usando RTC_CNTL");
      break;
    case ESP_SLEEP_WAKEUP_TIMER:
      Serial.println("Despertado por conta do tempo");
      break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD:
      Serial.println("Despertou por conta do touchpad");
      break;
    case ESP_SLEEP_WAKEUP_ULP:
      Serial.println("Despertado por conta do programa ULP");
      break;   
    default:
      Serial.printf("Não foi despertado pelo sono profundo: %d\n", motivo_despertou);
      break;
  }
  
}

void acionaLed()
{
  digitalWrite(LED, HIGH);
}

void setup() 
{
  pinMode(4, INPUT);
  pinMode(LED, OUTPUT);

  Serial.begin(115200);

  ++bootCount;
  Serial.println("Numeros de boot: " + String(bootCount));

  //Imprime o motivo do despertar
  print_motivo_despertou();

  acionaLed();

  //Define quanto tempo o ESP ficará em sono profundo
  esp_sleep_enable_timer_wakeup(TEMPO_DE_SONO * SEGUNDO_PARA_MICROSSEGUNDOS);

  //Define se o ESP será acordado por um botão (pino RTC)
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_4, 1);

  Serial.println("O ESP irá dormir por: " + String(TEMPO_DE_SONO) + "s" );

  Serial.println("Indo dormir");
  delay(1000);
  Serial.flush();

  //Coloca o ESP em sono profundo
  esp_deep_sleep_start();

  //tudo aquilo que está abaixo não aparecerá pois o ESP já dormiu
  Serial.print("Está mensagem nunca aparecerá");

}

void loop() 
{

}

