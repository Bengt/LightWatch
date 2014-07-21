#include <SoftwareSerial.h>
const int rx = 0;
const int tx = 3;

SoftwareSerial mySerial(rx, tx);

void setup() {
  pinMode(rx,INPUT);
  pinMode(tx,OUTPUT);
  mySerial.begin(9600);
}

void loop() {
  mySerial.println(1);
  delay(200);
  mySerial.println(0);
  delay(200);
}
