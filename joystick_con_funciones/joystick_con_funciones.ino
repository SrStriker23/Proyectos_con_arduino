int xPin = A4;
int yPin = A5;
int switchPin = 2; // Pin del botón del joystick
int xVal; // Variable para almacenar los valores del eje x del joystick
int yVal; // Variable para almacenar los valores del eje y del joystick
int switchState; // Variable para almacenar el estado del interruptor del joystick

// Rango para considerar el joystick como "en reposo"
const int deadZone = 100;

void setup() {
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(switchPin, INPUT_PULLUP); // Establece el pin del interruptor como entrada con resistencia pull-up
  Serial.begin(9600); // Inicializa el monitor serial
}

void loop() {
  // Lee los valores de x, y y el estado del interruptor del joystick
  xVal = analogRead(xPin);
  yVal = analogRead(yPin);
  switchState = digitalRead(switchPin);

  // Detecta el movimiento del joystick en las direcciones principales
  if (xVal > 600) {
    moverDerecha();
  } else if (xVal < 400) {
    moverIzquierda();
  } else if (yVal > 600) {
    moverAbajo(); // Invertido: el valor alto de y ahora mueve hacia abajo
  } else if (yVal < 400) {
    moverArriba(); // Invertido: el valor bajo de y ahora mueve hacia arriba
  } else if (xVal > 512 - deadZone && xVal < 512 + deadZone && yVal > 512 - deadZone && yVal < 512 + deadZone) {
    enReposo();
  }

  delay(100); // Pausa para que las lecturas sean visibles
}

// Función que se activa al mover el joystick hacia la derecha
void moverDerecha() {
  Serial.println("Moviendo a la derecha");
}

// Función que se activa al mover el joystick hacia la izquierda
void moverIzquierda() {
  Serial.println("Moviendo a la izquierda");
}

// Función que se activa al mover el joystick hacia arriba
void moverArriba() {
  Serial.println("Moviendo hacia arriba");
}

// Función que se activa al mover el joystick hacia abajo
void moverAbajo() {
  Serial.println("Moviendo hacia abajo");
}

// Función que se activa cuando el joystick está en reposo
void enReposo() {
  Serial.println("Joystick en reposo");
}

