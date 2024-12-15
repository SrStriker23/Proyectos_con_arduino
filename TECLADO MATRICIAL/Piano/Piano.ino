#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 4; 

// Definir las notas (frecuencias) para cada tecla del piano
int noteC = 261;  // Do
int noteD = 294;  // Re
int noteE = 329;  // Mi
int noteF = 349;  // Fa
int noteG = 392;  // Sol
int noteA = 440;  // La
int noteB = 493;  // Si
int noteHighC = 523; // Do agudo

// Definir los pines para el buzzer y el LED
int buzzer = 12;
int led = 13;

// Teclado matricial
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', '4'},
  {'5', '6', '7', '8'},
  {'9', '0', 'A', 'B'},
  {'C', 'D', '*', '#'}
};

byte rowPins[ROWS] = {5, 4, 3, 2}; // Pines para las filas del teclado
byte colPins[COLS] = {8, 9, 10, 11}; // Pines para las columnas del teclado

// Crear el objeto Keypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  char customKey = customKeypad.getKey();  // Obtener la tecla presionada

  if (customKey) {
    // Mostrar la tecla presionada en el monitor serial
    Serial.println(customKey);
    
    // Tocar diferentes notas según la tecla presionada
    switch (customKey) {
      case '1': tone(buzzer, noteC, 300); break;    // Do
      case '2': tone(buzzer, noteD, 300); break;    // Re
      case '3': tone(buzzer, noteE, 300); break;    // Mi
      case '4': tone(buzzer, noteF, 300); break;    // Fa
      case '5': tone(buzzer, noteG, 300); break;    // Sol
      case '6': tone(buzzer, noteA, 300); break;    // La
      case '7': tone(buzzer, noteB, 300); break;    // Si
      case '8': tone(buzzer, noteHighC, 300); break; // Do agudo

      case '9': tone(buzzer, noteC * 2, 300); break; // Octava superior
      case '0': tone(buzzer, noteC / 2, 300); break; // Octava inferior
      case 'A': tone(buzzer, noteF, 300); break;    // Otra nota Fa
      case 'B': tone(buzzer, noteE, 300); break;    // Otra nota Mi
      case 'C': tone(buzzer, noteD, 300); break;    // Otra nota Re
      case 'D': tone(buzzer, noteC, 300); break;    // Otra nota Do
      case '*': tone(buzzer, 100, 300); break;      // Tono muy bajo
      case '#': tone(buzzer, 2000, 300); break;     // Tono muy alto
      default: noTone(buzzer); break;  // Detener el tono si no hay tecla válida
    }
    delay(100);  // Espera entre notas
  }
}

