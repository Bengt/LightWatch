int softpotPin = A0; //analog pin 0
int count = 1; // Werte im Speicher
int sum = 1; // Summe der Werte
int zeroCount = 0;


void setup(){
  
  digitalWrite(softpotPin, HIGH); //enable pullup resistor
  Serial.begin(9600);
  
}

void loop(){
  int softpotReading = analogRead(softpotPin); 

  if(softpotReading > 1000 || softpotReading < 990) {
   
      sum =  sum + softpotReading;
      count++;
    
  } else {
      zeroCount++;
      
      if(zeroCount >= 5) {
          sum = 1;
          count = 1;
          zeroCount = 0;
          Serial.println("-------------- Zurückgesetzt ------------");
      }
  }
  Serial.print(count);
  Serial.print(" ------ ");
  Serial.print(sum/count);
  Serial.print(" ------ ");
  Serial.println(softpotReading);
  Serial.println(hotPotToRGB(softpotReading));
  delay(750); //just here to slow down the output for easier reading
}

int hotPotToRGB(int v){
  if(v < 1000 && v > 990)
  return 0;
  
  if(v<541) {
    if(v<256) {
      if(v<176) {
        if(v<91) {
          // 1
          return 1;
          
        } else {
          // 2
          return 1;
        }
      } else {
        // 3
        return 3;
      }
    } else { // größer 256
      if(v<451) {
        if(v<336) {
          // 4
          return 4;
        } else {
          // 5
          return 5;
        }
      } else {
        // 6
       return 6;
      }
      
    }
    
  } else { // größer 541
    if(v<811) {
      if(v<711) {
        if(v<631) {
          // 7
          return 7;
        } else {
          // 8
          return 8;
        }
      } else { //
        // 9
        return 9;
      }
    } else { // größer 811
      if(v<1001) {
        if(v<911) {
          // 10
          return 10;
        } else {
          // 11
          return 11;
        }
      } else {
        // 12
        
        return 12;
      }
      
    }
  }
}
