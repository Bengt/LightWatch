//Who can ever remember what the prescaler combinations are?
//These are for Timer0
int PRESCALE0_1 = 0 | (1 << CS00);
int PRESCALE0_8 = 0 | (1 << CS01);
int PRESCALE0_64 = 0 | (1 << CS00) | (1 << CS01);
int PRESCALE0_256 = 0 | (1 << CS02);
int PRESCALE0_1024 = 0 | (1 << CS02) | (1 << CS00);

volatile int LED_PIN = 0;

int IRQS_PER_SECOND = 1000;

void setup() {
  pinMode (LED_PIN, OUTPUT);
  //setupTimer();
//  setupTimer0();
  //setupTimer1();
  setupTimer2();
  //timer1_init();
}
/*
void setupTimer() {
  cli();

  TCCR1 = (1<<CS12) | (1<<CS11);
  OCR1A = 124;           // [(8Mhz/32)*500µs]-1 = 124
  TIMSK = (1<<OCIE1A);     // enable Timer interrupts

  sei();
}
*/

void setupTimer0() { 
  TCCR0A = (1 << WGM01); // CTC Modus
  TCCR0B |= (1 << CS01); // Prescaler 8
  // ((1000000/8)/1000) = 125
  /*
  Der Compare Interrupt Handler 
  wird aufgerufen, wenn 
  TCNT0 = OCR0A = 125-1 
  ist (125 Schritte), d.h. genau alle 1 ms
  */
  OCR0A = 125 - 1;
 
  // Compare Interrupt erlauben
  TIMSK |= (1<<OCIE0A);
 
  // Global Interrupts aktivieren
  sei();
}

/*
void setupTimer1() {
  TCCR0A |= PRESCALE0_1024;
  OCR0A = 1;
  TIMSK |= (1 << TOIE0);
  TCNT0 = 0;

  //  TCCR0B |= 1 << WGM02;

  sei();
}
*/

/*
void setupTimer2() {
  cli();           // disable all interrupts
  
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1C = 0; // ***THIS LINE ADDED***
  TCNT1  = 0;
  
  OCR1A = (8000000/1024)/(125);     // compare match register.
  TCCR1B = (1 << WGM12) | (4 << CS10);    // CTC mode and 256 prescaler 
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt

  // enable interrupts
  sei();
}
*/

void loop(){
}

ISR(TIMER1_COMPA_vect) {  // das ist der Richtige aufruf des "Timer Interrupt" ISR Interupt Service Routine

  digitalWrite(0, HIGH);
  delay(10000);
  digitalWrite(0, LOW);
  delay(10000);
}

ISR (TIMER0_COMPA_vect) {
  digitalWrite(0, HIGH);
  delay(1000);
  digitalWrite(0, LOW);
  delay(10000);
}

ISR(TIM0_OVF_vect) { 
  digitalWrite(0, HIGH);
  delay(10000);
  digitalWrite(0, LOW);
  delay(1000);
}

