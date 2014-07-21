/* lights the led if the left side of the hotpot is pressed */

// Configuration
int LED_PIN = 0;
int POT_PIN = 3;

void setup(){
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(POT_PIN, HIGH); //enable pullup resistor
}

void loop(){
  if (analogRead(POT_PIN) >= 512) {
    // left side pressed
    digitalWrite(LED_PIN, HIGH);
  } else {
    // right side pressed
    digitalWrite(LED_PIN, LOW);
  }
}

