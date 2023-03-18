//Eric Lyons 2016
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3
//Uses pinduino library

#include <pinduino.h>

int aLEDNum1 = 50; // Number of LEDs in LED strip 1
int aLEDNum2 = 50; // Number of LEDs in LED strip 2

pinduino pd (aLEDNum1, aLEDNum2, "Nano");

int attract_on = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
int attractWaitTime = 20000; //Amount of time to wait before chase lights start up again 1000 == 1 second
String color = "white"; // color of LEDs that attract mode starts with

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
    pd.adrLED1()->color("blue",255);
    pd.adrLED2()->color("blue",255);
    delay(500);
    trigger=1;
  }
  if ( pd.pinState()->J126(2) ){ 
    trigger=1;
  }
  if ( pd.pinState()->J126(3) ){ 
    trigger=1;
  }
  if ( pd.pinState()->J126(4) ){ 
    trigger=1;
  }
  if ( pd.pinState()->J126(5) ){ 
    trigger=1;
  }
  if ( pd.pinState()->J126(6) ){ 
    trigger=1;
  }
  if ( pd.pinState()->J126(7) ){ 
//    trigger=1;
  }
  if ( pd.pinState()->J126(8) ){ 
    trigger=1;
  }
  if ( pd.pinState()->J126(9) ){ 
    trigger=1;
  }
  if ( pd.pinState()->J126(10) ){ 
    trigger=1;
  }
  if ( pd.pinState()->J126(11) ){ 
    trigger=1;
  }
  if ( pd.pinState()->J126(12) ){ 
    trigger=1;
  }
  if ( pd.pinState()->J126(13) ){ //extended WPC with extra 4-pin plug
    trigger=1;
  }
  if ( pd.pinState()->J126(14) ){  //extended WPC with extra 4-pin plug
    trigger=1;
  }
  if ( pd.pinState()->J126(15) ){  //extended WPC with extra 4-pin plug
    trigger=1;
  }
  if ( pd.pinState()->J126(16) ){  //extended WPC with extra 4-pin plug
    trigger=1;
  }

  
//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   pd.adrLED1()->clear();
   pd.adrLED2()->clear();
   pd.pinState()->reset();
   trigger =0;
   attract_on = 0;
   timeLastEvent = millis();
  }
//end function checkPinStates
}



void attractMode() {
  pd.adrLED1()->sparkle(color,1);
  pd.adrLED2()->sparkle(color,1);
  if (random(1000) == 0) {
    if (color == "white") color = "blue";
    else if (color == "blue") color = "red";
    else color = "white";
  }
}


