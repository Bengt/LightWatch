/**
* Check user input for the menu.
*/
void inputCurrentStrain() {
  
   unsigned long start, stop;
   boolean waitForPress = true;
   
   // start the abort/input count
   start = millis(); 
   rgbOn(0,0,3);
   while(waitForPress) {
     
     averagePot(); // log userinput
     
     mySerial.println(sumValues/countMenu);
     
     // userInput > 100 ?
     if(millis()-start > 4000 && countMenu > 100) {
       
       rgbOn(0,(sumValues/countMenu),3);
       mySerial.println("Belastung ist: " +  String(sumValues/countMenu));
       EEPROMWriteInt(eepromCount, sumValues/countMenu);
       eepromCount = eepromCount+2;
       EEPROMWriteInt(0, eepromCount);
       delay(3000);
   
     }
     
     // Abort after 7000 ms
     if(millis()-start > 7000) {
       turnOffAllLEDs();
       return;
     }
     
   }
}
