## Test mit Test_LED.ino

-  LED an Pin 0: Upload geht, LED blinkt
-  LED an Pin 1: Upload geht, LED blinkt
-  LED an Pin 2: Upload geht, LED blinkt
-  LED an Pin 3: Upload geht, LED blinkt
-  LED an Pin 4: Upload geht, LED blinkt

Erkenntnis: LED lässt sich überall anschließen

## Test mit Test_RGB.ino

-  LED an Pin 0: Upload geht, Ring blinkt
-  LED an Pin 1: Upload geht, Ring blinkt
-  LED an Pin 2: Upload geht, Ring blinkt
-  LED an Pin 3: Upload geht, Ring blinkt
-  LED an Pin 4: Upload geht, Ring blinkt

Erkenntnis: RGB Ring lässt sich überall anschließen

## Test mit Test_Pot.ino

-   HotPot an Pin 0: Upload geht, Test schlägt fehl; kein Analog-Pin
-   HotPot an Pin 1: Upload geht, Test schlägt fehl; kein Analog-Pin
-   HotPot an Pin 2: Upload geht, Test schlägt fehl; pin-13-LED des Arduino-ISP glimmt
-   HotPot an Pin 3: Upload geht, Test erfolgreich
-   HotPot an Pin 4: Upload geht, Test schlägt fehl
    -   ATtiny25 geht es. Input des ATtiny85 defekt?
    
Erkenntnis: HotPot muss an Pin 3 oder (einen heilen) Pin 4.

## Test mit Test_Pulse.ino

-   
