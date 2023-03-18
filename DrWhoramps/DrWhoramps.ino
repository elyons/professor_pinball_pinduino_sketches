//Eric Lyons and Eric Bundy 2018
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.2 and v0.3
//Uses pinduino library

/// ---=====  NOTE ====---
/// 

#include <pinduino.h>
int aLEDNum1 = 120; //left ramp
int aLEDNum2 = 145; //right ramp
int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");

int bg_on = 1; //attract effect
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 4000; //Amount of time to wait before chase lights start up again 1000 == 1 second
String color = "green";
int sparkleTime = 10000; // run sparkle effect on ramps for 10 seconds when game are turned on
int attractHold = 0; // variable to hold solid color in attract mode
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
  
  

  
 if ( pd.pinState()->J126(1) ){ // 
    pd.adrLED1()->clear();
    pd.adrLED2()->clear();
    pd.adrLED1()->bulletFromPoint2Color("white", "white", 5, 2, 75);
    pd.adrLED2()->bulletFromPoint2Color("white", "white", 5, 2, 75);
    trigger = 1; 
  }

 if ( pd.pinState()->J126(2) ){ //
    pd.adrLED1()->clear();
    pd.adrLED2()->clear();
    pd.chaseAllAdr2Color("white", "white", 5, 2, 75);
    delay(100);
    trigger = 1; 
  }

  if ( pd.pinState()->J126(3) ){ //
    pd.adrLED1()->clear();
    pd.adrLED2()->clear();
    pd.adrLED1()->fadeIn("red", 50);
    pd.adrLED1()->spreadOutToPoint(54, 200);
    pd.adrLED1()->fadeOut(10);
    trigger = 1; 
  }
  if ( pd.pinState()->J126(4) ){ // 
    pd.adrLED1()->clear();
    pd.adrLED2()->clear();
    pd.adrLED2()->bullet2Color("lime", "green", 25,  4,  -1);
    trigger=1;
  }
  if ( pd.pinState()->J126(5) ){ // 
    pd.adrLED1()->clear();
    pd.adrLED2()->clear();
    pd.adrLED2()->bullet2Color("blue", "red", 25,  4,  1);
    pd.adrLED1()->bullet2Color("red", "green", 25,  4,  1);
    trigger=1;
  }
  
  if ( pd.pinState()->J126(6) ){ // 
    pd.adrLED1()->clear();
    pd.adrLED2()->clear();
    pd.adrLED1()->bullet2Color("red", "yellow", 10, 3, 1);
    trigger =1;
  }
  
  if ( pd.pinState()->J126(7) ){ // 
    pd.adrLED1()->clear();
    pd.adrLED2()->clear();
    pd.adrLED2()->bullet2Color("blue", "green", 10, 3, -1);
    trigger =1;
  }
  if ( pd.pinState()->J126(8) ){ // 
    pd.adrLED1()->clear();
    pd.adrLED2()->clear();
    pd.adrLED1()->bullet2Color("purple", "green", 10, 3, 1);
    trigger =1;
  }

//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
    pd.adrLED1()->clear();
    pd.adrLED2()->clear();
   pd.pinState()->reset();
   trigger =0;
   bg_on = 0;
   timeLastEvent = millis();
  }

//end function checkPinStates
}



void background() {
  if (millis()-timeLastEvent <  sparkleTime) {
    pd.adrLED1()->sparkle(color,20);
    pd.adrLED2()->sparkle(color,20);
    if (random(200) == 0) {
      if (color == "green") color = "red";
      else if (color == "red") color = "blue";
      else if (color == "blue") color = "orange";
      else color = "green";
    }
  }
  else if ((millis()-timeLastEvent >  sparkleTime) && (millis()-timeLastEvent < sparkleTime+sparkleTime/2) && attractHold == 0 ){
    pd.fadeOutAllAdr(100);
    pd.fadeAllAdrRGB2RGB(0,0,0,200,50,0,1);
    attractHold = 1;
  }
  else {
    pd.fadeOutAllAdr(20);
    timeLastEvent = millis();
    attractHold = 0;
  }
}
