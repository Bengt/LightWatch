boolean beat = true;

void inputPulseSensor() {
   unsigned long start, stop;
   int count = 0;
   start = millis();
   
   while(beat) {
     rgbOn(0,0,1);
     delay(40);
     if(analogRead(pulseSensorPIN) > 815 && analogRead(pulseSensorPIN) < 825) {
        count = count+1;
        mySerial.println("count");
     } 
     
     if(analogRead(pulseSensorPIN) < 815 || analogRead(pulseSensorPIN) > 825){
       count = 0;
       mySerial.println("zero");
     }
     
     if(count > 8) {
      mySerial.println("over18");
       start = millis(); // reset the abort timer
     rgbOn(0,0,3);
      delay(2000);
      countBeats();
     }
   
     if(millis()-start > 10000 && count == 0) {
       mySerial.println("abort");
       turnOffAllLEDs();
       return;
     }
     
   }
     
     

}

int countBeats() {
  int beatCounter = 0;
  rgbOn(0,beatCounter,3);
  boolean beatWasThere = true;
  delay(1500);
  while(true) {
  
  if(analogRead(pulseSensorPIN) > 750 && !beatWasThere) {
   rgbOn(0,beatCounter,3);
   beatCounter++;
   mySerial.println(beatCounter);
   beatWasThere = true;
   
   if(beatCounter == 13) {
      rgbOn(0,beatCounter,1);
    delay(5000);  
   }
   
   } 
  
  if(analogRead(pulseSensorPIN) < 600) {
    turnOffAllLEDs();
    beatWasThere = false;
  }
  
  if(analogRead(pulseSensorPIN) == 0) {
    delay(10);
    if(analogRead(pulseSensorPIN) == 0) {
      mySerial.println("abort");
    turnOffAllLEDs();
    return -1;
    } 
  }
  }
}


