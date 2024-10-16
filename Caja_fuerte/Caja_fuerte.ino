#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
char password[5];
char match[5] = "5242";  // Contraseña correcta
char off[5] = "0000";    // Contraseña de desbloqueo (apagar)
byte enter = 0;
int led = 13;
int on = 0;
int buzzer = 12;
int attempts = 0;     // Contador de intentos fallidos
int maxAttempts = 3;  // Máximo de intentos permitidos
bool locked = false;  // Estado de bloqueo

// Teclado matricial
char hexaKeys[ROWS][COLS] = {
  { '0', '1', '2', '3' },
  { '4', '5', '6', '7' },
  { '8', '9', 'A', 'B' },
  { 'C', 'D', 'E', 'F' }
};
byte rowPins[ROWS] = { 5, 4, 3, 2 };    //connect to the row pinouts of the keypad
byte colPins[COLS] = { 8, 9, 10, 11 };  //connect to the column pinouts of the keypad

// Crear el objeto Keypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  char customKey = customKeypad.getKey();

  if (locked) {  // Si está bloqueado, solo aceptar la contraseña de desbloqueo
    if (customKey) {
      password[enter] = customKey;
      tone(buzzer, 1000, 200);
      enter++;
      on++;
    }

    if (on == 4) {
      if (!strcmp(password, off)) {  // Desbloquear con la contraseña de apagar
        digitalWrite(led, LOW);
        enter = 0;
        attempts = 0;    // Reiniciar los intentos
        locked = false;  // Desbloquear el sistema
        delay(300);
        tone(buzzer, 970, 150);
        delay(100);
        tone(buzzer, 900, 120);
      } else {
        enter = 0;  // Si no es la contraseña de desbloqueo, reiniciar
        delay(300);
        tone(buzzer, 1500, 1000);  // Tono de error
      }
      on = 0;
    }
    return;  // No permitir más interacción si está bloqueado
  }

  if (customKey) {  // Si no está bloqueado, aceptar entradas normalmente
    password[enter] = customKey;
    tone(buzzer, 1000, 200);
    enter++;
    on++;
  }

  if (on == 4) {                           // Si se han ingresado 4 caracteres
    if (!strcmp(password, match)) {        // Si la contraseña es correcta
      digitalWrite(led, HIGH);             // Enciende el LED
      Serial.println("Acceso permitido");  // Mensaje en el monitor serial
      enter = 0;
      attempts = 0;  // Reiniciar los intentos si es correcta
      delay(300);
      tone(buzzer, 970, 150);
      delay(100);
      tone(buzzer, 1050, 120);
    } else {                          // Contraseña incorrecta
      attempts++;                     // Incrementar contador de intentos fallidos
      if (attempts >= maxAttempts) {  // Si se excede el número de intentos
        locked = true;                // Bloquear el sistema
        Serial.println("Sistema bloqueado. Ingrese la contraseña de apagado para desbloquear.");
        delay(300);
        tone(buzzer, 1500, 1000);  // Tono de error largo
      } else {
        Serial.println("Contraseña incorrecta. Intentos restantes: " + String(maxAttempts - attempts));
        delay(300);
        tone(buzzer, 1500, 1000);  // Tono de error
      }
    }
    enter = 0;  // Reiniciar el contador de entrada
    on = 0;     // Reiniciar el contador de caracteres ingresados
  }
}
