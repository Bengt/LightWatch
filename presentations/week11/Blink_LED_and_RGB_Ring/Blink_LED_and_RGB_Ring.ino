/*
 * light_ws2812 example
 *
 * Created: 07.03.2014 12:49:30
 *  Author: Matthias Riegler
 */ 

#include <WS2812.h>

int LED_COUNT = 12;
int MAX_BRIGHTNESS = 20;
WS2812 LED(LED_COUNT); // 1 LED
int LED_PIN = 3;
int RING_PIN = 4;

void setup() {
    LED.setOutput(4); // Digital Pin 9
    pinMode(RING_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);

    cRGB color;
    for (int i = 0; i < 1000; i++) {
      for (int LED_ID = 1; LED_ID <= 12; LED_ID++) {
        color.b = i % 2 * LED_ID * 21 / (255 / MAX_BRIGHTNESS);
        color.g = i % 2 * LED_ID * 21 / (255 / MAX_BRIGHTNESS);
        color.r = i % 2 * LED_ID * 21 / (255 / MAX_BRIGHTNESS);
        LED.set_crgb_at(LED_ID - 1, color);
      }
      LED.sync();
      
      int ledState;
      if (i % 2 == 1)
        ledState = HIGH;
      else
        ledState = LOW;
      // set the LED with the ledState of the variable:
      digitalWrite(LED_PIN, ledState);
      
      delay(1000);
  }
}

void loop() {

}

