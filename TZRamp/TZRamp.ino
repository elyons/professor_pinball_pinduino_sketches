//Eric Lyons 2016
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3
//Uses pinduino library

#include <pinduino.h>

int aLEDNum1 = 44;
int aLEDNum2 = 0;
int aLEDNum3 = 0;
int N_LEDS=aLEDNum1;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");

int bg_chase_on = 0;
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 20000; //Amount of time to wait before chase lights start up again 1000 == 1 second
int whiteWaitTime = 100; //Amount of time to wait before gumball goes to white

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
}

void loop(){
  for (int i = 0; i < 1000; i = i + 1) { //check pinstates for a while
    pd.pinState()->update();
  }
  
//   Print the pin states out to serial 
  pd.pinState()->print();
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) {bg_chase_on=1;}
//  if (millis()-timeLastEvent > whiteWaitTime) {
//    pd.adrLED1()->color("white", 255);
//}
  if (bg_chase_on){backgroundChase();}

}

void checkPinStates(){
  int trigger =0;
  
  if ( pd.pinState()->J126(1) ){ // Bumpers
    pd.adrLED1()->chase("white",1, 5, -1);
    pd.adrLED1()->chase("white",1, 5, 1);
    trigger=1;
  }
  if ( pd.pinState()->J126(2) ){ //Power Payoff
    pd.adrLED1()->spreadInFromPoint2Color (1, "red", "orange", 500);
    delay(500);
    pd.adrLED1()->fadeOut(500);    
    trigger=1;
  }
  if ( pd.pinState()->J126(3) ){ // Mini Playfield
    pd.adrLED1()->spreadInFromPoint2Color(N_LEDS/2,"red", "blue", 1000);
    delay(500);
    pd.adrLED1()->fadeOut(200);
    trigger=1;
  }
  if ( pd.pinState()->J126(4) ){ //Upper left ramp
    pd.adrLED1()->chase2Color("red", "blue",N_LEDS, 10, -1);
    trigger=1;
  }
  if ( pd.pinState()->J126(5) ){ //Left Magnet
 //   pd.adrLED1()->chase2Color("green", "yellow",N_LEDS/8, 10, -1);
 //   trigger=1;
  }
  if ( pd.pinState()->J126(6) ){ // Upper right Magenet
    trigger=1;
  }
  if ( pd.pinState()->J126(7) ){ // Lower right magnet
    pd.adrLED1()->chase2ColorFromPoint(N_LEDS/2,"red","green", 10,5);
    trigger=1;
  }
  if ( pd.pinState()->J126(8) ){ //Gumball motor
    pd.adrLED1()->chase2Color("red", "green", N_LEDS, 1, -1);
    pd.adrLED1()->chase2Color("green", "blue",N_LEDS, 1, 1);
    pd.adrLED1()->chase2Color("blue", "red", N_LEDS, 1, -1);
    trigger=1;
  }
  if ( pd.pinState()->J126(9) ){ 
    pd.adrLED1()->spreadInFromPoint2Color(1, "yellow", "red", 5);
    pd.adrLED1()->fadeOut(200);
    trigger=1;
  }

  
//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   pd.adrLED1()->clear();
   pd.pinState()->reset();
   trigger =0;
   bg_chase_on = 0;
   timeLastEvent = millis();
  }
//end function checkPinStates
}



void backgroundChase() {
  pd.adrLED1()->clear();
  int skip = 0; //if game has started, 
  if (!skip) {pd.adrLED1()->fadeIn("red", 1000);}
  if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->fadeColor2Color("red", "white", 1000);}
  if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->fadeOut(1000);}
  if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->chase2Color("white", "purple",N_LEDS/4, 20, -1);}
  if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->chase2Color("purple", "red",N_LEDS/4, 20, 1);}
  if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->chase2Color("red", "yellow",N_LEDS/4, 20, -1);}
  if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->chase2Color("yellow", "green",N_LEDS/4, 20, 1);}
  if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->chase2Color("green", "sky",N_LEDS/4, 20, -1);}
  if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->chase2Color("sky", "blue",N_LEDS/4, 20, 1);}
  if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->chase2Color("blue", "purple",N_LEDS/4, 20, -1);}
  if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->chase2Color("purple", "red",N_LEDS/4, 20, 1);}
  for (int i = 0; i < 1000; i = i + 1) { //check pinstates for a while
    pd.pinState()->update();
  }

}


