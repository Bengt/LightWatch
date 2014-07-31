int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 12;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
boolean beat; // is there a beat ?
int currentCount = 0;
int maxCount = 99;
void setup() {
  
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  
  delay(1000);
  
}

void loop() {
  
   int SensorValue = analogRead(sensorPin);
   
     Serial.println(analogRead(sensorPin));
   
   delay(200);
   
   if(analogRead(sensorPin) > 970) {
      Serial.println("-------------------- beat there? ---------------------");
      beat = true;
      while(beat) {
        delay(20);
        Serial.print(currentCount);
        currentCount = currentCount+1;
        
        if(analogRead(sensorPin) == 0) {
          thereIsABeat();
          currentCount = 0;
        }
        
        if(currentCount >= maxCount) {
          currentCount = 0;
          Serial.println("-------------------- no beat ---------------------");
          return;
        }
        
      }
   }
}

void thereIsABeat() {
  Serial.println("There is a beat!");
  
  boolean end = true;
  boolean doneBeat = true;
   int beatCounter = 0;
   unsigned long start, stop, elapsed;
   
   
   
  while(end) {
    Serial.println("-----------------------Anfang-------------------- " + String(analogRead(sensorPin)));
    

    if(analogRead(sensorPin) > 700) {
      if(doneBeat) {
        if(beatCounter == 5)
          start = millis();
          
        Serial.println("There is a beat!");
        digitalWrite(ledPin, HIGH);
        doneBeat = false; 
        beatCounter = beatCounter+1;
      }
    } else {
      digitalWrite(ledPin, LOW);
      doneBeat = true;
    }
    
    if(beatCounter == 15) {
      digitalWrite(ledPin, LOW);
      stop = millis();
      elapsed = stop-start;
      float i = 60000/(float)(elapsed);
                
      Serial.println("-------------------- STOP ---------------------");
      Serial.println(i*(float)10);
      return; 
    }
     
  }
  
  delay(5000);
  return;
  beat = false;
  
}
