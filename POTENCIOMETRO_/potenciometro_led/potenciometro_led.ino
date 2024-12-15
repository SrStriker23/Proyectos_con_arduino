int ledpin = 10;
int potpin = A2;
int potval;
int dt = 200;
int light;
void setup() {
  pinMode(ledpin, OUTPUT);
  pinMode(potpin, INPUT);
  Serial.begin(9600);
}

void loop() {
  potval = analogRead(potpin);
  Serial.println(potval);
  Serial.println(light);
  light = map(potval,0,1023,0,255);
  analogWrite(ledpin,light);
  delay(dt);
}
