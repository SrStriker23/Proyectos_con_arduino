float vout;
float vread;
int dt = 100;
float analogval;

void setup() {
  pinMode(vread,INPUT);
  Serial.begin(9600);
}

void loop() {
  analogval = analogRead(vread);
  vout=(5.*analogval)/1023;
  Serial.print("El voltaje acutal es : ");
  Serial.print(vout);
  Serial.println("Voltios");
  delay(dt);
}
