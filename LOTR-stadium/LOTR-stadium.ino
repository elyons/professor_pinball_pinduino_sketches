//Eric Lyons and Tres Vogt2018
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.2 and v0.3
//Uses pinduino library

/// ---=====  NOTE ====---
/// 


#include <pinduino.h>
int aLEDNum1 = 32; //apron and backbox
int aLEDNum2 = 18; //stadium lighting
int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");



int bg_on = 1; //attract effect
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 20000; //Amount of time to wait before chase lights start up again 1000 == 1 second
int bgWhiteTime = 50;
String color = "white";

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
}

void loop(){
  if (bg_on){attract_mode();}
//   Print the pin states out to serial 
//  pd.pinState()->print();
  pd.pinState()->update();
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) {bg_on=1;}
  if (millis()-timeLastEvent > bgWhiteTime && !bg_on) {
    pd.adrLED1()->color("white");
    pd.adrLED2()->color("white");
  }
}

void checkPinStates(){
  int trigger = 0;
  
  if ( pd.pinState()->J6(1) ){ // pop flashers x3
    pd.adrLED1()->color("red");
    pd.adrLED2()->color("red");
    delay(100);
   trigger = 1; 
  }

  if ( pd.pinState()->J6(2) ){ // ring
    pd.adrLED1()->color("red");
    pd.adrLED2()->color("red ");
    delay(100);
    trigger = 1; 
  }

  if ( pd.pinState()->J6(3) ){ // back panel
    pd.adrLED1()->color("yellow");
    pd.adrLED2()->color("white");
    delay(100);
    trigger=1;
  }

  if ( pd.pinState()->J6(5) ){ // ringwraith
    pd.adrLED1()->color("purple");
    pd.adrLED2()->color("white");
    delay(100);
   trigger=1;
  }

  if ( pd.pinState()->J6(6) ){ // sword
   pd.adrLED1()->color("blue");
   pd.adrLED2()->color("white");
   delay(100);
   trigger=1;
  }
  
  if ( pd.pinState()->J6(7) ){ // destroy the ring
   pd.adrLED1()->color("red");
   pd.adrLED2()->color("white");
   trigger=1;
  }

  if ( pd.pinState()->J6(8) ){ // balrog
   pd.adrLED1()->color("red");
   pd.adrLED2()->color("white");
   delay(100);   
   trigger=1;
  }

  if ( pd.pinState()->J7(8) ){ // balrog motor
    pd.adrLED1()->color("red");
    pd.adrLED2()->color("red");
   trigger=1;
  }

  if ( pd.pinState()->J7(4) ){ // top saucer
    pd.adrLED1()->color("purple");
    pd.adrLED2()->color("white");
    delay(100); 
    trigger=1;
  }

//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   pd.pinState()->reset();
   trigger = 0;
   bg_on = 0;
   timeLastEvent = millis();
  }

//end function checkPinStates
}



void attract_mode() {
  pd.adrLED1()->sparkle(color,20);
  pd.adrLED2()->sparkle(color,20);
  if (random(1000) == 0) {
    if (color == "white") color = "green";
    else color = "white";
  }
}
