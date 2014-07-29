int STATE = LOW;

void setup(){
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop(){
  digitalWrite(0, STATE);
  digitalWrite(1, STATE);
  digitalWrite(2, STATE);
  digitalWrite(3, STATE);
  digitalWrite(4, STATE);

  STATE = !STATE;
  
  delay(1000);
}

