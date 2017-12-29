//Eric Lyons 2017
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.2 and v0.3
//Uses pinduino library

/// ---=====  NOTE ====---
/// 


#include <pinduino.h>
int aLEDNum1 = 99; //left ramp
int aLEDNum2 = 59; //right ramp
int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");



int bg_on = 1; //attract effect
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 4000; //Amount of time to wait before chase lights start up again 1000 == 1 second
int bgWhiteTime = 500;
String color = "orange";
int cottage_count = 0;

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
}

void loop(){
  if (bg_on){background();}
//   Print the pin states out to serial 
  pd.pinState()->update();
  pd.pinState()->print();
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) {bg_on=1;}
  if (millis()-timeLastEvent > bgWhiteTime && !bg_on) {
    pd.adrLED1()->clear();
    pd.adrLED2()->clear();
  }
}

void checkPinStates(){
  int trigger =0;
  
  

  
  if ( pd.pinState()->J126(1) ){ // cottage
    cottage_count = cottage_count+1;
    if (cottage_count > 100) {
      pd.chaseAllAdr2Color("orange", "blue", 10, 0, 1);
      cottage_count = 0;
//      pd.adrLED1()->bullet2Color("blue", "orange", 25,  4,  1);
       }
    trigger = 1; 
  }

 if ( pd.pinState()->J126(2) ){ //rocket
    pd.adrLED1()->spreadInFromPoint2Color (46, "red", "yellow", 200);
    delay(100);
    trigger = 1; 
  }

  if ( pd.pinState()->J126(3) ){ //WOOC
    pd.adrLED1()->color("red", 255);
    pd.adrLED1()->spreadOutToPoint(54, 200);
    pd.adrLED1()->fadeOut(10);
    trigger = 1; 
  }
  if ( pd.pinState()->J126(4) ){ // comic
    pd.adrLED2()->bullet2Color("lime", "purple", 25,  4,  -1);
//    pd.adrLED1()->color("blue", 255);
//    delay(100);
    trigger=1;
  }
  if ( pd.pinState()->J126(5) ){ // ozone
    pd.adrLED1()->bullet2Color("red", "orange", 25,  4,  1);
    trigger=1;
  }
  
  if ( pd.pinState()->J126(6) ){ // right side flash
    pd.adrLED2()->bulletFromPoint2Color("orange", "purple", 20, 5, 25);
    trigger =1;
  }
  
  if ( pd.pinState()->J126(7) ){ // not used
  }
  if ( pd.pinState()->J126(8) ){ // not used
  }

//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   pd.pinState()->reset();
   trigger =0;
   bg_on = 0;
   timeLastEvent = millis();
  }

//end function checkPinStates
}



void background() {
  pd.adrLED1()->sparkle(color,20);
  pd.adrLED2()->sparkle(color,20);
  if (random(1000) == 0) {
    if (color == "orange") color = "red";
    else if (color == "red") color = "yellow";
    else color = "orange";
  }
}
