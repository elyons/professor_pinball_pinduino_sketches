//Eric Lyons 2020
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.2 and v0.3
//Uses pinduino library

/// ---=====  NOTE ====---
/// This is a draft sketch that was made without having a Jackbot to use

#include <pinduino.h>


int aLEDNum1 = 40; //ramp
int aLEDNum2 = 0; 
int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");



int bg_on = 1; //attract effect
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 20000; //Amount of time to wait before chase lights start up again 1000 == 1 second
String color = "white"; //attract color
int bg_style = 1;

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
}

void loop(){
  if (bg_on){background();}
  pd.pinState()->update();
//   Print the pin states out to serial 
//  pd.pinState()->print();
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) {bg_on=1;}
}

void checkPinStates(){
  int trigger =0;
 
  if ( pd.pinState()->J126(1) ){ // center visor flasher
    pd.adrLED1()->RGBBand(10, 0,0,255, 11);
    delay(200);
    pd.adrLED1()->clear();
    pd.adrLED1()->RGBBand(30, 255,0,0, 11);
    delay(200);
    pd.adrLED1()->clear();  
    trigger = 1; 
  }

  if ( pd.pinState()->J126(2) ){ //pinbot face flasher
    pd.adrLED1()->RGBBand(10, 0,0,255, 11);
    pd.adrLED1()->RGBBand(30, 255,0,0, 11);
    delay(200);
    pd.adrLED1()->clear();  
    trigger = 1; 
  }

  if ( pd.pinState()->J126(3) ){ // jet bumpers flasher
    pd.adrLED1()->color("red");
    delay(200);
    pd.adrLED1()->color("blue");
    delay(200);
    pd.adrLED1()->clear();      
    trigger = 1; 
  }

  if ( pd.pinState()->J126(4) ){ // lower left flasher
    pd.adrLED1()->bullet("red", 3, 10,  1);
    trigger = 1;
  }

  if ( pd.pinState()->J126(5) ){ // middle left flasher
    pd.adrLED1()->bullet("blue", 3, 10,  1);
    trigger = 1; 
  }
  
  if ( pd.pinState()->J126(6) ){ // lower right flasher
    pd.adrLED1()->bullet("purple", 3, 10,  -1);
    trigger = 1; 
    trigger = 1; 
  }
  
  if ( pd.pinState()->J126(7) ){ //back panel 1 (lt) flasher
    pd.adrLED1()->bullet("red", 3, 1,  1);
    trigger = 1; 
  }

  if ( pd.pinState()->J126(8) ){ //back panel 2 flasher
    trigger = 1;
  }

  if ( pd.pinState()->J126(13) ){ //back panel 3 flasher
    trigger = 1;
  }

  if ( pd.pinState()->J126(14) ){ //back panel 4 flasher
    trigger = 1;
  }

  if ( pd.pinState()->J126(15) ){ //back panel 5 (rt) flasher
    pd.adrLED1()->bullet("blue", 3  , 1,  -1);
    trigger = 1;
  }

  if ( pd.pinState()->J126(16) ){ // visor motor
    pd.adrLED1()->bullet2Color("blue", "red", 10, 10, 1);
    pd.adrLED1()->bullet2Color("red", "blue", 10, 10, -1);
    trigger = 1;
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
   if (bg_style) {
    pd.adrLED1()->sparkle(color,20);
    if (random(1000) == 0) {
        if (color == "white") color = "red";
        else if (color == "red") color = "blue";
        else color = "white";
    }
  }
  else {
    pd.adrLED1()->dataStreamNoTail2Color("blue", "red", 20, 20, 1);
    bg_style=1;
  }
  if (random(1000) == 0) {
    if (bg_style) { bg_style = 0;}
    else {bg_style = 1;}
  }
  }
