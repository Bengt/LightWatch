
#include <WS2812.h>
int softpotPin = A1;
int count = 0;
int sum = 0;
int zeroCount = 0;
int ringPin = 7;
int LED_COUNT = 12;
int MAX_BRIGHTNESS = 20;
WS2812 LED(LED_COUNT);
cRGB colorOn;
int sensorPin = A0;
int ledPin = 12;
int sensorValue = 0;
boolean beat;
int currentCount = 0;
int maxCount = 99;
void setup(){
  pinMode(ringPin, OUTPUT);
  LED.setOutput(ringPin);
  colorOn.r = 255/MAX_BRIGHTNESS;
  colorOn.g = 255/MAX_BRIGHTNESS;
  colorOn.b = 255/MAX_BRIGHTNESS;
  digitalWrite(softpotPin, HIGH);
  Serial.begin(9600);
  ledRing(0);
}
void loop(){
  int s = analogRead(softpotPin); 
  if(s > 1010 || s < 985) {
    int i = hotPotToRGB(s);
    sum = sum+i;
    count++;
    if(count == 10) {

      ledRing(sum/count);
     

      count = 0; // Werte im Speicher
      sum = 0; // Summe der Werte

    }


  } 
  else {
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
  if(analogRead(sensorPin) > 970) {
    beat = true;
    while(beat) {
      delay(20);
      currentCount = currentCount+1;
      if(analogRead(sensorPin) == 0) {
        thereIsABeat();
        currentCount = 0;
      }

      if(currentCount >= maxCount) {
        currentCount = 0;

        return;
      }

    }
  }
}

void thereIsABeat() {
  boolean end = true;
  boolean doneBeat = true;
  int beatCounter = 0;
  unsigned long start, stop, elapsed;


  int zeroCount = 0;
  while(end) {

    if(analogRead(sensorPin) > 700) {
      if(doneBeat) {
        if(beatCounter == 3)
          start = millis();
        ledRing(beatCounter);
        doneBeat = false; 
        beatCounter = beatCounter+1;
        zeroCount =0;
      }
    } 
    else {
      ledRing(0);
      digitalWrite(ledPin, LOW);
      doneBeat = true;
      zeroCount = zeroCount +1;
    }

    if(zeroCount > 50)
      return;

    if(beatCounter == 10) {
      digitalWrite(ledPin, LOW);
      stop = millis();
      elapsed = stop-start;
      float i = 60000/(float)(elapsed);
      i = i*((float)7);
      
      return; 
    }
  }
  delay(5000);
  ledRing(12);
  ledRing(1);
  
  
  return;
  beat = false;
}

void ledRing(int value){
  cRGB colorOff;
  
  for (int LED_ID = 1; LED_ID <= LED_COUNT; LED_ID++) {
    if(LED_ID <= value) {
      LED.set_crgb_at(LED_ID - 1, colorOn);      
    } 
    else {
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
}


