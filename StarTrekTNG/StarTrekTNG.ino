//Eric Lyons 2018
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3 (Nano!)
//Uses pinduino library

#include <pinduino.h>
int R_START = 46;

int aLEDNum1 = 90;
int aLEDNum2 = 25;
int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");

int attractOn = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
unsigned long startChaseWaitTime = 40000; //Amount of time to wait before chase lights start up again 1000 == 1 second
String color = "blue"; //attract color
int attract_style = 1;
void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
}

void loop(){
  if (attractOn){attractMode();}
  pd.pinState()->update();
//   Print the pin states out to serial 
//  pd.pinState()->print();
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) {attractOn=1;}
}

void checkPinStates(){
  int trigger =0;

  if ( pd.pinState()->J126(1) and pd.pinState()->J126(2) ){ // both motors running
    pd.fadeInAllAdr("red", 50);
    pd.fadeOutAllAdr(50);
    trigger = 1;
  }
  else if ( pd.pinState()->J126(1) ){  //  Left Gun Motor
    pd.adrLED1()->fadeIn("red",50);
    pd.adrLED1()->fadeOut(50);
    trigger =1;
  }
  else if ( pd.pinState()->J126(2) ){ //  Right Gun Motor
    pd.adrLED2()->fadeIn("red",50);
    pd.adrLED2()->fadeOut(50);
    trigger =1;
  }
  if ( pd.pinState()->J126(4) ){ //Jets
    pd.adrLED2()->color("purple");
    delay(200);
    pd.adrLED2()->fadeOut(100);
    trigger =1;
  }
  if ( pd.pinState()->J126(5) ){ //Right Popper 
    pd.adrLED2()->bullet2Color("orange","red",10,5,-1);
    trigger =1;
  }
  if ( pd.pinState()->J126(6) ){ //Middle Ramp 
//    pd.adrLED1()->bulletFromPoint2Color( "blue", "purple", 10, 5, R_START);
    trigger =1;
  }
  if ( pd.pinState()->J126(7) ){ //Shields
    pd.fadeInAllAdr("blue",10);
    delay(50);
    pd.fadeOutAllAdr(10); 
    trigger =1;
  }
  if ( pd.pinState()->J126(8) ){ //Autofire
    trigger=1;
  }
  if ( pd.pinState()->J126(13) ){ // Exit Underground
    pd.adrLED1()->bulletFromPoint2RGB( 50,50,100, 0,0,255,15, 5, R_START);
    trigger=1;
  }
  if ( pd.pinState()->J126(14) and pd.pinState()->J126(15)) { //both left/right borg flashers are going
//    pd.chaseAllAdr2RGBFromPoint(45, 0, 255, 0, 0, 255, 0, 5, 2);
    pd.fadeInAllAdr("green", 5);
    pd.fadeOutAllAdr(5);
    trigger=1;
  }
  else if ( pd.pinState()->J126(14) ){ //Right Borg ship
    pd.adrLED2()->bullet("green", 5, 10, 1);
    trigger =1;
  }
  else if ( pd.pinState()->J126(15) ){ //Left Borg ship
    pd.adrLED1()->bulletFromPoint( "green", 5, 5, R_START);
    trigger =1;
  }
  if ( pd.pinState()->J126(16)){ // Center Borg ship
//    pd.adrLED1()->bulletFromPoint( "green", 5, 5, R_START);
    trigger =1;
  }
 
//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   pd.adrLED1()->clear();
   pd.adrLED2()->clear();
   pd.pinState()->reset();
   trigger =0;
   attractOn = 0;
   timeLastEvent = millis();
  }

//end function checkPinStates
}



void attractMode() {
  pd.adrLED1()->sparkle(color,80,20);
  pd.adrLED2()->sparkle(color,80,20);
  if (random(1000) == 0) {
    if (color == "blue") {color = "purple";}
    else color = "blue";
  }
}


