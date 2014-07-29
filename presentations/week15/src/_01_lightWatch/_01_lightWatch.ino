/**
* ########################################################################################
* libary for the eeprom
* to read and ride to the eeprom use the methods in eepromWriteAndRead.
* optimized to read and write integer
* ########################################################################################
*/
#include <EEPROM.h>

/**
* ########################################################################################
* HotPot Rotary Potentiometer
* ########################################################################################
*/
const int potentiometerPIN = 3; //HotPot Rotary Potentiometer input PIN

/**
* ########################################################################################
* pulseSensor
* ########################################################################################
*/
const int pulseSensorPIN = A1; // PulseSensor intput PIN

/**
* ########################################################################################
* LED Ring
* ########################################################################################
*/
#include <WS2812.h> // The libary to access the ring

const int rgbRingPIN = 0; // RGB Ring output PIN 
const int LED_COUNT = 12; // all LEDs on the ring
const int MAX_BRIGHTNESS = 50; // otherwise eye cancer. 0 is HIGH 255 is low

WS2812 LED(LED_COUNT); // tell the libary, that there are 12 LEDs on the ring.

// you cant use cRGB Objects as method param
cRGB colorOn; // the led color
cRGB colorOff; // white(colorOff) does not need to setup, because its the default value.

/**
* ########################################################################################
* SoftwareSerial
* ########################################################################################
*/
#include <SoftwareSerial.h>

const int serialTX = 4; // serial tx
const int serialRX = 0; // serial rx. kind of useless. We don't need it.

SoftwareSerial mySerial(serialRX, serialTX);

/**
* ########################################################################################
* Global sh*t. dirty code but it works
* ########################################################################################
*/
int sumValues = 0; // sum of user input
int countMenu = 0; // count
int lastPotValue = 0; // the last user input
int eepromCount = 0;

/**
* ########################################################################################
* We like hufflepuff.
* ########################################################################################
*/
void setup() {
 
  // RGB Ring
  pinMode(rgbRingPIN, OUTPUT); // initialize the LED pin as an output:
  LED.setOutput(rgbRingPIN);  // sets the output pin for the 12-rgb-ring
  turnOffAllLEDs();
  // SoftwareSerial
  pinMode(serialRX,INPUT);
  pinMode(serialTX,OUTPUT);
  mySerial.begin(9600);
  
  // HotPot Rotary Potentiometer
  digitalWrite(potentiometerPIN, HIGH); // initialize the HotPot Rotary Potentiometer
  

  //reads out the eeprom count
  eepromCount = EEPROMReadInt(0);
  
  // read all values from rom
  for (int i = 2; i< eepromCount; i= i=i+2) {
    mySerial.println((String) i + " " + (String) EEPROMReadInt(i));
  }
}
