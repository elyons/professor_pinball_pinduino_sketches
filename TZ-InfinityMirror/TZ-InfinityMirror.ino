//Eric Lyons 2016
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3
//Uses pinduino library

#include <pinduino.h>

int aLEDNum1 = 73;
int aLEDNum2 = 17;
int aLEDNum3 = 0;
int N_LEDS=aLEDNum1;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");

int attract_on = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 20000; //Amount of time to wait before attract lights start up again 1000 == 1 second
int bgWaitTime = 100; //Amount of time to wait before backglass turns on
int bgOn = 0; // is background on
String color = "blue"; //attract color


void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
}

void loop(){
  pd.pinState()->update();
  pd.adrLED2()->sparkle("white",20);
  //   Print the pin states out to serial 
//  pd.pinState()->print();
  checkPinStates();

//  if (millis()-timeLastEvent > startChaseWaitTime) {attract_on=1;}
//  if (millis()-timeLastEvent > bgWaitTime && bgOn == 0) {
//    pd.adrLED1()->fadeIn("blue", 500);
//    bgOn =1;
//  }
////  if ( attract_on){attract(color);}

  pd.adrLED1()->sparkle(color,20);
  if (random(1000) == 0) {
      if (color == "blue") color = "red";
      else if (color == "red") color = "green";
//      else if (color == "white") color = "green";
      else color = "blue";
  }
}

void checkPinStates(){
  int trigger =0;
  if ( pd.pinState()->J126(1) ){ // Bumpers
    pd.adrLED1()->fadeOut(50);    
    pd.adrLED1()->multiBullet2Color("orange", "red", 3, 0, 1, 5);
    trigger=1;
  }
  if ( pd.pinState()->J126(2) ){ //Power Payoff
    pd.adrLED1()->fadeOut(50);    
    pd.adrLED1()->fadeIn("red", 50);
    delay(50);
    pd.adrLED1()->fadeOut(50);    
    trigger=1;
  }
  if ( pd.pinState()->J126(3) ){ // Mini Playfield
    pd.adrLED1()->fadeOut(50);        
    pd.adrLED1()->spreadInFromPoint2RGB(N_LEDS/2,150,150,150, 0,0,255, 500);
    delay(300);
    pd.adrLED1()->fadeOut(200);
    trigger=1;
  }
  if ( pd.pinState()->J126(4) ){ //Upper left ramp
    pd.adrLED1()->fadeOut(50);    
     pd.adrLED1()->multiBullet2RGB(150,150,150, 0,0,255, 3, 0, -1, 2);
//   pd.adrLED1()->chase2Color("white", "blue",10, 10, -1);
    trigger=1;
  }
  if ( pd.pinState()->J126(5) ){ //Left Magnet
  }
  if ( pd.pinState()->J126(6) ){ // Upper right Magenet
  }
  if ( pd.pinState()->J126(7) ){ // Lower right magnet
  }
  if ( pd.pinState()->J126(8) ){ //Gumball motor
    pd.adrLED1()->fadeOut(50);
    pd.adrLED1()->fadeIn("green", 500);    
    pd.adrLED1()->fadeColor2Color("green", "red", 500);
    pd.adrLED1()->fadeColor2Color("red", "blue",500);
    trigger=1;
  }
  if ( pd.pinState()->J126(9) ){ 
    pd.adrLED1()->fadeOut(50);    
    pd.adrLED1()->spreadInFromPoint2Color(N_LEDS/2, "yellow", "red", 5);
    pd.adrLED1()->fadeOut(200);
    trigger=1;
  }

  
//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   pd.adrLED1()->clear();
   pd.pinState()->reset();
   trigger =0;
   attract_on = 0;
   bgOn = 0;
   timeLastEvent = millis();
   color = "blue";
  }
//end function checkPinStates
}



void attract(String color) {
  int skip = 0; //if game has started, 
//  pd.adrLED1()->sparkle(color,20);
//  if (bgOn==0) {
//    pd.adrLED1()->fadeIn("blue", 1000);
//  }
//  if (!skip) {pd.adrLED1()->fadeColor2Color("blue", "white", 1000);}
//  delay(1000);
//  if (pd.pinState()->any()) {skip =1;}
//  if (!skip) {pd.adrLED1()->fadeOut(1000);}
//  if (pd.pinState()->any()) {skip =1;}
//  delay(1000);
//  if (!skip) {pd.adrLED1()->bullet2Color("white", "blue",100, 20, 1);}
//  if (pd.pinState()->any()) {skip =1;}
//  if (!skip) {pd.adrLED1()->bullet2Color("blue", "white",100, 20, 1);}
//  if (pd.pinState()->any()) {skip =1;}
//  pd.adrLED1()->fadeOut(50);
//  delay(500);
  bgOn = 1; 

}


