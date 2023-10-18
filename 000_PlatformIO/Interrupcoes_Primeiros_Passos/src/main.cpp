#include <Arduino.h>

const short   botao         = 2;
unsigned long tempoAtual    = 0,
              tempoAnterior = 0;
volatile bool estadoBotao   = false;


void IRAM_ATTR mudaStatusBotao()
{
  tempoAtual = xTaskGetTickCount(); //Substitui o millis()
  if((tempoAtual - tempoAnterior) > 10)
  {
    estadoBotao = !estadoBotao;
    tempoAnterior = tempoAtual;

  } 
}


void setup() 
{
  Serial.begin(115200);
  pinMode(botao, INPUT);                                //Interrompe..
  //attachInterrupt(botao, mudaStatusBotao, RISING);    //Na borda de subida
  //attachInterrupt(botao, mudaStatusBotao, FALLING);  //Na borda de descida
  attachInterrupt(botao, mudaStatusBotao, CHANGE);       //Na bordade de subida e descida
}
void loop() 
{
  Serial.print("O botão está: ");
  
  if(estadoBotao)
  {
    Serial.println("Ativo");
  }
  else
  {
    Serial.println("Desativado");
  }
  delay(1000);
}


