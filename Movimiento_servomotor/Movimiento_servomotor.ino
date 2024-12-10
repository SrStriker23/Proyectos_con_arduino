#include <Servo.h> // Librería para controlar el servomotor

Servo servoMotor;  // Crear objeto servo
const int servoPin = 6; // Pin donde está conectado el servomotor

// Variables para el movimiento del servo
int angle = 0;          // Ángulo actual del servo
int step = 1;           // Incremento o decremento del ángulo
const int minAngle = 0; // Ángulo mínimo
const int maxAngle = 180; // Ángulo máximo
unsigned long previousMillis = 0;
const unsigned long interval = 20; // Intervalo de tiempo para el movimiento (ms)

void setup() {
  servoMotor.attach(servoPin); // Conectar el servo al pin
  servoMotor.write(angle);     // Inicializar en el ángulo inicial
}

void loop() {
  unsigned long currentMillis = millis();

  // Movimiento del servo en intervalos
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Actualizar el ángulo del servo
    angle += step;

    // Invertir la dirección del movimiento si alcanza los límites
    if (angle >= maxAngle || angle <= minAngle) {
      step = -step;
    }

    // Mover el servo al nuevo ángulo
    servoMotor.write(angle);
  }
}
