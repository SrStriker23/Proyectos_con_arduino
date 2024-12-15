#include <Servo.h> // Librería para controlar el servomotor

// Configuración de pines
const int servoPin = 6;       // Pin del servomotor
const int trigPin = 9;        // Pin TRIG del sensor ultrasónico
const int echoPin = 10;       // Pin ECHO del sensor ultrasónico
const int buzzerPin = 5;      // Pin del buzzer

// Variables del servomotor
Servo servoMotor;  
int angle = 0;          // Ángulo actual del servo
int step = 1;           // Incremento o decremento del ángulo
const int minAngle = 0; // Ángulo mínimo
const int maxAngle = 180; // Ángulo máximo

// Variables de tiempo
unsigned long previousMillisServo = 0;
unsigned long previousMillisSensor = 0;
const unsigned long servoInterval = 20;   // Intervalo para mover el servo (ms)
const unsigned long sensorInterval = 50; // Intervalo para leer el sensor (ms)

// Configuración de distancia
const int detectionDistance = 20; // Distancia de detección en cm

// Función para obtener la distancia desde el sensor ultrasónico
float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // Tiempo en microsegundos
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

  servoMotor.attach(servoPin); // Conectar el servomotor
  servoMotor.write(angle);     // Inicializar ángulo del servo

  Serial.begin(9600); // Iniciar comunicación serial
}

void loop() {
  unsigned long currentMillis = millis();

  // Movimiento del servomotor
  if (currentMillis - previousMillisServo >= servoInterval) {
    previousMillisServo = currentMillis;

    // Actualizar el ángulo del servo
    angle += step;

    // Cambiar dirección del movimiento si se alcanzan los límites
    if (angle >= maxAngle || angle <= minAngle) {
      step = -step;
    }

    // Mover el servomotor al nuevo ángulo
    servoMotor.write(angle);
  }

  // Leer el sensor ultrasónico
  if (currentMillis - previousMillisSensor >= sensorInterval) {
    previousMillisSensor = currentMillis;

    float distance = getDistance(); // Obtener la distancia medida

    // Verificar si la distancia está dentro del rango de detección
    if (distance != -1 && distance <= detectionDistance) {
      Serial.print("Objeto detectado a ");
      Serial.print(distance);
      Serial.println(" cm");

      // Activar el buzzer
      digitalWrite(buzzerPin, HIGH);
      delay(100);
      digitalWrite(buzzerPin, LOW);
    }
  }
}
