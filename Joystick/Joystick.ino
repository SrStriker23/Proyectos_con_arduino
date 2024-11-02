int xPin = A4;
int yPin = A5;
int switchPin = 2; // Pin del botón del joystick
int xVal; // variable para almacenar los valores del eje x del joystick
int yVal; // variable para almacenar los valores del eje y del joystick
int switchState; // variable para almacenar el estado del interruptor del joystick
 
void setup() {
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(switchPin, INPUT_PULLUP); // Establece el pin del interruptor como entrada con resistencia pull-up
  Serial.begin(9600); // inicializa el monitor serial
}
 
void loop() {
  // lee los valores de x, y y el estado del interruptor del joystick
  xVal = analogRead(xPin);
  yVal = analogRead(yPin);
  switchState = digitalRead(switchPin);
 
  // imprime las lecturas en el monitor serial
  Serial.print("X: ");
  Serial.print(xVal);
  Serial.print(" | Y: ");
  Serial.print(yVal);
  Serial.print(" | Switch: ");
  Serial.println(switchState);
 
  delay(100); // pausa para que las lecturas sean visibles
}
