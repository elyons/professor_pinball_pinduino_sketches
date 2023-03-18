//Eric Lyons 2015
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3
//Uses pinduino library
//Updated in 2022 to create a version without having the LEDs turned on to which
// when no game activity is happening

#include <pinduino.h>
int N_LEDS = 27;
int R_START = 13;

int aLEDNum1 = N_LEDS;
int aLEDNum2 = 0;
int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");

int bg_chase_on = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 30000; //Amount of time to wait before chase lights start up again 1000 == 1 second
int bgWhiteTime = 50;

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
}

void loop(){
  if (bg_chase_on){backgroundChase();}
  pd.pinState()->update();
//   Print the pin states out to serial 
//  pd.pinState()->print();
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) {bg_chase_on=1;}
//  if (millis()-timeLastEvent > bgWhiteTime && bg_chase_on==0) { pd.adrLED1()->colorRGB(255, 255, 255); }
}

void checkPinStates(){
  int trigger =0;
  
  if ( pd.pinState()->J6(1) ) // pop bumpers
  {
     pd.adrLED1()->color("red", 255);
     delay(50);
     pd.adrLED1()->clear();
     delay(50);
     trigger =1;
  }
  if ( pd.pinState()->J6(2) ) // grave marker flash
  { 
     pd.adrLED1()->color("purple", 255);
     delay(50);
     pd.adrLED1()->clear();
     delay(50);
     trigger =1;
  }
  if ( pd.pinState()->J6(3) ) // electric chair
  { 
     pd.adrLED1()->color("blue", 255);
     delay(50);
     pd.adrLED1()->clear();
     delay(50);
     trigger =1; 
//    pd.adrLED1()->fadeColor2Color ("white", "orange", 100);
//    pd.adrLED1()->fadeColor2Color("orange","red",100);
//    pd.adrLED1()->fadeOut(500);
//    trigger =1;   
  }
  if ( pd.pinState()->J6(4) )  // electric chair spot
  {
     pd.adrLED1()->color("red", 255);
     delay(50);
     pd.adrLED1()->clear();
     delay(50);
     trigger =1; 
  }
  if ( pd.pinState()->J6(5) )  // right ramp
  { 
    pd.adrLED1()->clear();
    pd.adrLED1()->spreadInFromPoint2Color (R_START, "yellow", "red", 200);
    delay(50);
    pd.adrLED1()->fadeOut(100);
    trigger=1;
   }
  if ( pd.pinState()->J6(6))  // snake
  {
     pd.adrLED1()->color("green", 255);
     delay(50);
     pd.adrLED1()->clear();
     delay(50);
     trigger =1;
  }
  if ( pd.pinState()->J6(7) )  // coffin insert
  {
     pd.adrLED1()->color("red", 255);
     delay(50);
     pd.adrLED1()->clear();
     delay(50);
     trigger =1;
//    pd.adrLED1()->clear();
//    pd.adrLED1()->fadeIn("white", 100);
//    delay(50);
//   pd.adrLED1()->fadeColor2Color("white","red",100);
//    delay(50);
//    pd.adrLED1()->fadeOut(300);
//    trigger =1;
  }
  if ( pd.pinState()->J6(8) )  // electric chair insert
  { 
    pd.adrLED1()->fadeIn("red",100);
    delay(50);
    pd.adrLED1()->fadeOut(100);
    trigger =1;
  }

///J7

  if ( pd.pinState()->J7(3) )  // not used
  {
  }
  if ( pd.pinState()->J7(4) )  // flash grave marker
  { 
     pd.adrLED1()->color("purple", 150);
     delay(50);
     pd.adrLED1()->clear();
     trigger =1;
  }
  if ( pd.pinState()->J7(6) )  // grave marker motor
  {
    pd.adrLED1()->clear();
    pd.adrLED1()->spreadInFromPoint2Color (R_START, "green", "green", 100);
    delay(50);
    pd.adrLED1()->fadeOut (100);
    trigger =1;
  }
  if ( pd.pinState()->J7(7) )  // flash back panel left
  {
     pd.adrLED1()->color("blue", 255);
     delay(50);
     pd.adrLED1()->clear();
     delay(50);
     trigger =1;
  }
  if ( pd.pinState()->J7(8) )  // flash back panel right
  {
     pd.adrLED1()->color("red", 255);
     delay(50);
     pd.adrLED1()->clear();
     delay(50);
     trigger =1;
  }
  if ( pd.pinState()->J7(9) )  // flash left ramp
  {
    pd.adrLED1()->clear();
    pd.adrLED1()->spreadInFromPoint2Color (R_START, "red", "yellow", 100);
    delay(100);
    pd.adrLED1()->fadeOut(100);
    trigger=1;
  }
  if ( pd.pinState()->J7(10) )  // not used
  {
  }

//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   pd.adrLED1()->clear();
   pd.pinState()->reset();
   trigger =0;
   bg_chase_on = 0;
   timeLastEvent = millis();
  }
//  pd.adrLED1()->color("white", 200);

//end function checkPinStates
}



void backgroundChase() {
  int skip = 0; //if game has started, 
  pd.adrLED1()->clear();
  pd.adrLED1()->spreadInFromPoint2Color(R_START,"red", "blue", 500);
  for (int i=0; i<50; i=i+1){
      pd.pinState()->update();
      if (pd.pinState()->any()) {skip =1;}
      if (!skip) {delay(10);}
  }  
  if (!skip) {pd.adrLED1()->fadeOut(200);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {delay(50);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->color("red",255);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->fadeOut(200);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {delay(50);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->color("red",255);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->fadeOut(200);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {delay(50);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->color("red",255);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->fadeOut(200);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {delay(50);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->color("red",255);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->fadeOut(200);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {delay(50);}
    pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->color("red",255);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->fadeOut(200);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {delay(50);}
    pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->color("red",255);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->fadeOut(200);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {delay(50);}
    pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->color("red",255);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->fadeOut(200);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {delay(50);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->color("red",255);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->fadeOut(300);}
  for (int i=0; i<100; i=i+1){
      pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
      if (!skip) {delay(10);}
  }  
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
}
