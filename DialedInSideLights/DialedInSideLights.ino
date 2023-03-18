//Eric Lyons 2018
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.2 and v0.3
//Uses pinduino library

/// ---=====  NOTE ====---
/// 


#include <pinduino.h>
int aLEDNum1 = 46; //left ramp
int aLEDNum2 = 0; //right ramp
int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");



int bg_on = 1; //attract effect
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 4000; //Amount of time to wait before chase lights start up again 1000 == 1 second
int bgWhiteTime = 500;
String color = "white";

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
}

void loop(){
//  if (bg_on){background();}
//   Print the pin states out to serial 
  pd.pinState()->update();
  pd.pinState()->print();
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) {bg_on=1;}
  if (millis()-timeLastEvent > bgWhiteTime) {
    pd.adrLED1()->color("white");
  }
}

void checkPinStates(){
  int trigger =0;
  
  

  
  if ( pd.pinState()->J126(1) ){ // not used
//    trigger = 1; 
  }

 if ( pd.pinState()->J126(2) ){ //left pop
    pd.adrLED1()->bullet2Color("orange", "blue", 15, 0, 1);
//    pd.adrLED1()->spreadInFromPoint2Color (46, "red", "yellow", 200);
//    delay(100);
    trigger = 1; 
  }

  if ( pd.pinState()->J126(3) ){ //right pop
    pd.adrLED1()->fadeOut(50);
    pd.adrLED1()->bullet2Color("blue", "orange", 15, 0, -1);
    trigger = 1; 
  }
  if ( pd.pinState()->J126(4) ){ // lower pop
    pd.adrLED1()->fadeOut(50);   
    pd.adrLED1()->bulletFromPoint2Color("red", "blue", 30, 0, 23);
    trigger=1;
  }
  if ( pd.pinState()->J126(5) ){ // theater magnet
    pd.adrLED1()->fadeOut(50);
    pd.adrLED1()->chase2Color("red", "blue", 46,  0,  1);
    trigger=1;
  }
  
  if ( pd.pinState()->J126(6) ){ // skill shot kicker
    pd.adrLED1()->fadeOut(50);
    pd.adrLED1()->bulletFromPoint2Color("orange", "red", 30, 0, 23);
    trigger =1;
  }
  
  if ( pd.pinState()->J126(7) ){ // phone scoop
    pd.adrLED1()->fadeOut(50);
    pd.adrLED1()->bullet2Color("red", "white", 10,  1,  1);
    pd.adrLED1()->bullet2Color("red", "white", 10,  1,  1);
    pd.adrLED1()->bullet2Color("red", "white", 10,  1,  1);
    pd.adrLED1()->bullet2Color("red", "white", 10,  1,  1);
    trigger=1;
  }
  if ( pd.pinState()->J126(8) ){ // knocker
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
  pd.adrLED1()->sparkle(color,5);
  if (random(1000) == 0) {
    if (color == "white") color = "orange";
    else if (color == "orange") color = "blue";
    else color = "white";
  }
}
