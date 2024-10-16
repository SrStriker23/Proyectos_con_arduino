void setup() {
  pinMode(2, INPUT);  //pin 2 como salida 
  pinMode(3,OUTPUT);  //Pin 3 como salida

}

void loop() {
  if(digitalRead(2) == HIGH){   //evaluo si la entrada esta a nivel alto
    digitalWrite(3,HIGH);   //enciendo LED
  }
  else{
    digitalWrite(3,LOW);  //Apago el led
  }

}
