#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

#define RST_PIN  9
#define SS_PIN  10
#define BUZZER_PIN 5       // Pin del buzzer
#define RED_LED_PIN 4      // Pin de la luz roja
#define GREEN_LED_PIN 3    // Pin de la luz verde

MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Lista de UIDs permitidos
const byte UIDsPermitidos[][4] = {
  { 0x13, 0x92, 0x47, 0x14 },  // Llavero Vicente
  { 0x63, 0xA6, 0x2B, 0x27 },  // Tarjeta Vicente
  { 0xF3, 0x1F, 0x12, 0xAD },  // Tarjeta Franco
  { 0x64, 0x17, 0xCE, 0xCF },  // Llavero Franco
  { 0x17, 0x07, 0x55, 0x86 },  // Tarjeta Celeste
  { 0x8A, 0x18, 0xDE, 0x00 },  // Llavero Celeste
  { 0x26, 0xb4, 0x7E, 0x00 },  // Tarjeta Misael
  { 0x07, 0x6F, 0x1F, 0x86 },  // Llavero Misael
};

const char* nombres[] = {
  "Vicente",
  "Vicente",
  "Franco",
  "Franco",
  "Celeste",
  "Celeste",
  "Misael",
  "Misael"
};

const char* nivel[] = {
  "302",
  "302",
  "302",
  "302",
  "302",
  "302",
  "302",
  "302"
};

byte LecturaUID[4];

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.init();
  lcd.backlight();
  
  // Mensaje de inicio en el LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Inicializando...");
  delay(2000);  // Mostrar el mensaje de inicio durante 2 segundos
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Escaner listo");
  Serial.println("Escáner listo");
  delay(2000);  // Mantener mensaje en pantalla por 2 segundos
}

void loop() {
  digitalWrite(RED_LED_PIN, LOW);    // Apagar luces al iniciar el ciclo
  digitalWrite(GREEN_LED_PIN, LOW);

  // Verificar si hay una tarjeta presente
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Leer el UID de la tarjeta y mostrarlo en el monitor serie
  Serial.print("UID leido: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    LecturaUID[i] = mfrc522.uid.uidByte[i];
    Serial.print(mfrc522.uid.uidByte[i], HEX); // Mostrar UID en hexadecimal
    Serial.print(" ");
  }
  Serial.println();

  // Verificar si el UID coincide con uno permitido
  int indice = buscaUID(LecturaUID);
  if (indice >= 0) {
    // Si el UID es válido, emitir tono de éxito y encender luz verde
    Serial.print("Acceso permitido para: ");
    Serial.println(nombres[indice]);

    tone(BUZZER_PIN, 970, 150); 
    delay(100);
    tone(BUZZER_PIN, 1050, 120);
    
    digitalWrite(GREEN_LED_PIN, HIGH);  // Encender luz verde

    // Mostrar mensaje en el LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Nombre:");
    lcd.print(nombres[indice]);
    lcd.setCursor(0, 1);
    lcd.print("Nivel:");
    lcd.print(nivel[indice]);

    delay(5000);  // Mostrar mensaje durante 5 segundos
    lcd.clear();  // Limpiar pantalla después de 5 segundos
  } else {
    // Emitir tono de error y encender luz roja
    Serial.println("Acceso denegado: No te conozco");

    tone(BUZZER_PIN, 500, 500);  // Sonido de incorrecto en el buzzer
    digitalWrite(RED_LED_PIN, HIGH);  // Encender luz roja

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ACCESO DENEGADO");

    delay(5000);  // Mantener mensaje de acceso denegado durante 5 segundos
    lcd.clear();  // Limpiar pantalla después de 5 segundos
  }

  // Espera a que la tarjeta sea retirada antes de continuar
  while (mfrc522.PICC_IsNewCardPresent() || mfrc522.PICC_ReadCardSerial()) {
    delay(50);
  }

  mfrc522.PICC_HaltA();
  
  // Mensaje de "Escáner preparado" después de cada lectura
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Escaner listo");
  Serial.println("Escaner listo");
  delay(1000);  // Mantener el mensaje por 1 segundo antes de reiniciar el ciclo
}

// Función para buscar el UID en la lista de permitidos
int buscaUID(byte lectura[]) {
  for (int i = 0; i < sizeof(UIDsPermitidos) / sizeof(UIDsPermitidos[0]); i++) {
    bool coincide = true;
    for (byte j = 0; j < 4; j++) {
      if (lectura[j] != UIDsPermitidos[i][j]) {
        coincide = false;
        break;
      }
    }
    if (coincide) return i;
  }
  return -1;
}

