
// The libary to access the ring
#include <WS2812.h>

int softpotPin = A0; //analog pin für den Ring
int count = 1; // Werte im Speicher
int sum = 1; // Summe der Werte
int zeroCount = 0;

int ringPin = 7;
int LED_COUNT = 12; // Anzahl der LEDs auf dem RGBRing
int MAX_BRIGHTNESS = 20; // 0 is HIGH 255 is low
WS2812 LED(LED_COUNT); // 1 LED
cRGB colorOn;
cRGB colorOff;



void setup(){

  pinMode(ringPin, OUTPUT); // initialize the LED pin as an output:
  LED.setOutput(ringPin);  // sets the output pin for the 12-rgb-ring

  colorOn.r = 255/MAX_BRIGHTNESS;  // Setup the colors
  colorOn.g = 255/MAX_BRIGHTNESS;  // white(colorOff) does not need to setup, because its the default value.
  colorOn.b = 255/MAX_BRIGHTNESS;

  digitalWrite(softpotPin, HIGH); //enable pullup resistor

  Serial.begin(9600);

  // initial setup for the ring
  ledRing(1);

}

void loop(){
  int softpotReading = analogRead(softpotPin); 

  if(softpotReading > 1000 || softpotReading < 990) {

    Serial.println(softpotReading);
    int i = hotPotToRGB(softpotReading);
    Serial.println(i);
    ledRing(i);

  } 
  else {
    
    Serial.println(softpotReading);
    
    }
  
  
  
  
  delay(750); //just here to slow down the output for easier reading
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
  
  LED.sync();
  
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

        } 
        else {
          // 2
          return 1;
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
  }
}

