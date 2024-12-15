#include <Servo.h> // Librería para controlar el servomotor

// Configuración de pines
const int servoPin = 6;       // Pin donde está conectado el servomotor
const int trigPin = 9;        // Pin TRIG del sensor ultrasónico
const int echoPin = 10;       // Pin ECHO del sensor ultrasónico
const int buzzerPin = 5;      // Pin donde está conectado el buzzer

// Variables del servomotor
Servo servoMotor;  
int angle = 0;          // Ángulo actual del servomotor
int step = 1;           // Incremento o decremento del ángulo (dirección de movimiento)
const int minAngle = 0; // Ángulo mínimo del servo (límite izquierdo)
const int maxAngle = 180; // Ángulo máximo del servo (límite derecho)

// Variables de tiempo para control de intervalos
unsigned long previousMillisServo = 0;   // Tiempo anterior para el movimiento del servo
unsigned long previousMillisSensor = 0; // Tiempo anterior para la lectura del sensor
const unsigned long servoInterval = 20;   // Intervalo para mover el servo en milisegundos
const unsigned long sensorInterval = 50; // Intervalo para leer el sensor ultrasónico en milisegundos

// Configuración de distancia
const int detectionDistance = 20; // Distancia de detección en cm (15 cm)

// Función para obtener la distancia desde el sensor ultrasónico
float getDistance() {
  // Enviar un pulso TRIG de 10 microsegundos
  digitalWrite(trigPin, LOW);        // Asegurarse de que TRIG esté en bajo
  delayMicroseconds(2);              // Pausa para estabilidad
  digitalWrite(trigPin, HIGH);       // Generar pulso de inicio
  delayMicroseconds(10);             // Duración del pulso
  digitalWrite(trigPin, LOW);        // Detener el pulso

  // Medir el tiempo del eco (ECHO) en microsegundos
  long duration = pulseIn(echoPin, HIGH, 30000); // Máximo tiempo de espera: 30 ms
  if (duration == 0) {
    return -1; // Si no se detecta eco, retorna -1 (valor inválido)
  }

  // Calcular distancia en cm (velocidad del sonido = 343 m/s o 0.034 cm/μs)
  float distance = duration * 0.034 / 2; // Dividir entre 2 porque es ida y vuelta
  return distance;
}

// Función para limpiar el buffer serial (opcional)
void clearSerialBuffer() {
  // Leer y descartar cualquier dato acumulado en el buffer serial
  while (Serial.available()) {
    Serial.read();
  }
}

void setup() {
  // Configuración de pines
  pinMode(trigPin, OUTPUT); // Configurar TRIG como salida
  pinMode(echoPin, INPUT);  // Configurar ECHO como entrada
  pinMode(buzzerPin, OUTPUT); // Configurar buzzer como salida

  servoMotor.attach(servoPin); // Asociar el servomotor al pin 6
  servoMotor.write(angle);     // Inicializar el servo en el ángulo 0

  Serial.begin(9600); // Iniciar comunicación serial a 9600 baudios
}

void loop() {
  unsigned long currentMillis = millis(); // Obtener el tiempo actual

  // Movimiento del servomotor en intervalos
  if (currentMillis - previousMillisServo >= servoInterval) {
    previousMillisServo = currentMillis; // Actualizar tiempo anterior

    // Actualizar el ángulo del servomotor
    angle += step; // Incrementar o decrementar el ángulo

    // Cambiar la dirección del movimiento al alcanzar los límites
    if (angle >= maxAngle || angle <= minAngle) {
      step = -step; // Invertir la dirección
    }

    // Mover el servomotor al nuevo ángulo
    servoMotor.write(angle);
  }

  // Leer el sensor ultrasónico en intervalos
  if (currentMillis - previousMillisSensor >= sensorInterval) {
    previousMillisSensor = currentMillis; // Actualizar tiempo anterior

    float distance = getDistance(); // Obtener la distancia medida

    // Verificar si la distancia está dentro del rango de detección
    if (distance != -1 && distance <= detectionDistance) {
      Serial.print("Objeto detectado a ");
      Serial.print(distance);
      Serial.println(" cm");

      // Activar el buzzer si se detecta un objeto
      digitalWrite(buzzerPin, HIGH); // Encender el buzzer
      delay(100);                    // Mantenerlo encendido 100 ms
      digitalWrite(buzzerPin, LOW);  // Apagar el buzzer
    }
  }

  // Limpiar el buffer serial para evitar saturación
  clearSerialBuffer();
}


