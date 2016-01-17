//Eric Lyons 2016
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.2
//Uses pinduino library

/// ---=====  NOTE ====---
/// 


#include <pinduino.h>
int aLEDNum1 = 46; //ramp
int aLEDNum2 = 7; //head
int aLEDNum3 = 1;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3);



int bg_on = 1; //attract effect
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
  if (bg_on){background();}
  pd.pinState()->update();
//   Print the pin states out to serial 
//  pd.pinState()->print();
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) {bg_on=1;}
  if (millis()-timeLastEvent > bgWhiteTime && !bg_on) {
//    pd.adrLED1()->color("white", 255);
    pd.adrLED2()->color("white", 255);
  }
}

void checkPinStates(){
  int trigger =0;
  
  if ( pd.pinState()->J6(1) ){
//    pd.adrLED1()->color("blue", 1);
//    pd.adrLED2()->color("purple", 1);
//    pd.fadeInAllAdr(200);
//    delay(200);
//    pd.fadeOutAllAdr(200);
      pd.adrLED2()->fadeIn("purple", 300);
      delay(120);
      pd.adrLED2()->fadeOut(300);
    trigger = 1; 
  }
  if ( pd.pinState()->J6(2) ){
    pd.adrLED1()->color("blue", 255);
    pd.adrLED2()->color("red", 255);
    delay(1200);
    trigger = 1; 
  }
  if ( pd.pinState()->J6(3) ){ 
    pd.adrLED1()->color("green", 255);
    pd.adrLED2()->color("cyan", 255);    
    delay(500);
    trigger = 1; 
  }
  if ( pd.pinState()->J6(4) ){ //Monger chest
  }
  if ( pd.pinState()->J6(5) ){ // whiplash
    pd.adrLED1()->color("white", 255);
    pd.adrLED2()->color("cyan", 255);
    delay(500);
    pd.adrLED1()->clear();
    pd.adrLED2()->clear();
    delay(900);
    trigger = 1; 
  }
  if ( pd.pinState()->J6(6) ){ // Make VI
    pd.adrLED1()->color("blue", 255);
    pd.adrLED2()->color("white", 255);
    delay(500);
    trigger = 1; }
  if ( pd.pinState()->J6(7) ){ //Left ramp bottom
    pd.adrLED1()->color("red", 255);
    pd.adrLED2()->color("red", 255);
    delay(1200);
    trigger = 1; 
  }
  if ( pd.pinState()->J6(8) ){ //Right ramp bottom
    pd.adrLED1()->color("red", 255);
    pd.adrLED2()->color("red", 255);
    delay(1200);
    trigger = 1;
  }
  if ( pd.pinState()->J7(6) ){ //pops
    pd.adrLED1()->color("green", 255);
    pd.adrLED2()->color("white", 255);
    delay(50);
    trigger = 1; 
  }
  if ( pd.pinState()->J7(7) ){ //Left ramp top
    pd.adrLED1()->color("yellow", 255);
    pd.adrLED2()->color("blue", 255);
    delay(1200);
    trigger = 1; 
  }
  if ( pd.pinState()->J7(8) ){//War Machine front
    pd.adrLED1()->color("green", 255);
    pd.adrLED2()->color("cyan", 255);
    delay(500);
    trigger = 1; 
  }
  if ( pd.pinState()->J7(9) ){//monger center lane
  }

//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
//   pd.adrLED1()->clear();
//   pd.adrLED2()->clear();
   pd.pinState()->reset();
   trigger =0;
   bg_on = 0;
   timeLastEvent = millis();
  }
//   delay(100);
//   pd.adrLED1()->color("white", 255);
//   pd.adrLED2()->color("white", 255);

//end function checkPinStates
}



void background() {
  pd.adrLED2()->fadeOut(1000);
  delay(1000);
  pd.adrLED1()->chase2Color("red", "orange", 35,  5,  -1);
  delay(200);
  for (int i=0; i<40; i++) {
     int cor = i*10;
     int time = 110-cor;
     if (time < 20){time = 20;}
     pd.adrLED2()->chase("red", 1,  time,  -1);
    }  
  pd.adrLED2()->fadeIn("red", 2000);
  pd.adrLED2()->fadeColor2Color("red", "purple", 3000);
  delay(2000);
  pd.adrLED2()->fadeColor2Color("purple", "white", 3000);
  delay(2000);
  pd.adrLED2()->fadeColor2Color("white", "blue", 3000);
  delay(2000);
  }

