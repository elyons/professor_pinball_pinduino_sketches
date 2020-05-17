//Eric Lyons 2016
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.2 and v0.3
//Uses pinduino library

/// ---=====  NOTE ====---
/// 


#include <pinduino.h>
int aLEDNum1 = 46; //ramp
int aLEDNum2 = 50; //head
int aLEDNum3 = 1;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");



int bg_on = 1; //attract effect
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 30000; //Amount of time to wait before chase lights start up again 1000 == 1 second
int bgWhiteTime = 500;

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
    pd.adrLED1()->clear();
    pd.adrLED2()->color("white");
  }
}

void checkPinStates(){
  int trigger =0;
  
  

  
  if ( pd.pinState()->J126(1) ){ // billion
    pd.adrLED2()->fadeOut(200);
    pd.adrLED2()->fadeIn("red", 200);
    delay(300);
    pd.adrLED2()->fadeOut(200);
    trigger = 1; 
  }

 if ( pd.pinState()->J126(2) ){ //left ramp shuttle
    pd.adrLED2()->color("blue", 255);
    pd.adrLED1()->chase2Color("purple","blue", 2,  10,  -1);
    pd.adrLED2()->fadeOut(1000);
    trigger = 1; 
  }

  if ( pd.pinState()->J126(3) ){ //jackpot
    pd.adrLED1()->chase2ColorFromPoint(23, "green", "red", 10,5);
    trigger = 1; 
  }
  if ( pd.pinState()->J126(4) ){ // right shuttle skill shot
    pd.adrLED2()->color("red", 255);
    pd.adrLED2()->fadeOut(200);
    trigger=1;
  }
  if ( pd.pinState()->J126(5) ){ // left helmet
    pd.adrLED2()->color("yellow", 255);
    delay(100);
    pd.adrLED2()->clear();    
    trigger = 1; 
    trigger = 1; 
  }
  
  if ( pd.pinState()->J126(6) ){ // right helmet
    pd.adrLED2()->color("purple", 255);
    delay(100);
    pd.adrLED2()->clear();    
    trigger = 1; 
  }
  
  if ( pd.pinState()->J126(7) ){ //right boob
    pd.adrLED2()->color("red", 255);
    delay(100);
    pd.adrLED2()->clear();
    trigger = 1; 
  }
  if ( pd.pinState()->J126(8) && ! pd.pinState()->J126(7) ){ // 8==left boob, 7==right boob
    pd.adrLED2()->color("blue", 255);
    pd.adrLED1()->chase2Color("red", "orange", 60,  1,  -1);
    pd.adrLED2()->clear();
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
  pd.adrLED1()->sparkle("white", 20);
  pd.adrLED2()->sparkle("purple", 20);
  }
