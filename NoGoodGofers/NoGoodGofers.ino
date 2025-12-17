//Eric Lyons 2018
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.2 and v0.3
//Uses pinduino library

/// ---=====  NOTE ====---
/// 


#include <pinduino.h>
int aLEDNum1 = 34; //left ramp
int aLEDNum2 = 0; //right ramp
int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");



int bg_on = 1; //attract effect
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 20000; //Amount of time to wait before chase lights start up again 1000 == 1 second
int bgWhiteTime = 50 ;
String color = "white";

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
//  pd.pinState()->print();
  pd.pinState()->update();
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) {bg_on=1;}
  if (millis()-timeLastEvent > bgWhiteTime && !bg_on) {
    pd.adrLED1()->colorRGB(128,128,128);
  }
}

void checkPinStates(){
  int trigger =0;
  
  if ( pd.pinState()->J126(12) ){ // upper right 1 (blue)
//   pd.adrLED1()->fadeOut(50); 
//   pd.adrLED1()->bullet2Color("blue", "white", 20, 2, 1);
    pd.adrLED1()->color("blue");
    delay(100);
   trigger = 1; 
  }

  if ( pd.pinState()->J126(11) ){ //upper right 2 (red)
//   pd.adrLED1()->fadeOut(50); 
//   pd.adrLED1()->bullet2Color("red", "orange", 20, 2, 1);
    pd.adrLED1()->color("red");
    delay(100);
    trigger = 1; 
  }

  if ( pd.pinState()->J126(10) ){ //upper right 3 (white)
   pd.adrLED1()->fadeOut(50); 
     pd.adrLED1()->bullet2Color("green", "red", 20, 2, 1);
//    pd.adrLED1()->color("green");
//    delay(100);
    trigger = 1; 
  }
  if ( pd.pinState()->J126(9) ){ // upper playfield right
   pd.adrLED1()->fadeOut(50); 
    pd.adrLED1()->bulletFromPoint2Color("white", "green", 17, 5, 17);
    trigger=1;
  }
  
  if ( pd.pinState()->J126(7) ){ // upper playfield left
   pd.adrLED1()->fadeOut(50); 
    pd.adrLED1()->bulletFromPoint2Color("green", "white", 17, 5, 17);
    trigger =1;
  }
  
  if ( pd.pinState()->J126(6) ){ // upper left 3 (white)
    pd.adrLED1()->color("green");
    delay(50);
    trigger = 1;
  }
  if ( pd.pinState()->J126(5) ){ // upper left 2 (red)
    pd.adrLED1()->color("red");
    delay(50);
    trigger = 1;
  }
  if ( pd.pinState()->J126(4) ){ // upper left 1 (blue)
    pd.adrLED1()->color("blue");
    delay(50);
    trigger = 1;
  }
  if ( pd.pinState()->J126(3) ){ // 
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
  pd.adrLED1()->sparkle(color,30);
  if (random(1000) == 0) {
    if (color == "white") color = "green";
    else if (color == "green") color = "blue";
    else color = "white";
  }
}
