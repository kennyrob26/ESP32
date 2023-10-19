/*
  Autor: Kenny Robert
  Trabalhando com Interrupções
    O código monitora um botão, e verifica por quanto tempo este ficou pressionado
    Por exemplo, se o usuário pressiona o botão por 10s, 
    a variável tempoPressionado armazenará algo em torno de 10.000 (10s)
    Assim é possível tomar decisões com base  no tempo que o botão foi pressionado 
*/

#include <Arduino.h>

/*=================--- Variáveis ---=========================*/

const short   botao  = 2;

//Sempre que algo for modificado tanto no programa principal, quanto na interrupção
//É importa definir tal variável com volatile para garantir a correta modificações
volatile unsigned long tempoAtual       = 0,
                       tempoAnterior    = 0,
                       tempoPressionado = 0;

volatile bool estadoBotao   = true;

/*=================--- Interrupções ISR ---=========================*/

void IRAM_ATTR mudaStatusBotao()
{
  tempoAtual = xTaskGetTickCount(); //Substitui o millis()
  //Para evitar acionamento acidental
  if((tempoAtual - tempoAnterior) > 1000)
  {
    //Quando o botão for de HIGH para LOW 
    //Será armazenado em tempoPressionado quanto tempo o botão ficou pressionado.
    if(!estadoBotao)
      tempoPressionado = tempoAtual - tempoAnterior;
    
    //Nunca esquercer de resetar o tempo anterior
    tempoAnterior = tempoAtual;
    //Inverte o valor de estado do botão
    estadoBotao = !estadoBotao;
    

  } 
}

/*========================--- SETUP ---=============================*/

void setup() 
{
  Serial.begin(115200);
  pinMode(botao, INPUT);                                //Interrompe..
  //attachInterrupt(botao, mudaStatusBotao, RISING);    //Na borda de subida
  //attachInterrupt(botao, mudaStatusBotao, FALLING);  //Na borda de descida
  attachInterrupt(digitalPinToInterrupt(botao), mudaStatusBotao, CHANGE);       //Na bordade de subida e descida
}

/*=========================--- LOOP ---=============================*/

void loop() 
{
  //Serial.println("O botão está: ");
  Serial.println(tempoPressionado);

  //Se o botão ficou pressionado por mais de 5 segundos
  if(tempoPressionado > 5000 )
  {
    Serial.println("Resetar o ESP");
    tempoPressionado = 0;
  }
  //Se o botão ficou pressionado por mais de 3 segundo e menos de 5 segundos
  else if(tempoPressionado > 3000)
  {
    Serial.println("Reiniciar ESP");
    tempoPressionado = 0;
  }
  //Se o botão foi pressionado por menos de 3 segundo
  else
  {
    tempoPressionado = 0;
  }
  delay(1000);
}