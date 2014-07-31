/**
* Mapping between RGB-RING and HotPot Rotary Potentiometer for a single press
* @param   potValue   value of the HotPot Rotary Potentiometer
* @return  the RGB-LED count
*/
int singlePressMapper(int potValue){
  
  if(potValue < 35) return 0; // less than
  if(potValue < 120) return 1;
  if(potValue < 250) return 2;
  if(potValue < 370) return 3;
  if(potValue < 420) return 4;
  if(potValue < 515) return 5;
  if(potValue < 600) return 6;
  if(potValue < 700) return 7;
  if(potValue < 800) return 8;
  if(potValue < 900) return 9;
  if(potValue < 960) return 10;
  if(potValue > 1010) return 11; // more(!) than 1010
  
}
