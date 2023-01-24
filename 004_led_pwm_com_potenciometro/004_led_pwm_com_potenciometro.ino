const int led =  2; //GPIO do led
const int pot = 4;  //GPIO do potenciometro

//Parâmetros do pwm
int canal = 0;
int frequencia = 5000;
int ciclo = 8;   //é o ciclo de trabalho

void setup() {

  Serial.begin(115200);

  //Configurações do PWM
  ledcSetup(canal, frequencia, ciclo);
  ledcAttachPin(led, canal);
}

void loop() {

  int valor = analogRead(pot);  //Recebe os dados do potenciômetro em 12 bits
  int brilho = map(valor, 0, 4095, 0, 255); //Converte para 8 bits
  Serial.println(brilho); //Recebe o valor do potenciometro em 8 bits
  ledcWrite(canal, brilho); //Muda o brilho do led de acordo com o potenciômetro


}
