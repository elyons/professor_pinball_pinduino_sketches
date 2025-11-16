//Eric Lyons 2018
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3
//Uses pinduino library

#include <pinduino.h>

int aLEDNum1 = 100;
int aLEDNum2 = 0;

pinduino pd (aLEDNum1, aLEDNum2, "Nano");

int attract_on = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
int attractWaitTime = 20000; //Amount of time to wait before chase lights start up again 1000 == 1 second
String color = "blue"; // color of LEDs that attract mode starts with

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.pinState()->reset();
}

void loop(){
  pd.pinState()->update();
//   Print the pin states out to serial 
//  pd.pinState()->print();
  checkPinStates();
  if (millis()-timeLastEvent > attractWaitTime) { attract_on=1; }
  if (attract_on){attractMode();}
}

void checkPinStates(){
  int trigger =0;
  
  if ( pd.pinState()->J126(1) ){
 }
  if ( pd.pinState()->J126(2) ){ 
  }
  if ( pd.pinState()->J126(3) ){  // left mountain
  }
  if ( pd.pinState()->J126(4) ){ // Upper left playfield
    pd.adrLED1()->bullet2Color("blue", "white", 10, 5, 1);
    trigger=1;
  }
  if ( pd.pinState()->J126(5) ){ // Insantify falls
  }
  if ( pd.pinState()->J126(6) ){ 
  }
  if ( pd.pinState()->J126(7) ){ //whirlpool enter
    pd.adrLED1()->chase2ColorFromPoint(50, "blue", "white", 15, 1);
    trigger=1;
  }
  if ( pd.pinState()->J126(8) ){
  }
  if ( pd.pinState()->J126(9) ){ 
  }
  if ( pd.pinState()->J126(10) ){ 
  }
  if ( pd.pinState()->J126(11) ){ 
  }
  if ( pd.pinState()->J126(12) ){ 
  }
  if ( pd.pinState()->J126(13) ){ //extended WPC with extra 4-pin plug
  }
  if ( pd.pinState()->J126(14) ){  //extended WPC with extra 4-pin plug
  }
  if ( pd.pinState()->J126(15) ){  //extended WPC with extra 4-pin plug
  }
  if ( pd.pinState()->J126(16) ){  //extended WPC with extra 4-pin plug
  }

  
//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   pd.adrLED1()->clear();
   pd.pinState()->reset();
   trigger =0;
   attract_on = 0;
   timeLastEvent = millis();
  }
//end function checkPinStates
}



void attractMode() {
  pd.adrLED1()->sparkle(color,20);
}
