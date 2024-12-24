#include <Servo.h> // Librería para controlar los servomotores

// Configuración de pines
const int servo1Pin = 6;      // Pin del primer servomotor
const int servo2Pin = 11;     // Pin del segundo servomotor
const int trigPin = 9;        // Pin TRIG del sensor ultrasónico
const int echoPin = 10;       // Pin ECHO del sensor ultrasónico
const int buzzerPin = 5;      // Pin del buzzer
const int buttonPin = 4;      // Pin del botón

// Variables de los servomotores
Servo servo1;
Servo servo2;
int angle1 = 35;
int angle2 = 60;
int step1 = 1;
int step2 = 1;
const int minAngle1 = 35;
const int maxAngle1 = 145;
const int minAngle2 = 60;
const int maxAngle2 = 120;

// Variables de tiempo
unsigned long previousMillisServo1 = 0;
unsigned long previousMillisServo2 = 0;
unsigned long previousMillisSensor = 0;
unsigned long previousMillisBuzzer = 0;
const unsigned long servo1Interval = 20;
const unsigned long servo2Interval = 40;
const unsigned long sensorInterval = 50;
const unsigned long buzzerDuration = 100;

// Configuración de distancia
const int detectionDistance = 40;

// Estado del buzzer
bool buzzerState = false;

// Estado del botón y del sistema
bool systemState = false;  // Estado actual del sistema: apagado inicialmente
bool lastButtonState = HIGH; // Estado anterior del botón (para detectar flancos)

// Función para obtener la distancia desde el sensor ultrasónico
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

  float distance = duration * 0.034 / 2;
  return distance;
}

// Función para emitir un sonido específico con el buzzer
void playBuzzerSound(bool turnOn) {
  if (turnOn) {
    // Sonido de encendido: dos pitidos cortos
    for (int i = 0; i < 2; i++) {
      digitalWrite(buzzerPin, HIGH);
      delay(100);
      digitalWrite(buzzerPin, LOW);
      delay(100);
    }
  } else {
    // Sonido de apagado: un pitido largo
    digitalWrite(buzzerPin, HIGH);
    delay(300);
    digitalWrite(buzzerPin, LOW);
  }
}

void setup() {
  // Configuración de pines
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Configuración de botón como pull-up

  // Asociar los servomotores a sus pines
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);

  // Inicializar servos
  servo1.write(minAngle1);
  servo2.write(minAngle2);

  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();

  // Lectura del botón para alternar el estado del sistema
  bool buttonState = digitalRead(buttonPin);
  if (buttonState == LOW && lastButtonState == HIGH) { // Detectar flanco descendente
    systemState = !systemState; // Alternar el estado del sistema
    Serial.print("Sistema ");
    Serial.println(systemState ? "ENCENDIDO" : "APAGADO");

    // Emitir sonido de encendido o apagado
    playBuzzerSound(systemState);

    delay(200); // Pequeña pausa para evitar rebotes
  }
  lastButtonState = buttonState;

  // Si el sistema está apagado, apagar servos y buzzer
  if (!systemState) {
    servo1.write(minAngle1);
    servo2.write(minAngle2);
    digitalWrite(buzzerPin, LOW);
    return; // Salir del loop para no ejecutar el resto del código
  }

  // Movimiento del primer servomotor
  if (currentMillis - previousMillisServo1 >= servo1Interval) {
    previousMillisServo1 = currentMillis;
    angle1 += step1;
    if (angle1 >= maxAngle1 || angle1 <= minAngle1) step1 = -step1;
    servo1.write(angle1);
  }

  // Movimiento del segundo servomotor
  if (currentMillis - previousMillisServo2 >= servo2Interval) {
    previousMillisServo2 = currentMillis;
    angle2 += step2;
    if (angle2 >= maxAngle2 || angle2 <= minAngle2) step2 = -step2;
    servo2.write(angle2);
  }

  // Lectura del sensor ultrasónico
  if (currentMillis - previousMillisSensor >= sensorInterval) {
    previousMillisSensor = currentMillis;
    float distance = getDistance();
    if (distance != -1 && distance <= detectionDistance) {
      Serial.print("Objeto detectado a ");
      Serial.print(distance);
      Serial.println(" cm");

      buzzerState = true;
      previousMillisBuzzer = currentMillis;
    }
  }

  // Control no bloqueante del buzzer
  if (buzzerState && (currentMillis - previousMillisBuzzer < buzzerDuration)) {
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
    buzzerState = false;
  }
}
