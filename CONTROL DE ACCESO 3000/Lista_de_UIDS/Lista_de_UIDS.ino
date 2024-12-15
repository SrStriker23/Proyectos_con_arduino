#include <SPI.h>      // incluye libreria bus SPI
#include <MFRC522.h>  // incluye libreria especifica para MFRC522

#define RST_PIN 9  // constante para referenciar pin de reset
#define SS_PIN 10  // constante para referenciar pin de slave select

MFRC522 mfrc522(SS_PIN, RST_PIN);  // crea objeto mfrc522 enviando pines de slave select y reset

byte LecturaUID[4];  // crea array para almacenar el UID leido

// Lista de UIDs permitidos (puedes añadir más si es necesario)
const byte UIDsPermitidos[][4] = {
  { 0x13, 0x92, 0x47, 0x14 },  // Llavero Vicente
  { 0x63, 0xA6, 0x2B, 0x28 },  // Tarjeta Vicente
  { 0xF3, 0x1F, 0x12, 0xAD },  // Tarjeta Franco
  { 0x64, 0x17, 0xCE, 0xCF },  // Llavero Franco
  { 0x17, 0x07, 0x55, 0x86 },  // Tarjeta Celeste
  { 0x8A, 0x18, 0xDE, 0x00 },  // Llavero Celeste
  { 0x26, 0xb4, 0x7E, 0x00 },  // Tarjeta Misael
  { 0x07, 0x6F, 0x1F, 0x86 },  // Llavero Misael
};

void setup() {
  Serial.begin(9600);       // inicializa comunicacion por monitor serie a 9600 bps
  SPI.begin();              // inicializa bus SPI
  mfrc522.PCD_Init();       // inicializa modulo lector
  Serial.println("Listo");  // Muestra texto Listo
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent())  // si no hay una tarjeta presente
    return;                              // retorna al loop esperando por una tarjeta

  if (!mfrc522.PICC_ReadCardSerial())  // si no puede obtener datos de la tarjeta
    return;                            // retorna al loop esperando por otra tarjeta

  Serial.print("UID:");                          // muestra texto UID:
  for (byte i = 0; i < mfrc522.uid.size; i++) {  // bucle recorre de a un byte por vez el UID
    if (mfrc522.uid.uidByte[i] < 0x10)           // si el byte leido es menor a 0x10
      Serial.print(" 0");                        // imprime espacio en blanco y numero cero
    else
      Serial.print(" ");                        // imprime un espacio en blanco
    Serial.print(mfrc522.uid.uidByte[i], HEX);  // imprime el byte del UID leido en hexadecimal
    LecturaUID[i] = mfrc522.uid.uidByte[i];     // almacena en array el byte del UID leido
  }

  Serial.print("\t");  // imprime un espacio de tabulacion

  if (esUIDPermitido(LecturaUID))        // verifica si el UID está en la lista de permitidos
    Serial.println("Acceso permitido");  // si está en la lista, muestra acceso permitido
  else
    Serial.println("No te conozco");  // si no está en la lista, muestra acceso denegado

  mfrc522.PICC_HaltA();  // detiene comunicacion con tarjeta
}

bool esUIDPermitido(byte lectura[]) {                                              // funcion para verificar si el UID está en la lista permitida
  for (byte i = 0; i < sizeof(UIDsPermitidos) / sizeof(UIDsPermitidos[0]); i++) {  // recorre cada UID en la lista
    bool coinciden = true;
    for (byte j = 0; j < 4; j++) {  // compara cada byte del UID
      if (lectura[j] != UIDsPermitidos[i][j]) {
        coinciden = false;
        break;
      }
    }
    if (coinciden) return true;  // si los 4 bytes coinciden, retorna verdadero
  }
  return false;  // si ninguno coincide, retorna falso
}
