//Eric Lyons 2015
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3
//Uses pinduino library

#include <pinduino.h>
int N_LEDS = 27;
int R_START = 14;

int aLEDNum1 = N_LEDS;
int aLEDNum2 = 0;
int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");

int attractMode_on = 1;
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
  if (attractMode_on){attractMode();}
  pd.pinState()->update();
//   Print the pin states out to serial 
//  pd.pinState()->print();
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) {attractMode_on=1;}
  if (millis()-timeLastEvent > bgWhiteTime && attractMode_on==0) { pd.adrLED1()->color("white", 255); }
}

void checkPinStates(){
  int trigger =0;
  
  if ( pd.pinState()->J6(1) ){
      pd.adrLED1()->color("red", 255);
      delay(50);
      pd.adrLED1()->clear();
      trigger =1;
  }
  if ( pd.pinState()->J6(2) ){ 
      pd.adrLED1()->color("red", 255);
      delay(50);
      pd.adrLED1()->clear();
      trigger =1;
  }
  if ( pd.pinState()->J6(3) ){ 
      pd.adrLED1()->color("red", 255);
      delay(50);
      pd.adrLED1()->clear();
      trigger =1;

  }
  if ( pd.pinState()->J6(4) ){ //NOT USED
  }
  if ( pd.pinState()->J6(5) ){
    pd.adrLED1()->clear();
    pd.adrLED1()->spreadInFromPoint2Color (R_START, "green", "red", 300);
    delay(500);
    pd.adrLED1()->fadeOut(200);
    trigger=1;
  }
  if ( pd.pinState()->J6(6)){
    pd.adrLED1()->clear();
    pd.adrLED1()->spreadInFromPoint2Color (R_START, "green", "blue", 300);
    delay(500);
    pd.adrLED1()->spreadOutFromPoint (R_START, 400);
    trigger =1;
  }
  if ( pd.pinState()->J6(7) ){
    pd.adrLED1()->clear();
    delay(50);
    pd.adrLED1()->fadeIn("red", 3000);
    delay(1000);
    pd.adrLED1()->fadeOut(3000);
    delay(50);
    trigger =1;
  }
  if ( pd.pinState()->J6(8) ){ 
    pd.adrLED1()->fadeColor2Color("orange","red",200);
    delay(500);
    pd.adrLED1()->fadeColor2Color("red","orange",200);
    trigger =1;
  }

///J7

  if ( pd.pinState()->J7(3) ){
  }
  if ( pd.pinState()->J7(4) ){ 
  }
  if ( pd.pinState()->J7(6) ){
  }
  if ( pd.pinState()->J7(7) ){
  }
  if ( pd.pinState()->J7(8) ){
    pd.adrLED1()->fadeColor2Color("orange","red",200);
    delay(500);
    pd.adrLED1()->fadeColor2Color("red","orange",200);
    trigger=1;
  }
  if ( pd.pinState()->J7(9) ){
    pd.adrLED1()->clear();
    pd.adrLED1()->spreadInFromPoint2Color (R_START, "green", "blue", 400);
    delay(300);
    pd.adrLED1()->fadeOut(200);
    delay(300);
    trigger=1;
  }
  if ( pd.pinState()->J7(10) ){
  }

//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   pd.adrLED1()->clear();
   pd.pinState()->reset();
   trigger =0;
   attractMode_on = 0;
   timeLastEvent = millis();
  }

//end function checkPinStates
}



void attractMode() {
  pd.adrLED1()->fire(20,10);
}


