const int led = 2;

bool  movimento = 0;

void setup() {
  Serial.begin(115200);
  pinMode(2, INPUT);

}

void loop() {
  movimento = digitalRead(led);
  //Serial.println(digitalRead(led));
  
  if(movimento == 0){
    Serial.println("Tudo OK!");
  } else{
    Serial.println("ATENÇÃO MOVIMENTO DETECTADO!!");
  }
  delay(300);

}
