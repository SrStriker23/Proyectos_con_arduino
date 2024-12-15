

// Pines del joystick
int xPin = A4;        // Pin del eje X del joystick
int yPin = A5;        // Pin del eje Y del joystick
int xVal;             // Variable para almacenar el valor del eje X del joystick
int yVal;             // Variable para almacenar el valor del eje Y del joystick

// Rango para considerar el joystick "en reposo"
const int deadZone = 300;

// Pines para las columnas y filas de la matriz LED
int columnas[] = { 2, 3, 4, 5, 6, 7, 8, 9 };       // Pines de las columnas de la matriz
int filas[] = { 10, 11, 12, 13, A0, A1, A2, A3 };  // Pines de las filas de la matriz

// Funciones de figuras para la matriz LED

// Dibuja la figura para el movimiento hacia la izquierda
void left() {
  encenderUnLed(3, 0);
  encenderUnLed(4, 0);
  encenderUnLed(2, 1);
  encenderUnLed(3, 1);
  encenderUnLed(1, 2);
  encenderUnLed(2, 2);
  // Resto de la figura
  encenderUnLed(0, 3);
  encenderUnLed(1, 3);
  encenderUnLed(2, 3);
  encenderUnLed(3, 3);
  encenderUnLed(4, 3);
  encenderUnLed(5, 3);
  encenderUnLed(6, 3);
  encenderUnLed(7, 3);
  encenderUnLed(0, 4);
  encenderUnLed(1, 4);
  encenderUnLed(2, 4);
  encenderUnLed(3, 4);
  encenderUnLed(4, 4);
  encenderUnLed(5, 4);
  encenderUnLed(6, 4);
  encenderUnLed(7, 4);
  encenderUnLed(1, 5);
  encenderUnLed(2, 5);
  encenderUnLed(2, 6);
  encenderUnLed(3, 6);
  encenderUnLed(3, 7);
  encenderUnLed(4, 7);
}

// Dibuja la figura para el movimiento hacia adelante
void forward() {
  encenderUnLed(3, 0);
  encenderUnLed(4, 0);
  encenderUnLed(2, 1);
  encenderUnLed(5, 1);
  encenderUnLed(1, 2);
  encenderUnLed(6, 2);
  encenderUnLed(0, 3);
  encenderUnLed(0, 4);
  encenderUnLed(7, 3);
  encenderUnLed(7, 4);
  encenderUnLed(1, 5);
  encenderUnLed(6, 5);
  encenderUnLed(2, 6);
  encenderUnLed(5, 6);
  encenderUnLed(3, 7);
  encenderUnLed(4, 7);
}

// Dibuja la figura para el movimiento hacia la derecha
void right() {
  encenderUnLed(3, 0);
  encenderUnLed(4, 0);
  encenderUnLed(4, 1);
  encenderUnLed(5, 1);
  encenderUnLed(5, 2);
  encenderUnLed(6, 2);
  encenderUnLed(0, 3);
  encenderUnLed(1, 3);
  encenderUnLed(2, 3);
  encenderUnLed(3, 3);
  encenderUnLed(4, 3);
  encenderUnLed(5, 3);
  encenderUnLed(6, 3);
  encenderUnLed(7, 3);
  encenderUnLed(0, 4);
  encenderUnLed(1, 4);
  encenderUnLed(2, 4);
  encenderUnLed(3, 4);
  encenderUnLed(4, 4);
  encenderUnLed(5, 4);
  encenderUnLed(6, 4);
  encenderUnLed(7, 4);
  encenderUnLed(6, 5);
  encenderUnLed(5, 5);
  encenderUnLed(4, 6);
  encenderUnLed(5, 6);
  encenderUnLed(3, 7);
  encenderUnLed(4, 7);
}

// Dibuja la figura para el movimiento hacia abajo
void stop() {
  encenderUnLed(3, 0);
  encenderUnLed(4, 0);
  encenderUnLed(3, 1);
  encenderUnLed(4, 1);
  encenderUnLed(3, 2);
  encenderUnLed(4, 2);
  encenderUnLed(3, 3);
  encenderUnLed(4, 3);
  encenderUnLed(3, 6);
  encenderUnLed(4, 6);
  encenderUnLed(3, 7);
  encenderUnLed(4, 7);
}

// Dibuja la figura para el estado en reposo (standby)
void stand_by() {
  encenderUnLed(0, 3);
  encenderUnLed(1, 3);
  encenderUnLed(2, 3);
  encenderUnLed(3, 3);
  encenderUnLed(4, 3);
  encenderUnLed(5, 3);
  encenderUnLed(6, 3);
  encenderUnLed(7, 3);
  encenderUnLed(0, 4);
  encenderUnLed(1, 4);
  encenderUnLed(2, 4);
  encenderUnLed(3, 4);
  encenderUnLed(4, 4);
  encenderUnLed(5, 4);
  encenderUnLed(6, 4);
  encenderUnLed(7, 4);
}

// Funciones para controlar el joystick

// Función que se activa cuando el joystick se mueve hacia la derecha
void moverDerecha() {
  right();
}

// Función que se activa cuando el joystick se mueve hacia la izquierda
void moverIzquierda() {
  left();
}

// Función que se activa cuando el joystick se mueve hacia arriba
void moverArriba() {
  stand_by();
}

// Función que se activa cuando el joystick se mueve hacia abajo
void moverAbajo() {
  stop();
}

// Función que se activa cuando el joystick está en reposo
void enReposo() {
  forward();
}

void setup() {
  // Configurar pines de columnas y filas de la matriz LED como salidas
  for (int i = 0; i < 8; i++) {
    pinMode(columnas[i], OUTPUT);
    pinMode(filas[i], OUTPUT);

    // Inicialmente, apagar todos los LEDs
    digitalWrite(columnas[i], LOW);  // Desactiva columnas
    digitalWrite(filas[i], HIGH);      // Desactiva filas
  }

  // Configurar pines del joystick como entradas
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
}

void loop() {
  // Leer los valores actuales del joystick
  xVal = analogRead(xPin);
  yVal = analogRead(yPin);

  // Detectar el movimiento del joystick en las direcciones principales
  if (xVal > 600) {
    moverDerecha();  // Mover derecha si el valor de X es alto
  } else if (xVal < 400) {
    moverIzquierda();  // Mover izquierda si el valor de X es bajo
  } else if (yVal > 600) {
    moverAbajo();  // Mover abajo si el valor de Y es alto
  } else if (yVal < 400) {
    moverArriba();  // Mover arriba si el valor de Y es bajo
  } else if (xVal > 512 - deadZone && xVal < 512 + deadZone && yVal > 512 - deadZone && yVal < 512 + deadZone) {
    enReposo();  // El joystick está en reposo dentro de la zona muerta
  }
}

// Encender un solo LED en la posición especificada (columna, fila)
void encenderUnLed(int columna, int fila) {
  // Apagar todos los LEDs antes de encender uno nuevo
  apagarMatriz();

  // Activar la columna y fila deseadas para encender el LED específico
  digitalWrite(columnas[columna], HIGH);  // Activa la columna
  digitalWrite(filas[fila], LOW);         // Activa la fila
}

// Apagar todos los LEDs en la matriz
void apagarMatriz() {
  // Coloca todas las columnas en LOW y todas las filas en HIGH para apagar todos los LEDs
  for (int i = 0; i < 8; i++) {
    digitalWrite(columnas[i], LOW);  // Desactivar todas las columnas
    digitalWrite(filas[i], HIGH);    // Desactivar todas las filas
  }
}
