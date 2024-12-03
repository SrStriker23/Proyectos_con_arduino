#include <Servo.h>
#include <avr/wdt.h> // Librería para usar el Watchdog

// Definir pines
const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 5;
Servo servoMotor;

// Variables
int servoAngle = 0;
const int servoMin = 0;
const int servoMax = 180;
const int objectDistance = 60;
bool increasing = true;

// Variables para manejo del tiempo
unsigned long previousMillisServo = 0;
unsigned long previousMillisSensor = 0;
const unsigned long servoInterval = 5;  // Intervalo más rápido para mover el servo (ms)
const unsigned long sensorInterval = 50; // Intervalo para leer el sensor (ms)

// Prototipos de funciones
float getDistance(); // Función para medir la distancia instantánea
float getFilteredDistance(int samples = 5); // Función para medir distancia filtrada

// Configuración inicial
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  servoMotor.attach(6);
  servoMotor.write(servoMin);

  Serial.begin(9600);

  // Configurar el Watchdog con un tiempo de 4 segundos
  wdt_enable(WDTO_4S);
}

// Bucle principal
void loop() {
  unsigned long currentMillis = millis();

  // Mover el servo periódicamente
  if (currentMillis - previousMillisServo >= servoInterval) {
    previousMillisServo = currentMillis;

    if (increasing) {
      servoAngle++;
      if (servoAngle >= servoMax) {
        increasing = false;
      }
    } else {
      servoAngle--;
      if (servoAngle <= servoMin) {
        increasing = true;
      }
    }

    servoMotor.write(servoAngle);
  }

  // Leer el sensor periódicamente
  if (currentMillis - previousMillisSensor >= sensorInterval) {
    previousMillisSensor = currentMillis;

    float distance = getFilteredDistance(); // Obtener distancia filtrada

    if (distance != -1 && distance <= objectDistance) {
      Serial.print("Objeto detectado a ");
      Serial.print(distance);
      Serial.println(" cm");

      // Activar el buzzer
      digitalWrite(buzzerPin, HIGH);
      delay(100);
      digitalWrite(buzzerPin, LOW);
    }
  }

  // Reiniciar el Watchdog para evitar reinicios innecesarios
  wdt_reset();
}

// Función para medir distancia promedio (filtrada)
float getFilteredDistance(int samples) {
  float totalDistance = 0;
  int validSamples = 0;

  for (int i = 0; i < samples; i++) {
    float distance = getDistance();
    if (distance >= 3 && distance <= 400) { // Validar que la distancia esté dentro del rango confiable
      totalDistance += distance;
      validSamples++;
    }
    delay(10); // Pequeño retraso entre lecturas
  }

  if (validSamples > 0) {
    return totalDistance / validSamples; // Retorna el promedio de las muestras válidas
  } else {
    return -1; // Si no hay muestras válidas, retorna -1
  }
}

// Función para medir distancia usando el sensor ultrasónico
float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) {
    return -1;
  }

  float distance = duration * 0.034 / 2; // Velocidad del sonido: 343 m/s
  return distance;
}



