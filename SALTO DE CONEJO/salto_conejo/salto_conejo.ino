
int luz1 = 1;
int luz2 = 2;
int luz3 = 3;
int luz4 = 4;
int luz5 = 5;
int luz6 = 6;

int tiempo=500;

void setup() {
  pinMode(luz1,OUTPUT);
  pinMode(luz2,OUTPUT);
  pinMode(luz3,OUTPUT);
  pinMode(luz4,OUTPUT);
  pinMode(luz5,OUTPUT);
  pinMode(luz6,OUTPUT);

}

void loop() {
  digitalWrite(luz1,HIGH);
  delay(tiempo);
  digitalWrite(luz1,LOW);
  digitalWrite(luz2,HIGH);
  delay(tiempo);
  digitalWrite(luz2,LOW);
  digitalWrite(luz3,HIGH);
  delay(tiempo);
  digitalWrite(luz3,LOW);
  digitalWrite(luz4,HIGH);
  delay(tiempo);
  digitalWrite(luz4,LOW);
  digitalWrite(luz5,HIGH);
  delay(tiempo);
  digitalWrite(luz5,LOW);
  digitalWrite(luz6,HIGH); //PRIMER CICLO
  delay(tiempo);
  digitalWrite(luz1,HIGH);
  delay(tiempo);
  digitalWrite(luz1,LOW);
  digitalWrite(luz2,HIGH);
  delay(tiempo);
  digitalWrite(luz2,LOW);
  digitalWrite(luz3,HIGH);
  delay(tiempo);
  digitalWrite(luz3,LOW);
  digitalWrite(luz4,HIGH);
  delay(tiempo);
  digitalWrite(luz4,LOW);
  digitalWrite(luz5,HIGH); //SEGUNDO CICLO
  delay(tiempo);


  digitalWrite(luz1,HIGH);
  delay(tiempo);
  digitalWrite(luz1,LOW);
  digitalWrite(luz2,HIGH);
  delay(tiempo);
  digitalWrite(luz2,LOW);
  digitalWrite(luz3,HIGH);
  delay(tiempo);
  digitalWrite(luz3,LOW);
  digitalWrite(luz4,HIGH); //TERCER CICLO
  delay(tiempo);
  

  digitalWrite(luz1,HIGH);
  delay(tiempo);
  digitalWrite(luz1,LOW);
  digitalWrite(luz2,HIGH);
  delay(tiempo);
  digitalWrite(luz2,LOW);
  digitalWrite(luz3,HIGH); // CUARTO CICLO
  delay(tiempo);
  

  digitalWrite(luz1,HIGH);
  delay(tiempo);
  digitalWrite(luz1,LOW);
  digitalWrite(luz2,HIGH); //QUINTO CICLO
  delay(tiempo);
  

  digitalWrite(luz1,HIGH); //SEXTO CICLO
  delay(1000);

  digitalWrite(luz1,LOW);
  delay(tiempo);
  
  digitalWrite(luz2,LOW);
  digitalWrite(luz1,HIGH);
  delay(tiempo);

  digitalWrite(luz1,LOW);
  digitalWrite(luz3,LOW);
  digitalWrite(luz2,HIGH);
  delay(tiempo);
  digitalWrite(luz2,LOW);
  digitalWrite(luz1,HIGH);
  delay(tiempo);

  digitalWrite(luz1,LOW);
  digitalWrite(luz4,LOW);
  digitalWrite(luz3,HIGH);
  delay(tiempo);
  digitalWrite(luz3,LOW);
  digitalWrite(luz2,HIGH);
  delay(tiempo);
  digitalWrite(luz2,LOW);
  digitalWrite(luz1,HIGH);
  delay(tiempo);

  digitalWrite(luz1,LOW);
  digitalWrite(luz5,LOW);
  digitalWrite(luz4,HIGH);
  delay(tiempo);
  digitalWrite(luz4,LOW);
  digitalWrite(luz3,HIGH);
  delay(tiempo);
  digitalWrite(luz3,LOW);
  digitalWrite(luz2,HIGH);
  delay(tiempo);
  digitalWrite(luz2,LOW);
  digitalWrite(luz1,HIGH);
  delay(tiempo);

  digitalWrite(luz1,LOW);
  digitalWrite(luz6,LOW);
  digitalWrite(luz5,HIGH);
  delay(tiempo);
  digitalWrite(luz5,LOW);
  digitalWrite(luz4,HIGH);
  delay(tiempo);
  digitalWrite(luz4,LOW);
  digitalWrite(luz3,HIGH);
  delay(tiempo);
  digitalWrite(luz3,LOW);
  digitalWrite(luz2,HIGH);
  delay(tiempo);
  digitalWrite(luz2,LOW);
  digitalWrite(luz1,HIGH);
  delay(tiempo);

  digitalWrite(luz1,LOW);
  delay(1000);







  




       


  
  
}
