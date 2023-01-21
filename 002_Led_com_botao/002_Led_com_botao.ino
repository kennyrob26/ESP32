int pinLed = 2;
int pinBut = 17;
int pressionado;
void setup() {
  // put your setup code here, to run once:
  pinMode(pinLed, OUTPUT);
  pinMode(pinBut, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  pressionado = digitalRead(pinBut);
  if(pressionado){
    digitalWrite(pinLed, HIGH);
  }else{
    digitalWrite(pinLed, LOW);
  }
}
