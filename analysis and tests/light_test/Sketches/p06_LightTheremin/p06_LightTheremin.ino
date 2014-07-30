/*
  Arduino Starter Kit example
 Project 6  - Light Theremin
 
 This sketch is written to accompany Project 6 in the
 Arduino Starter Kit
 
 Parts required:
 photoresistor
 10 kilohm resistor 
 piezo
 
 Created 13 September 2012
 by Scott Fitzgerald
 
 http://arduino.cc/starterKit
 
 This example code is part of the public domain 
*/
#include <EEPROM.h>

// address
int address = 0;
// variable to hold sensor value
int sensorValue;
// variable to calibrate low value
int sensorLow = 1023;
// variable to calibrate high value
int sensorHigh = 0;
// LED pin
const int ledPin = 13;
const int buttonPin = 11;

void setup() {
  // unser code
  Serial.begin(4800);
   pinMode(13,OUTPUT);
  pinMode(11,INPUT);
  
  int value;
  for (int i = 0; i < 1024; i=i+2) {
    value = EEPROMReadInt(i);
    Serial.println((String) i + " " + (String) value);
  }
  Serial.println("-------------------------------");
}

void loop() {
  //read the input from A0 and store it in a variable
  
  log_sensor();
  int currentValue = EEPROMReadInt(address-2);
  int prefValue = EEPROMReadInt(address-4);
  int prefPrefValue = EEPROMReadInt(address-6);
  

      
      
      if(currentValue <= 20 && prefValue >= 800) {
        Serial.println("---------------------------------");
        Serial.println("push and pull");
        Serial.println("currentValue:" +  ((String)currentValue));
        Serial.println("prefValue:" +  ((String)prefValue));
        Serial.println("---------------------------------");  
      }
        
      if(currentValue >= 800 && prefValue <= 20) {
        Serial.println("---------------------------------");
        Serial.println("pull and push");
         Serial.println("currentValue:" +  ((String)currentValue));
        Serial.println("prefValue:" +  ((String)prefValue));
        Serial.println("---------------------------------");
      }
      
  
    
  delay(1000);
}

int input() {
      
  // Sensorpin
  sensorValue = analogRead(A0);
  Serial.println((String) address + " " + (String) sensorValue);
  EEPROMWriteInt(address, sensorValue);
  
  Serial.println((String)EEPROMReadInt(address));
  address=address+2;
  
  
}

void log_sensor() {
  
  if(address >= 1024)
    return;
    
  // Sensorpin
  sensorValue = analogRead(A0);
  Serial.println((String) address + " " + (String) sensorValue);
  EEPROMWriteInt(address, sensorValue);
  
  Serial.println((String)EEPROMReadInt(address));
  address=address+2;
  
  
}


//This function will write a 2 byte integer to the eeprom at the specified address and address + 1
void EEPROMWriteInt(int p_address, int p_value)
      {
      byte lowByte = ((p_value >> 0) & 0xFF);
      byte highByte = ((p_value >> 8) & 0xFF);

      EEPROM.write(p_address, lowByte);
      EEPROM.write(p_address + 1, highByte);
      }

//This function will read a 2 byte integer from the eeprom at the specified address and address + 1
unsigned int EEPROMReadInt(int p_address)
      {
      byte lowByte = EEPROM.read(p_address);
      byte highByte = EEPROM.read(p_address + 1);

      return ((lowByte << 0) & 0xFF) + ((highByte << 8) & 0xFF00);
      }
