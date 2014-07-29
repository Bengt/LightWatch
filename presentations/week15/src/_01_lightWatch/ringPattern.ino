/**
* Set the LED-Ring the the given value. The ring starts with LED 0
* @oaram lastLED the last LED
* @param firstLED the first LED
* @param color white=0,red=1,green=2,blue=3
*/
void rgbOn(int firstLED, int lastLED,int color){

  //resets the colors
  colorOn.b = 0;
  colorOn.g = 0;
  colorOn.r = 0;
      
  // you cant use cRGB Objects as method params.
  // and here is the workaround
  if(color == 0) {
      colorOn.b = 0;
      colorOn.g = 0;
      colorOn.r = 0; 
  }
    if(color == 1) {
      colorOn.r = 255/MAX_BRIGHTNESS; 
  }
      if(color == 2) {
      colorOn.g = 255/MAX_BRIGHTNESS; 
  }
      if(color == 3) {
      colorOn.b = 255/MAX_BRIGHTNESS; 
  }
      if(color == 4) {
      colorOn.r = 255/MAX_BRIGHTNESS;
      colorOn.g = 255/MAX_BRIGHTNESS;
      colorOn.b = 255/MAX_BRIGHTNESS; 
  }
    
  // from the first LED
  for (int LED_ID = firstLED; LED_ID <= LED_COUNT; LED_ID++) {  
    // user selected count
    if(LED_ID <= lastLED) {      
      LED.set_crgb_at(LED_ID, colorOn);      
    } 
    
    // the the lastLED
    else {
      
      LED.set_crgb_at(LED_ID, colorOff);
      
    }
    
  }

  LED.sync();
}

/**
* This method divides the ring in three colored segments.
*/
void initMenu() {
  
  cRGB color;
  turnOffAllLEDs();
  
  for (int LED_ID = 0; LED_ID <= LED_COUNT; LED_ID++) {  
    
    // red section
    if(LED_ID <= 3){
      color.g = 0/MAX_BRIGHTNESS;  // Setup the colors
      color.b = 0/MAX_BRIGHTNESS;  // Setup the colors
      color.r = 255/MAX_BRIGHTNESS;  // Setup the colors
      LED.set_crgb_at(LED_ID, color);      
    }
    
    // green section
    if(LED_ID > 3){
      color.g = 255/MAX_BRIGHTNESS;
      color.r = 0;
      LED.set_crgb_at(LED_ID, color);      
    }
    
   // blue section
   if(LED_ID > 7) {      
      color.b = 255/MAX_BRIGHTNESS;
      color.g = 0;
      color.r = 0; 
      LED.set_crgb_at(LED_ID, color);   
    }
    
     LED.sync();
  }
  
}

/**
* turn off all LEDs
*/
void turnOffAllLEDs(){
  for (int LED_ID = 1; LED_ID <= LED_COUNT; LED_ID++) {  
      LED.set_crgb_at(LED_ID - 1, colorOff);      
      LED.sync();
  }  
}


