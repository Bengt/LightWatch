// The libary to access the ring
#include <WS2812.h>
 
int softpotPin = A0; //analog pin für den Ring
int count = 0; // Werte im Speicher
int sum = 0; // Summe der Werte
int zeroCount = 0;

int ringPin = 13;
int LED_COUNT = 12; // Anzahl der LEDs auf dem RGBRing
int MAX_BRIGHTNESS = 20; // 0 is HIGH 255 is low
WS2812 LED(LED_COUNT); // 1 LED
cRGB colorOn;
cRGB colorOff;

int sensorPin = A1;    // select the input pin for the potentiometer
int ledPin = 12;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
boolean beat; // is there a beat ?
int currentCount = 0;
int maxCount = 99;

void setup(){
    
  pinMode(ringPin, OUTPUT); // initialize the LED pin as an output:
  LED.setOutput(ringPin);  // sets the output pin for the 12-rgb-ring

  colorOn.r = 255/MAX_BRIGHTNESS;  // Setup the colors
  colorOn.g = 255/MAX_BRIGHTNESS;  // white(colorOff) does not need to setup, because its the default value.
  colorOn.b = 255/MAX_BRIGHTNESS;

  digitalWrite(softpotPin, HIGH); //enable pullup resistor

  Serial.begin(9600);

  // initial setup for the ring
  ledRing(0);
}

void loop(){
  int softpotReading = analogRead(softpotPin); 
  
  if(softpotReading > 1010 || softpotReading < 985) {

    int i = hotPotToRGB(softpotReading);
    
    sum = sum+i;
    count++;
    //Serial.println("Dies ist der Mittelwert:" + String(sum/count));
    if(count == 10) {
      
      ledRing(sum/count);
      Serial.println("Umgeschaltet zu:" + String(sum/count));
      
      count = 0; // Werte im Speicher
      sum = 0; // Summe der Werte
      
    }
  

  } else {
    zeroCount++;
    if(zeroCount >= 5) {
      count = 0; // Werte im Speicher
      sum = 0; // Summe der Werte
      zeroCount = 0;
    }
    
    
 }

 pulseSensor();
 
}

void pulseSensor() {
  
   int SensorValue = analogRead(sensorPin);
   
     Serial.println(analogRead(sensorPin));
   
   if(analogRead(sensorPin) > 970) {
      Serial.println("-------------------- beat there? ---------------------");
      beat = true;
      while(beat) {
        delay(20);
        Serial.print(currentCount);
        currentCount = currentCount+1;
        
        if(analogRead(sensorPin) == 0) {
          thereIsABeat();
          currentCount = 0;
        }
        
        if(currentCount >= maxCount) {
          currentCount = 0;
          Serial.println("-------------------- no beat ---------------------");
          return;
        }
        
      }
   }
}

void thereIsABeat() {
  Serial.println("There is a beat!");
  
  boolean end = true;
  boolean doneBeat = true;
   int beatCounter = 0;
   unsigned long start, stop, elapsed;
   
   
   int zeroCount = 0;
  while(end) {
    Serial.println("-----------------------Anfang-------------------- " + String(analogRead(sensorPin)));
   
    if(analogRead(sensorPin) > 700) {
      if(doneBeat) {
        if(beatCounter == 3)
          start = millis();
          
        Serial.println("There is a beat!");
        ledRing(12);
        doneBeat = false; 
        beatCounter = beatCounter+1;
        zeroCount =0;
      }
    } else {
      ledRing(beatCounter);
      digitalWrite(ledPin, LOW);
      doneBeat = true;
      zeroCount = zeroCount +1;
    }
    
    if(zeroCount > 100)
      return;
    
    if(beatCounter == 10) {
      digitalWrite(ledPin, LOW);
      stop = millis();
      elapsed = stop-start;
      float i = 60000/(float)(elapsed);
                
      Serial.println("-------------------- STOP ---------------------");
      Serial.println(i*(float)7);
       i = i*((float)7);
      
      ledRing((int)((i)/(float)10));
      return; 
    }
     
  }
  
  delay(5000);
  return;
  beat = false;
  
}

void ledRing(int value){

    // loop for the max LED count defined by the ring
  for (int LED_ID = 1; LED_ID <= LED_COUNT; LED_ID++) {
     
    // user selected count
    if(LED_ID <= value) {
      
      LED.set_crgb_at(LED_ID - 1, colorOn);
         
    } else {
      
      LED.set_crgb_at(LED_ID - 1, colorOff);
      
    }
    
  }
  LED.set_crgb_at(11, colorOn);
  LED.sync();
  
}

int hotPotToRGB(int v){
    
  if(v< 69) return 1;
  if(v< 100) return 2;
  if(v< 200) return 3;
  if(v< 350) return 4;
  if(v< 450) return 5;
  if(v< 550) return 6;
  if(v< 600) return 7;
  if(v< 800) return 8;
  if(v< 850) return 9;
  if(v< 900) return 10;
  if(v< 960) return 11;
  if(v> 1010) return 12;
  /**
  if(v < 1010 && v > 985)
    return 0;

  if(v<541) {
    if(v<256) {
      if(v<120) {
        if(v<75) {
          // 1
          return 1;

        } 
        else {
          // 2
          return 2;
        }
      } 
      else {
        // 3
        return 3;
      }
    } 
    else { // größer 256
      if(v<451) {
        if(v<336) {
          // 4
          return 4;
        } 
        else {
          // 5
          return 5;
        }
      } 
      else {
        // 6
        return 6;
      }

    }

  } 
  else { // größer 541
    if(v<811) {
      if(v<711) {
        if(v<631) {
          // 7
          return 7;
        } 
        else {
          // 8
          return 8;
        }
      } 
      else { //
        // 9
        return 9;
      }
    } 
    else { // größer 811
      if(v<1001) {
        if(v<911) {
          // 10
          return 10;
        } 
        else {
          // 11
          return 11;
        }
      } 
      else {
        // 12

        return 12;
      }

    }
  }*/
}

