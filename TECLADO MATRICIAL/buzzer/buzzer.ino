void setup() {
  pinMode(7, OUTPUT);  // Configura el pin 5 como salida
}

void loop() {
  tone(7, 1000, 200);  // Intenta hacer sonar el buzzer en el pin 5
  delay(1000);         // Espera un segundo
}

