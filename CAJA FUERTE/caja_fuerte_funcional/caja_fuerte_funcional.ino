
#include <Keypad.h>
int buzzer = 13;
int ledrojo = 8;
int ledverde = 9;
char usuario[5];
char clave[5] = "AABA";
int entrada = 0;
int contador = 0;
const byte ROWS = 4;  //four rows
const byte COLS = 4;  //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  { 'A', 'B', '-', '-' },
  { '-', '-', '-', '-' },
  { '-', '-', '-', '-' },
  { '-', '-', '-', '-' }
};
byte rowPins[ROWS] = { 3, 2, 1, 0 };  //connect to the row pinouts of the keypad
byte colPins[COLS] = { 7, 6, 5, 4 };  //connect to the column pinouts of the keypad


//initialize an instance of class NewKeypad
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
  }
  if (customKey) {
    usuario[entrada] = customKey;
    tone(buzzer, 1000, 200);
    entrada++;
    contador++;
  }
  if (contador == 4) {
    if (!strcmp(usuario, clave)) {
      entrada = 0;
      digitalWrite(ledrojo, LOW);
      digitalWrite(ledverde, HIGH);
      delay(300);
      tone(buzzer, 970, 150);
      delay(100);
      tone(buzzer, 1050, 120);
      delay(3000);
      digitalWrite(ledverde, LOW);
      contador = 0;
    }else{
      
    }
  }
}
