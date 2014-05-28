/*
 * RGB_RING_with_two_buttons
 *
 * Created: 21.05.2014 
 *  Author: Bengt Lüers & Marius Wybrands  
 */ 

// The libary to access the ring
#include <WS2812.h>

// the led count on the ring
int LED_COUNT = 12;

// Default ledPin (just for testing)
int ledPin = 13;

// UpButton
int buttonUpPin = 9;
int buttonDownPin = 7;
int ringPin = 8;
// 0 is HIGH 255 is low
int MAX_BRIGHTNESS = 20;

int healthCount = 1;

WS2812 LED(LED_COUNT); // 1 LED
	
cRGB colorGreen;
cRGB colorYellow;
cRGB colorRed;
cRGB colorOff;

int rangeGreen = 4;
int rangeYellow = 3;
int rangeRed= 5;

// This two array must have the same number of values. To Define a color use the setup method
int rangeArray[3]={4,3,5};
cRGB colorArray[3]={colorGreen, colorYellow, colorRed};
int arrayLenght = 3;

// variables will change:
int buttonUpState = 0;         // variable for reading the pushbutton status

// variables will change:
int buttonDownState = 0;         // variable for reading the pushbutton status

/**
This method sets up the pinModes and config the led ring
**/
void setup() {
    // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(buttonUpPin, INPUT);
    // initialize the pushbutton pin as an input:
  pinMode(buttonDownPin, INPUT);
  // sets the output pin for the 12-rgb-ring
  LED.setOutput(ringPin);
  
  // Setup the colors
  // white(colorOff) does not need to setup, because its the default value.
  colorArray[0].g = 255/MAX_BRIGHTNESS;
  
  colorArray[1].r = 255/MAX_BRIGHTNESS;
  colorArray[1].g = 255/MAX_BRIGHTNESS;
  colorArray[1].b = 255/MAX_BRIGHTNESS;
  colorArray[2].r = 255/MAX_BRIGHTNESS;
  
  Serial.begin(9600);
  
  // initial setup for the ring
  ledRing(healthCount);
  
}

void ledRing(int lastLED) {
  
  int helper = 0;
  int helperCount = rangeArray[0];
  
  // loop for the max LED count defined by the ring
  for (int LED_ID = 1; LED_ID <= LED_COUNT; LED_ID++) {
     
    // user selected count
    if(LED_ID <= lastLED) {
      
      if(LED_ID <= helperCount) {
        LED.set_crgb_at(LED_ID - 1, colorArray[helper]);
      } else {
        helper++;
         helperCount = helperCount + rangeArray[helper];
         LED.set_crgb_at(LED_ID - 1, colorArray[helper]);
      }
         
    } else {
       LED.set_crgb_at(LED_ID - 1, colorOff);
    }
    
  }
  LED.sync();

}

void loop() {
   // read the state of the pushbutton value:
  buttonDownState = digitalRead(buttonDownPin);

   // read the state of the pushbutton value:
  buttonUpState = digitalRead(buttonUpPin);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  
  
  if (buttonUpState == LOW) {
            
    healthCount = (healthCount + 1)%(LED_COUNT+1);
    
        if(healthCount == 0)
          healthCount++;
          
    ledRing(healthCount);
      Serial.println((String) healthCount);

      
    delay(200);
  }

  if (buttonDownState == LOW && healthCount > 1) {

    healthCount = (healthCount - 1)%(LED_COUNT+1);
    ledRing(healthCount);
         Serial.println((String) healthCount);
    delay(500);
  }  
    
  
  
}

void set_all_leds_to(cRGB value) {
    for (int i = 0; i < LED_COUNT; i++) {
        LED.set_crgb_at(i, value);
    }
}

