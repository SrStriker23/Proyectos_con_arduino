#include <Keypad.h>

int buzzer = 13;
int ledrojo = 8;
int ledverde = 9;
char usuario[5];
char clave[5] = "AABA";
int entrada = 0;

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  { 'A', 'B', '-', '-' },
  { '-', '-', '-', '-' },
  { '-', '-', '-', '-' },
  { '-', '-', '-', '-' }
};
byte rowPins[ROWS] = { 3, 2, 1, 0 };
byte colPins[COLS] = { 7, 6, 5, 4 };


Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(ledrojo, OUTPUT);
  pinMode(ledverde, OUTPUT);
}

void loop() {
  char customKey = customKeypad.getKey();

  digitalWrite(ledrojo, HIGH);

  if (customKey) {
    Serial.println(customKey);
    usuario[entrada] = customKey;


    if (usuario[entrada] == clave[entrada]) {
      tone(buzzer, 1000, 200);
      entrada++;

      if (entrada == 4) {
        digitalWrite(ledverde, HIGH);
        digitalWrite(ledrojo, LOW);
        tone(buzzer, 970, 150);
        delay(100);
        tone(buzzer, 1050, 120);
        delay(15000);
        digitalWrite(ledverde, LOW);
        entrada = 0;
      }

    } else {

      digitalWrite(ledrojo, HIGH);
      tone(buzzer, 500, 500);
      delay(1000);
      digitalWrite(ledrojo, LOW);
      entrada = 0;
      memset(usuario, 0, sizeof(usuario));
    }
  }
}
