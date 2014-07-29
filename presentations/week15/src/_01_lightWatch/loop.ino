
/**
* Round and around
*/ 
void loop(){
  delay(20);
  
  averagePot(); // check user input and calculte average 
  
  // to start the menu press 6
  if(countMenu > 80 && sumValues/countMenu == 6) {
     
     resetVariabels();
     initMenu(); // ringPattern (visual)
     startMenu(); // check the user input
  }
  
}

/**
* Reset all helper variabels
*/
void resetVariabels() {
  lastPotValue = 0;
  sumValues = 0;
  countMenu = 0;
}

/**
* log the userinput
* this is just a workkaround and really dirty :/
*/
void averagePot() {
  
  // initial start
  if(lastPotValue == 0) {
    lastPotValue = singlePressMapper(analogRead(potentiometerPIN));
    return;
  }
  
  // difference between user input? => reset
  if(lastPotValue != singlePressMapper(analogRead(potentiometerPIN))) {
     resetVariabels();
     return;
  
  // no difference? Go on! Save the new lastPotValue 
  } else {
     int value = singlePressMapper(analogRead(potentiometerPIN));
     sumValues = sumValues+value;
     countMenu = countMenu + 1;
     lastPotValue = value;
     
  } 
  
}

/**
* Check user input for the menu.
*/
void startMenu() {
  
   unsigned long start, stop;
   boolean waitForPress = true;
   
   // start the abort/input count
   start = millis(); 
   
   while(waitForPress) {
     
     averagePot(); // log userinput
     
     mySerial.println(sumValues/countMenu);
     
     // userInput > 100 ?
     if(millis()-start > 2000 && countMenu > 100) {
       
       // Okay we can go on and check what the user is pressing
       // menu selection
       
       if(sumValues/countMenu <= 4) {
         turnOffAllLEDs();
         rgbOn(0,3,1); // visualize the input
         delay(2000);
         turnOffAllLEDs();
         resetVariabels();
         inputCurrentStrain();
         return;
       }
       
       if(sumValues/countMenu < 8) {
         turnOffAllLEDs();
         rgbOn(4,7,2); // visualize the input
         delay(2000);
         turnOffAllLEDs();
         resetVariabels();
         inputPulseSensor();
         return;
       }
       
       if(sumValues/countMenu > 8) {
         turnOffAllLEDs();
         rgbOn(8,11,3); // visualize the input
         resetVariabels();
         delay(2000);
         turnOffAllLEDs();
         return;
       }
       
     }
     
     // Abort after 7000 ms
     if(millis()-start > 7000) {
       turnOffAllLEDs();
       return;
     }
     
   }
}
