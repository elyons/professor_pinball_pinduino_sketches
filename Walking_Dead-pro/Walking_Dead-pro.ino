//Eric Lyons (Pinside: elyons) and Alan Miller (Pinside: algrande) 2022
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.2 and v0.3
//Uses pinduino library

/// ---=====  NOTE ====---
/// 


#include <pinduino.h>
int aLEDNum1 = 24; //apron
int aLEDNum2 = 76; //ramps
int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");



int bg_on = 1; //attract effect
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 20000; //Amount of time to wait before chase lights start up again 1000 == 1 second
int bgWhiteTime = 50;
String color = "purple";

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
  
  if ( pd.pinState()->J6(1) ){ // pop flashers
    pd.adrLED1()->color("red");
    pd.adrLED2()->colorRGB(200, 100, 0); //dimmer magenta
    delay(100);
   trigger = 1; 
  }

  if ( pd.pinState()->J6(2) ){ //Prison (TOP)
    pd.adrLED1()->color("blue");
    pd.adrLED2()->color("white ");
    delay(100);
    trigger = 1; 
  }

  if ( pd.pinState()->J6(3) ){ // Prison Bottom x2
//    pd.adrLED1()->color("red");
//    pd.adrLED2()->color("red");
//    delay(100);
//    trigger=1;
  }

  if ( pd.pinState()->J6(4) ){ // Left Dome
    pd.adrLED1()->color("white");
    pd.adrLED2()->color("orange");
    delay(100);
   trigger=1;
  }

  if ( pd.pinState()->J6(5) ){ // Right Dome
    pd.adrLED1()->color("orange");
    pd.adrLED2()->color("white");
    delay(100);
   trigger=1;
  }

  if ( pd.pinState()->J6(7) ){ // Left Loop
//   pd.adrLED1()->color("blue");
//   pd.adrLED2()->color("white");
//   trigger=1;
  }

  if ( pd.pinState()->J6(8) ){ // Center Loop
//   pd.adrLED1()->clear(); 
//   pd.adrLED2()->clear(); 
//   delay(100);
//   pd.adrLED1()->color("white"); 
//   pd.adrLED2()->color("white"); 
//   delay(100);
//   pd.adrLED1()->clear(); 
//   pd.adrLED2()->clear();    
//   trigger=1;
  }

  if ( pd.pinState()->J7(4) ){ // Well Walker
    pd.adrLED1()->color("green");
    pd.adrLED2()->color("white");
    delay(100);

   trigger=1;
  }

  if ( pd.pinState()->J7(5) ){ // Right Spinner
   pd.adrLED1()->color("green");
   pd.adrLED2()->color("white");
   delay(100);
   trigger=1;
  }

  if ( pd.pinState()->J7(7) ){ // Crossbow motor
   pd.adrLED1()->clear();
   pd.adrLED2()->fadeOut(50);
   pd.adrLED2()->bullet2Color("white", "yellow", 20, 2, -1); 
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
  String L1Color = color;
  String L2Color;
  if (L1Color = "red") L2Color = "purple";
  else L2Color = "red";
  pd.adrLED1()->sparkle(L1Color,20);
  pd.adrLED2()->sparkle(L2Color,20);
  if (random(1000) == 0) {
    if (color == "purple") color = "red";
    else color = "purple";
  }
}
