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
int bgWhiteTime = 1000;

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
}

void loop(){
  if (bg_on){background();}
  for (int i=0; i<1000; i=i+1) { //check pinstates for a while    
    pd.pinState()->update();
  }
//   Print the pin states out to serial 
//  pd.pinState()->print();
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) {bg_on=1;}
  if (millis()-timeLastEvent > bgWhiteTime && !bg_on) {
//    pd.adrLED1()->color("white", 255);
    pd.adrLED1()->clear();
    pd.adrLED2()->color("white", 255);
  }
}

void checkPinStates(){
  int trigger =0;
  
  

  
  if ( pd.pinState()->J6(1) ){ // billion
    for (int i=0; i<100; i++) {
     pd.adrLED2()->chase2Color("red", "blue", 1,  20,  -1);
     pd.adrLED2()->chase2Color("blue", "red", 1,  20,  1);
    }
    trigger = 1; 
  }

 if ( pd.pinState()->J6(2) ){ //left ramp shuttle
//    pd.adrLED1()->color("blue", 255);
    pd.adrLED2()->color("blue", 255);
    pd.adrLED1()->chase("blue", 2,  5,  -1);
    pd.adrLED2()->fadeOut(1000);
    trigger = 1; 
  }

  if ( pd.pinState()->J6(3) ){ //jackpot
    pd.adrLED1()->chase2ColorFromPoint(23, "green", "red", 10,5);
    trigger = 1; 
  }
  if ( pd.pinState()->J6(4) ){ // right shuttle skill shot
    pd.adrLED2()->color("red", 255);
    pd.adrLED2()->fadeOut(200);
    trigger=1;
  }
  if ( pd.pinState()->J6(5) ){ // left helmet
    pd.adrLED2()->color("yellow", 255);
    delay(100);
    pd.adrLED2()->clear();    
    trigger = 1; 
    trigger = 1; 
  }
  
  if ( pd.pinState()->J6(6) ){ // right helmet
    pd.adrLED2()->color("purple", 255);
    delay(100);
    pd.adrLED2()->clear();    
    trigger = 1; 
  }
  
  if ( pd.pinState()->J6(7) ){ //right boob
    pd.adrLED2()->color("red", 255);
    delay(100);
    pd.adrLED2()->clear();
    trigger = 1; 
  }
  if ( pd.pinState()->J6(8) && ! pd.pinState()->J6(7) ){ // 8==left boob, 7==right boob
    pd.adrLED2()->color("blue", 255);
    pd.adrLED1()->chase2Color("red", "orange", 60,  1,  -1);
    pd.adrLED2()->clear();
    trigger = 1;
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

