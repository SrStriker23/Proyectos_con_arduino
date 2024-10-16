int rojo1 = 5;
int amarillo1=6;
int verde1=7;

int rojo2 = 8;
int amarillo2 = 9;
int verde2 = 10;

void setup() {
  pinMode(rojo1,OUTPUT);
  pinMode(amarillo1,OUTPUT);
  pinMode(verde1,OUTPUT);

  pinMode(rojo2,OUTPUT);
  pinMode(amarillo2,OUTPUT);
  pinMode(verde2,OUTPUT);

}

void loop() {
  //SEMAFOORO 2 FUNCIONANDO Y EL 1 ESPERANDO (CICLO SEMAFORO 2)
  digitalWrite(rojo1,HIGH);
  digitalWrite(amarillo1,LOW);
  digitalWrite(verde1,LOW);

  digitalWrite(rojo2,LOW);
  digitalWrite(amarillo2,LOW);
  digitalWrite(verde2,HIGH);
  delay(3000);

  //PARPADEO DEL SEMAFORO 2 (dos parpadeos)
  digitalWrite(verde2,LOW);
  delay(1000);
  digitalWrite(verde2,HIGH);
  delay(1000);
  digitalWrite(verde2,LOW);
  delay(1000);
  digitalWrite(verde2,HIGH);
  delay(1000);

  //CAMBIO DEL SEMAFORO 2
  digitalWrite(verde2,LOW);
  digitalWrite(amarillo2,HIGH);
  delay(1000);

  //SEMAFOORO 1 FUNCIONANDO Y EL 2 ESPERANDO (CICLO SEMAFORO 1)
  digitalWrite(rojo2,HIGH);
  digitalWrite(amarillo2,LOW);
  digitalWrite(verde2,LOW);

  digitalWrite(rojo1,LOW);
  digitalWrite(amarillo1,LOW);
  digitalWrite(verde1,HIGH);
  delay(3000);

  //PARPADEO DEL SEMAFORO 2 (dos parpadeos)
  digitalWrite(verde1,LOW);
  delay(1000);
  digitalWrite(verde1,HIGH);
  delay(1000);
  digitalWrite(verde1,LOW);
  delay(1000);
  digitalWrite(verde1,HIGH);
  delay(1000);

  //CAMBIO DEL SEMAFORO 2
  digitalWrite(verde1,LOW);
  digitalWrite(amarillo1,HIGH);
  delay(1000);
}
