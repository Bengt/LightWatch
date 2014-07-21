/*
 * light_ws2812 example
 *
 * Created: 07.03.2014 12:49:30
 *  Author: Matthias Riegler
 */ 

#include <WS2812.h>

// Configuration
int LED_COUNT = 12;
int MAX_BRIGHTNESS = 20;
int RING_PIN = 0;

// globals #evil
bool STATE = LOW;
WS2812 LED(LED_COUNT);

void setup() {
  LED.setOutput(RING_PIN);
  pinMode(RING_PIN, OUTPUT);
}

void loop() {
  
  // set leds to state
  cRGB color;
  for (int LED_ID = 1; LED_ID <= 12; LED_ID++) {
    color.b = STATE * LED_ID * 21 / (255 / MAX_BRIGHTNESS);
    color.g = STATE * LED_ID * 21 / (255 / MAX_BRIGHTNESS);
    color.r = STATE * LED_ID * 21 / (255 / MAX_BRIGHTNESS);
    LED.set_crgb_at(LED_ID - 1, color);
  }
  LED.sync();

  STATE = !STATE;
  
  delay(1000);

}

