#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN  9
#define SS_PIN  10

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Acerque la tarjeta para escribir su nombre...");
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial())
    return;

  // Autenticación
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF; // Clave predeterminada

  byte nombre[] = "VicenteJaramillo"; // Cambia "Usuario1" por el nombre deseado (máx. 16 caracteres)

  // Intentar autenticarse en el bloque 4 antes de escribir
  MFRC522::StatusCode status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(mfrc522.uid));

  if (status != MFRC522::STATUS_OK) {
    Serial.print("Error en autenticación: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    mfrc522.PICC_HaltA();
    return;
  }

  // Intentar escribir en el bloque 4 después de autenticarse
  status = mfrc522.MIFARE_Write(4, nombre, 16);

  if (status == MFRC522::STATUS_OK) {
    Serial.println("Nombre escrito en la tarjeta correctamente");
  } else {
    Serial.print("Error al escribir: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
  }

  // Detener la comunicación con la tarjeta y esperar otra lectura
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1(); // Termina la autenticación
  delay(1000);
}

