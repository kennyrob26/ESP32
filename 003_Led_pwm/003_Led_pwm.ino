int pinLed1 = 2;

//pwm
int frequencia = 5000; //valor bom para trabalhar com led (o valor varia com o componete que estamos trabalhado)
int canal = 0;         //O esp32 possui 16 canais PWM, que vão de 0-15
int resolucao = 8;     //Significa que vamos trabalhar com 8 bits (0-255), mas o esp trabalha com até 16 bits

void setup() {
  //Configurações do pwm no canal desejado
  ledcSetup(canal, frequencia, resolucao);

  //Resumindo o led pinLed1 utiliza as configurações de pwm do canal 0
  ledcAttachPin(pinLed1, canal);

}

void loop() {
  // Laço de repetição que acende o led gradativamente
 //Como estamos trabalhando com 8 bits, o ciclo varia de 0 a 255
  for(int ciclo = 0 ; ciclo <= 255; ciclo++){
    ledcWrite(canal, ciclo);
    delay(15);
  }

  //Laço de repetição que apaga o led gradativamente 
  for(int ciclo = 255; ciclo >= 0; ciclo--){
    ledcWrite(canal, ciclo);
    delay(15);
  }


}
