//Eric Lyons 2015
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.2
//Uses pinduino library

#include <pinduino.h>
int N_LEDS = 16;
int MID = 8;

int aLEDNum1 = N_LEDS;
int aLEDNum2 = 0;
int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");

int attract_on = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
int startAttractWaitTime = 30000; //Amount of time to wait before attract lights start up again 1000 == 1 second
int bgWhiteTime = 500; // time after last event to turn all LEDs to white
int bgOn=1;
String color = "cyan"; //attract color

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
}

void loop(){
  if (attract_on){attract();}
  pd.pinState()->update();
//   Print the pin states out to serial 
//  pd.pinState()->print();
  checkPinStates();
  if (millis()-timeLastEvent > startAttractWaitTime) {attract_on=1;}
  if (millis()-timeLastEvent > bgWhiteTime && !attract_on) {
    pd.adrLED1()->color("cyan", 255);
  }
}

void checkPinStates(){
  int trigger =0;
  
  if ( pd.pinState()->J126(1) ){ // billion
  pd.adrLED1()->fadeOut(10);
  for (int i=0; i<3; i++) {
     pd.adrLED1()->bulletFromPoint2Color("green","blue", 4, 50, MID);
    }
    trigger = 1; 
  }

  if ( pd.pinState()->J126(2) ){ //left ramp shuttle
    pd.adrLED1()->fadeOut(10);
    pd.adrLED1()->bulletFromPoint2Color("blue","cyan", 8, 50, MID);
    trigger = 1; 
  }

  if ( pd.pinState()->J126(3) ){ //jackpot
    pd.adrLED1()->fadeOut(10);
    pd.adrLED1()->bulletFromPoint2Color("red","green", 4, 50, MID);
    trigger = 1; 
  }
  if ( pd.pinState()->J126(4) ){ // right shuttle skill shot
    pd.adrLED1()->fadeOut(10);
    pd.adrLED1()->bulletFromPoint2Color("green","blue", 10, 20, MID);    
    trigger=1;
  }
  if ( pd.pinState()->J126(5) ){ // left helmet
    pd.adrLED1()->fadeOut(10);
    pd.adrLED1()->bullet2Color("green", "cyan",4, 30, -1);
    pd.adrLED1()->bullet2Color("cyan", "green",4, 30, 1);
    trigger = 1; 
  }
  
  if ( pd.pinState()->J126(6) ){ // right helmet
    pd.adrLED1()->fadeOut(10);
    pd.adrLED1()->multiBullet2Color("blue", "blue", 2, 40, 1, 8);
    pd.adrLED1()->multiBullet2Color("blue", "cyan", 2, 40, 1, 8);
    pd.adrLED1()->multiBullet2Color("cyan", "cyan", 2, 40, 1, 8);
    trigger = 1; 
  }
  
  if ( pd.pinState()->J126(7) ){ //right boob
    pd.adrLED1()->fadeOut(10);
    pd.adrLED1()->bulletFromPoint2Color("cyan","blue", 4, 50, MID);
    trigger = 1; 
  }
  if ( pd.pinState()->J126(8) && ! pd.pinState()->J126(7) ){// 8==left boob, 7==right boob
    pd.adrLED1()->fadeOut(10);
    pd.adrLED1()->bulletFromPoint2Color("blue","cyan", 4, 50, MID);
    trigger = 1;
  }

//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
    timeLastEvent = millis();
    pd.adrLED1()->clear();
    pd.pinState()->reset();
    attract_on = 0;
    trigger =0;
  }

//end function checkPinStates
}



void attract() {
  pd.adrLED1()->sparkle(color,10, 30);
  if (random(1000) == 0) {
    if (color == "cyan") color = "blue";
    else if (color == "blue") color = "green";
    else if (color == "green") color = "white";
    else color = "cyan";
  } 
}


