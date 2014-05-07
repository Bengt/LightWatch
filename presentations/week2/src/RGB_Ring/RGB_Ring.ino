/*
 * light_ws2812 example
 *
 * Created: 07.03.2014 12:49:30
 *  Author: Matthias Riegler
 */ 

#include <WS2812.h>

int LED_COUNT = 12;
int MAX_BRIGHTNESS = 255;
WS2812 LED(LED_COUNT); // 1 LED
	
cRGB color;

void setup() {
    LED.setOutput(9); // Digital Pin 9
    Serial.begin(9600);

  for (int LED_ID = 1; LED_ID <= 12; LED_ID++) {
    color.b = LED_ID * 21 / (255 / MAX_BRIGHTNESS);
    color.g = LED_ID * 21 / (255 / MAX_BRIGHTNESS);
    color.r = LED_ID * 21 / (255 / MAX_BRIGHTNESS);
    LED.set_crgb_at(LED_ID - 1, color);
  }
  LED.sync();
}

void loop() {

}

void set_all_leds_to(cRGB value) {
    for (int i = 0; i < LED_COUNT; i++) {
        LED.set_crgb_at(i, value);
    }
}

