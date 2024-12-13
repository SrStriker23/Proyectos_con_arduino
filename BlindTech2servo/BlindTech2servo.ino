#include <Servo.h> // Librería para controlar los servomotores

// Configuración de pines
const int servo1Pin = 6;      // Pin del primer servomotor
const int servo2Pin = 11;     // Pin del segundo servomotor
const int trigPin = 9;        // Pin TRIG del sensor ultrasónico
const int echoPin = 10;       // Pin ECHO del sensor ultrasónico
const int buzzerPin = 5;      // Pin del buzzer

// Variables de los servomotores
Servo servo1;
Servo servo2;
int angle1 = 0;          // Ángulo actual del primer servomotor
int angle2 = 0;          // Ángulo actual del segundo servomotor
int step1 = 1;           // Incremento del ángulo para el primer servomotor
int step2 = 1;           // Incremento del ángulo para el segundo servomotor
const int minAngle = 0;  // Ángulo mínimo
const int maxAngle = 180; // Ángulo máximo

// Variables de tiempo para control de intervalos
unsigned long previousMillisServo1 = 0;  // Tiempo anterior para el movimiento del servo1
unsigned long previousMillisServo2 = 0;  // Tiempo anterior para el movimiento del servo2
unsigned long previousMillisSensor = 0; // Tiempo anterior para la lectura del sensor
unsigned long previousMillisBuzzer = 0; // Tiempo anterior para el manejo del buzzer
const unsigned long servo1Interval = 20;  // Intervalo del primer servomotor (ms)
const unsigned long servo2Interval = 40;  // Intervalo del segundo servomotor (ms) - Más lento
const unsigned long sensorInterval = 50; // Intervalo para leer el sensor ultrasónico (ms)
const unsigned long buzzerDuration = 100; // Duración del encendido del buzzer (ms)

// Configuración de distancia
const int detectionDistance = 20; // Distancia de detección en cm

// Estado del buzzer
bool buzzerState = false;

// Función para obtener la distancia desde el sensor ultrasónico
float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // Máximo tiempo de espera: 30 ms
  if (duration == 0) {
    return -1; // Si no se detecta eco, retorna -1
  }

  float distance = duration * 0.034 / 2; // Calcular distancia en cm
  return distance;
}

void setup() {
  // Configuración de pines
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  // Asociar los servomotores a sus pines
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);

  // Inicializar los servomotores en el ángulo mínimo
  servo1.write(minAngle);
  servo2.write(minAngle);

  Serial.begin(9600); // Iniciar comunicación serial
}

void loop() {
  unsigned long currentMillis = millis();

  // Movimiento del primer servomotor (más rápido)
  if (currentMillis - previousMillisServo1 >= servo1Interval) {
    previousMillisServo1 = currentMillis;

    // Actualizar el ángulo del primer servomotor
    angle1 += step1;

    // Cambiar dirección al alcanzar límites
    if (angle1 >= maxAngle || angle1 <= minAngle) {
      step1 = -step1;
    }

    // Mover el primer servomotor al nuevo ángulo
    servo1.write(angle1);
  }

  // Movimiento del segundo servomotor (más lento)
  if (currentMillis - previousMillisServo2 >= servo2Interval) {
    previousMillisServo2 = currentMillis;

    // Actualizar el ángulo del segundo servomotor
    angle2 += step2;

    // Cambiar dirección al alcanzar límites
    if (angle2 >= maxAngle || angle2 <= minAngle) {
      step2 = -step2;
    }

    // Mover el segundo servomotor al nuevo ángulo
    servo2.write(angle2);
  }

  // Leer el sensor ultrasónico en intervalos
  if (currentMillis - previousMillisSensor >= sensorInterval) {
    previousMillisSensor = currentMillis;

    float distance = getDistance(); // Obtener la distancia medida

    if (distance != -1 && distance <= detectionDistance) {
      Serial.print("Objeto detectado a ");
      Serial.print(distance);
      Serial.println(" cm");

      // Activar el buzzer si se detecta un objeto
      buzzerState = true; // Marcar el estado del buzzer como activo
      previousMillisBuzzer = currentMillis; // Registrar el tiempo actual
    }
  }

  // Control no bloqueante del buzzer
  if (buzzerState && (currentMillis - previousMillisBuzzer < buzzerDuration)) {
    digitalWrite(buzzerPin, HIGH); // Mantener el buzzer encendido
  } else {
    digitalWrite(buzzerPin, LOW); // Apagar el buzzer
    buzzerState = false;          // Restablecer el estado del buzzer
  }
}
