/*
  Analog Input
 Demonstrates analog input by reading an analog sensor on analog pin 0 and
 turning on and off a light emitting diode(LED)  connected to digital pin 13. 
 The amount of time the LED will be on and off depends on
 the value obtained by analogRead(). 
 
 The circuit:
 * Potentiometer attached to analog input 0
 * center pin of the potentiometer to the analog pin
 * one side pin (either one) to ground
 * the other side pin to +5V
 * LED anode (long leg) attached to digital output 13
 * LED cathode (short leg) attached to ground
 
 * Note: because most Arduinos have a built-in LED attached 
 to pin 13 on the board, the LED is optional.
 
 
 Created by David Cuartielles
 modified 30 Aug 2011
 By Tom Igoe
 
 This example code is in the public domain.
 
 http://arduino.cc/en/Tutorial/AnalogInput
 
 */

int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

int triggerTimeCount = 50;
int currentCount = 0;

boolean over = false;
boolean beat = true;
boolean zeroHelper = true;
unsigned long first, last, elapsed;
int beatCounter = 0;
void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  
  delay(3000);
}

void loop() {

  int SensorValue = analogRead(sensorPin);
  
  if(currentCount == 0) {
    Serial.println("currentCount ist Null" + String(analogRead(sensorPin)));
    if(analogRead(sensorPin) < 970) {
      Serial.println("kleiner als" + String(analogRead(sensorPin)));
      delay(100);
      return;
    }
    delay(100);
    boolean helper = true;
    Serial.println("IDLESTART! -----------------------------------------");
    while(helper) {
      currentCount = currentCount+1;
      Serial.println("idle" + String(analogRead(sensorPin)));
      
      if(analogRead(sensorPin) < 700) {
        currentCount = 0;
        Serial.println("IDLEABBRUCH! -----------------------------------------");
        return;
      }
      
      if(currentCount >= triggerTimeCount) {
        helper = false;
        Serial.println("IDLEDONE! -----------------------------------------");
      }
      
      delay(10);
    } // while end
  
    zeroHelper = true; // for one method 
   
  }
  
  if(beatCounter == 0 && currentCount == 50) {
   Serial.println("Zähler gestartet");
   delay(4000);
   first = millis();
  }
      
  // finger up and reset
  if(SensorValue == 0 && zeroHelper) {
    currentCount = 0;
    last = millis();
    myPulseIs(last-first, beatCounter);
    beatCounter = 0;
    zeroHelper = false;
    return;
  }
  
  if(SensorValue > 700) {
    
    if(beat) {
      digitalWrite(ledPin, HIGH);
      beatCounter = beatCounter +1;
      beat = false;
      
    }  
    
  } else {
    digitalWrite(ledPin, LOW);
    beat = true;
    
  }
  
  
  
 
}

void myPulseIs(unsigned long e, int beats) {
   Serial.println("Mein Puls ist: " + String(beats));
   
   beatCounter = 0;
   Serial.println("Mein Puls ist: " + String(beatCounter)); 
   delay(5000);
     
}
