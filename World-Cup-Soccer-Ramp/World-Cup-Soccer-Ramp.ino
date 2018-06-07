//Eric Lyons and Eric Bundy 2018
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.2 and v0.3
//Uses pinduino library

/// ---=====  NOTE ====---
/// 

#include <pinduino.h>
int aLEDNum1 = 150; //left ramp
int aLEDNum2 = 150; //right ramp
int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");

int bg_on = 1; //attract effect
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 4000; //Amount of time to wait before chase lights start up again 1000 == 1 second
String color = "green";
int sparkleTime = 10000; // run sparkle effect on ramps for 10 seconds when game are turned on

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
  pd.pinState()->print();
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) {bg_on=1;}
}

void checkPinStates(){
  int trigger =0;
  
  

  
 if ( pd.pinState()->J126(1) ){ // Goal cage top
    pd.adrLED1()->clear();
    pd.adrLED2()->clear();
    pd.adrLED1()->bulletFromPoint2Color("white", "white", 5, 2, 75);
    pd.adrLED2()->bulletFromPoint2Color("white", "white", 5, 2, 75);
    trigger = 1; 
  }

 if ( pd.pinState()->J126(2) ){ //goal
    pd.adrLED1()->clear();
    pd.adrLED2()->clear();
    pd.chaseAllAdr2Color("white", "white", 5, 2, 75);
    delay(100);
    trigger = 1; 
  }

  if ( pd.pinState()->J126(3) ){ //skill shot
    pd.adrLED1()->clear();
    pd.adrLED2()->clear();
    pd.adrLED1()->color("red", 255);
    pd.adrLED1()->spreadOutToPoint(54, 200);
    pd.adrLED1()->fadeOut(10);
    trigger = 1; 
  }
  if ( pd.pinState()->J126(4) ){ // jet bumpers
    pd.adrLED1()->clear();
    pd.adrLED2()->clear();
    pd.adrLED2()->bullet2Color("lime", "green", 25,  4,  -1);
    trigger=1;
  }
  if ( pd.pinState()->J126(5) ){ // goalie drive
    pd.adrLED1()->clear();
    pd.adrLED2()->clear();
    pd.adrLED2()->bullet2Color("blue", "red", 25,  4,  1);
    pd.adrLED1()->bullet2Color("red", "green", 25,  4,  1);
    trigger=1;
  }
  
  //Flashers 126-6,7,8  Are all the soccer ball direction
  //so 126-6 Lights change to Red and yellow, chase left to right 
  //126-7 lights blue and green, chase right to left
  //126-8 lights purple, and green, left to right
  
  if ( pd.pinState()->J126(6) ){ // spinning ball
    pd.adrLED1()->clear();
    pd.adrLED2()->clear();
    pd.adrLED1()->bullet2Color("red", "yellow", 10, 3, 1);
    trigger =1;
  }
  
  if ( pd.pinState()->J126(7) ){ // ball clockwise
    pd.adrLED1()->clear();
    pd.adrLED2()->clear();
    pd.adrLED1()->bullet2Color("blue", "green", 10, 3, -1);
    trigger =1;
  }
  if ( pd.pinState()->J126(8) ){ // Ball Counter-clockwise
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
    if (random(1000) == 0) {
      if (color == "green") color = "red";
      else if (color == "red") color = "blue";
      else color = "green";
    }
  }
  else if (millis()-timeLastEvent <  sparkleTime && millis()-timeLastEvent < sparkleTime+sparkleTime/2) {
    pd.adrLED1()->colorRGB(200,100,0);
    pd.adrLED2()->colorRGB(200,100,0);
  }
  else {
    pd.fadeOutAllAdr(5);
  }
}
