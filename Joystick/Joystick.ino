int xPin = A4;
int yPin = A5;
int xVal; // variable para almacenar los valores del eje x del joystick
int yVal; // variable para almacenar los valores del eje y del joystick
 
void setup() {
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  Serial.begin(9600); // inicializa el monitor serial
}
 
void loop() {
  // lee los valores de x, y y el estado del interruptor del joystick
  xVal = analogRead(xPin);
  yVal = analogRead(yPin);
 
  // imprime las lecturas en el monitor serial
  Serial.print("X: ");
  Serial.print(xVal);
  Serial.print(" | Y: ");
  Serial.println(yVal);

 
  delay(100); // pausa para que las lecturas sean visibles
}
