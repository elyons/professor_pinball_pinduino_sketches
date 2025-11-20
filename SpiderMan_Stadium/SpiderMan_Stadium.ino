//Eric Lyons 2015
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.2
//Uses pinduino library

#include <pinduino.h>
int N_LEDS = 15;
int R_START = 7;

int aLEDNum1 = N_LEDS;
int aLEDNum2 = 0;
int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");

int bg_chase_on = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 30000; //Amount of time to wait before chase lights start up again 1000 == 1 second

void setup() {
//  Serial.begin(115200);
  pd.adrLED1()->strip()->updateType("RGB");
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
}

void checkPinStates(){
  int trigger =0;
  
  if ( pd.pinState()->J6(1) ){ //venom flasher
     pd.adrLED1()->color("blue", 255);
     delay(50);
     trigger =1;
  }
  if ( pd.pinState()->J6(2) ){ //sandman arrow flasher
     pd.adrLED1()->color("yellow", 255);
     delay(50);
     trigger =1; 
  }
  if ( pd.pinState()->J6(3) ){ //sandman dome flasher
     pd.adrLED1()->color("orange", 255);
     delay(50);
     trigger =1;   
  }
  if ( pd.pinState()->J6(4) ){ //green goblin flasher
     pd.adrLED1()->color("green", 255);
     delay(50);
     trigger =1; 
  }
  if ( pd.pinState()->J6(5) ){ //back panel L flasher (blue)
    pd.adrLED1()->color("blue", 255);
     delay(50);
     trigger =1; 
   }
  if ( pd.pinState()->J6(6)){ //back panel R flasher (red)
     pd.adrLED1()->color("red", 255);
     delay(50);
     trigger =1;
  }
  if ( pd.pinState()->J6(7) ){ //pop flashers
     pd.adrLED1()->color("white", 255);
     delay(50);
     trigger =1;
  }
  if ( pd.pinState()->J6(8) ){ 
//    pd.adrLED1()->fadeIn("red",100);
//    delay(50);
//    pd.adrLED1()->fadeOut(100);
//    trigger =1;
  }

///J7

  if ( pd.pinState()->J7(3) ){
  }
  if ( pd.pinState()->J7(4) ){ //green goblin
     pd.adrLED1()->color("green", 255);
     delay(50);
     trigger =1;
  }
  if ( pd.pinState()->J7(6) ){ //sandman motor
     pd.adrLED1()->color("yellow", 255);
     delay(50);
     trigger =1;
  }
  if ( pd.pinState()->J7(7) ){ //doc ock flasher
     pd.adrLED1()->color("red", 255);
     delay(50);
     trigger =1;
  }
  if ( pd.pinState()->J7(8) ){ // loop diverter
  }
  if ( pd.pinState()->J7(9) ){ // sandman flashers
     pd.adrLED1()->color("yellow", 255);
     delay(50);
     trigger =1;
  }
  if ( pd.pinState()->J7(10) ){
  }

//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   pd.pinState()->reset();
   trigger =0;
   bg_chase_on = 0;
   timeLastEvent = millis();
  }
  if (millis() - timeLastEvent > 50) {
    pd.adrLED1()->color("white");
  }

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
