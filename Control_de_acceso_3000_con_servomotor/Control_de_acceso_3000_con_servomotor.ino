#include <SPI.h>               // Biblioteca para comunicación SPI, usada por el lector RFID
#include <MFRC522.h>           // Biblioteca para manejar el lector RFID
#include <LiquidCrystal_I2C.h> // Biblioteca para manejar el LCD con interfaz I2C
#include <Servo.h>             // Biblioteca para manejar el servomotor

// Definición de pines
#define RST_PIN  9           // Pin de reinicio del lector RFID
#define SS_PIN  10           // Pin de selección del lector RFID
#define BUZZER_PIN 5         // Pin del buzzer
#define RED_LED_PIN 4        // Pin de la luz roja
#define GREEN_LED_PIN 3      // Pin de la luz verde
#define SERVO_PIN 6          // Pin del servomotor

MFRC522 mfrc522(SS_PIN, RST_PIN); // Crear instancia del lector RFID
LiquidCrystal_I2C lcd(0x27, 16, 2); // Crear instancia del LCD (dirección 0x27, 16 columnas x 2 filas)
Servo servoMotor;                  // Crear instancia del servomotor

// Lista de UIDs permitidos (cada UID es un arreglo de 4 bytes)
const byte UIDsPermitidos[][4] = {
  { 0x13, 0x92, 0x47, 0x14 },  // Ejemplo: Llavero Vicente
  { 0x63, 0xA6, 0x2B, 0x28 },  // Ejemplo: Tarjeta Vicente
  { 0xF3, 0x1F, 0x12, 0xAD },  // Ejemplo: Tarjeta Franco
  { 0x64, 0x17, 0xCE, 0xCF },  // Ejemplo: Llavero Franco
  { 0x17, 0x07, 0x55, 0x86 },  // Ejemplo: Tarjeta Celeste
  { 0x8A, 0x18, 0xDE, 0x00 },  // Ejemplo: Llavero Celeste
  { 0x26, 0xB4, 0x7E, 0x00 },  // Ejemplo: Tarjeta Misael
  { 0x07, 0x6F, 0x1F, 0x86 },  // Ejemplo: Llavero Misael
  { 0x7A, 0xEE, 0x17, 0x02 },  // Ejemplo: Tarjeta Brandon
  { 0x53, 0xBC, 0xB8, 0x2C },  // Ejemplo: Llavero Brandon
};

// Nombres asociados a cada UID en el mismo orden
const char* nombres[] = {
  "Vicente",
  "Vicente",
  "Franco",
  "Franco",
  "Celeste",
  "Celeste",
  "Misael",
  "Misael",
  "Brandon",
  "Brandon",
};

// Nivel asociado a cada UID en el mismo orden
const char* nivel[] = {
  "306",
  "302",
  "302",
  "302",
  "302",
  "302",
  "302",
  "302",
  "302",
  "302",
};

byte LecturaUID[4];                 // Almacena temporalmente el UID leído
int servoPosicionCerrado = 90;      // Posición del servomotor cuando está cerrado
int servoPosicionAbierto = 180;     // Posición del servomotor cuando está abierto

void setup() {
  Serial.begin(9600);              // Inicializar comunicación serie
  SPI.begin();                     // Inicializar comunicación SPI
  mfrc522.PCD_Init();              // Inicializar el lector RFID
  lcd.init();                      // Inicializar el LCD
  lcd.backlight();                 // Activar la luz de fondo del LCD

  // Configurar pines como salida
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  // Configurar el servomotor y establecer posición inicial
  servoMotor.attach(SERVO_PIN);
  servoMotor.write(servoPosicionCerrado);

  // Mostrar mensaje de inicio en el LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Inicializando...");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Escaner listo");
  Serial.println("Escáner listo");
}

void loop() {
  digitalWrite(RED_LED_PIN, LOW);  // Apagar luces al inicio del ciclo
  digitalWrite(GREEN_LED_PIN, LOW);

  // Verificar si hay una tarjeta presente
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return; // Si no hay tarjeta, salir del ciclo
  }

  // Leer el UID de la tarjeta
  Serial.print("UID leido: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    LecturaUID[i] = mfrc522.uid.uidByte[i]; // Guardar el UID leído
    Serial.print(mfrc522.uid.uidByte[i], HEX); // Mostrar en hexadecimal
    Serial.print(" ");
  }
  Serial.println();

  // Verificar si el UID es permitido
  int indice = buscaUID(LecturaUID);
  if (indice >= 0) { // UID encontrado en la lista
    Serial.print("Acceso permitido para: ");
    Serial.println(nombres[indice]);

    tone(BUZZER_PIN, 970, 150); // Sonido de éxito
    delay(100);
    tone(BUZZER_PIN, 1050, 120);

    digitalWrite(GREEN_LED_PIN, HIGH); // Encender luz verde

    // Mostrar datos en el LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Nombre:");
    lcd.print(nombres[indice]);
    lcd.setCursor(0, 1);
    lcd.print("Nivel:");
    lcd.print(nivel[indice]);

    servoMotor.write(servoPosicionAbierto); // Abrir acceso
    delay(5000); // Mantener abierto 5 segundos
    servoMotor.write(servoPosicionCerrado); // Cerrar acceso

  } else { // UID no encontrado
    Serial.println("Acceso denegado: No te conozco");

    tone(BUZZER_PIN, 500, 500); // Sonido de error
    digitalWrite(RED_LED_PIN, HIGH); // Encender luz roja

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ACCESO DENEGADO");
    delay(5000); // Mostrar mensaje por 5 segundos
  }

  // Esperar a que se retire la tarjeta
  while (mfrc522.PICC_IsNewCardPresent() || mfrc522.PICC_ReadCardSerial()) {
    delay(50);
  }

  mfrc522.PICC_HaltA(); // Detener comunicación con la tarjeta

  // Preparar para la siguiente lectura
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Escaner listo");
  delay(1000);
}

// Buscar el UID en la lista de permitidos
int buscaUID(byte lectura[]) {
  for (int i = 0; i < sizeof(UIDsPermitidos) / sizeof(UIDsPermitidos[0]); i++) {
    bool coincide = true;
    for (byte j = 0; j < 4; j++) {
      if (lectura[j] != UIDsPermitidos[i][j]) {
        coincide = false;
        break;
      }
    }
    if (coincide) return i; // Retorna el índice si encuentra coincidencia
  }
  return -1; // Retorna -1 si no encuentra el UID
}
