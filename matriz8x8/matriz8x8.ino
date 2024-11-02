// Pines de columnas y filas basados en la tabla de conexión
int columnas[] = { 2, 3, 4, 5, 6, 7, 8, 9 };       // Pines de las columnas en el Arduino Uno
int filas[] = { 10, 11, 12, 13, A0, A1, A2, A3 };  // Pines de las filas en el Arduino Uno
//funciones para crear las figuras
void left() {
  encenderUnLed(3, 0);
  encenderUnLed(4, 0);

  encenderUnLed(2, 1);
  encenderUnLed(3, 1);

  encenderUnLed(1, 2);
  encenderUnLed(2, 2);

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
void stop() {
  encenderUnLed(3, 0);
  encenderUnLed(4, 0);

  encenderUnLed(3, 1);
  encenderUnLed(4, 1);

  encenderUnLed(3, 2);
  encenderUnLed(4, 2);

  encenderUnLed(3, 3);
  encenderUnLed(4, 3);

  encenderUnLed(3, 5);
  encenderUnLed(4, 5);
  encenderUnLed(2, 6);
  encenderUnLed(3, 6);
  encenderUnLed(4, 6);
  encenderUnLed(5, 6);
  encenderUnLed(3, 7);
  encenderUnLed(4, 7);
}
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
void setup() {
  // Configurar todos los pines de filas y columnas como salida
  for (int i = 0; i < 8; i++) {
    pinMode(columnas[i], OUTPUT);
    pinMode(filas[i], OUTPUT);

    // Inicialmente, apagamos todos los LEDs
    // Para eso, ponemos todas las columnas en HIGH y las filas en LOW
    digitalWrite(columnas[i], HIGH);  // Apagar columnas
    digitalWrite(filas[i], LOW);      // Apagar filas
  }
}

void loop() {
  left();
}

// Función para encender un solo LED en una posición específica (columna, fila)
void encenderUnLed(int columna, int fila) {
  // Primero apagamos todos los LEDs para evitar que otros LEDs se mantengan encendidos
  apagarMatriz();

  // Activamos solo el LED en la columna y fila deseada
  // Para encender un LED específico, ponemos la columna en HIGH y la fila en LOW
  digitalWrite(columnas[columna], HIGH);  // Activa columna deseada en HIGH
  digitalWrite(filas[fila], LOW);         // Activa fila deseada en LOW
}

// Función para apagar toda la matriz
void apagarMatriz() {
  // Para asegurarnos de que todos los LEDs están apagados,
  // ponemos todas las columnas en LOW y todas las filas en HIGH.
  for (int i = 0; i < 8; i++) {
    digitalWrite(columnas[i], LOW);  // Apagar todas las columnas (LOW)
    digitalWrite(filas[i], HIGH);    // Apagar todas las filas (HIGH)
  }
}
