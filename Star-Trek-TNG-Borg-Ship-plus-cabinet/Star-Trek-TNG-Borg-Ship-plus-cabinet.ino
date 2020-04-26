//Eric Lyons 2018
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3 (Nano!)
//Uses pinduino library

#include <pinduino.h>
int R_START = 25;

int aLEDNum1 = 65;
int aLEDNum2 = 150;
int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");


int attractOn = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
unsigned long attractModeTime = 10; //Amount of time to wait before chase lights start up again 1000 == 1 second
String color = "green"; //attract color

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
}

void loop(){
//  if (attractOn){attractMode();}
  attractMode();
  pd.pinState()->update();
//   Print the pin states out to serial 
//  pd.pinState()->print();
  checkPinStates();
 // if (millis()-timeLastEvent > attractModeTime) {attractOn=1;}
}

void checkPinStates(){
  int trigger =0;

  if ( pd.pinState()->J126(1) ){  //  Left Gun Motor
    pd.adrLED1()->color("red");
    pd.adrLED1()->fadeIn("red",50);
    delay(2000);
    pd.adrLED2()->clear();
    pd.adrLED1()->fadeOut(50);
    trigger =1;
  }
  if ( pd.pinState()->J126(2) ){ //  Right Gun Motor
    pd.adrLED1()->color("red");
    pd.adrLED1()->fadeIn("red",50);
    delay(2000);
    pd.adrLED2()->clear();
    pd.adrLED1()->fadeOut(50);
    trigger =1;
  }
  if ( pd.pinState()->J126(4) ){ //Jets
    pd.adrLED1()->color("purple");
    pd.adrLED2()->color("purple");
    delay(200);
    pd.adrLED1()->fadeOut(100);
    pd.adrLED2()->clear();
    trigger =1;
  }
  if ( pd.pinState()->J126(5) ){ //Right Popper 
    pd.adrLED1()->color("green");
    pd.adrLED2()->color("green");
    delay(200);
    pd.adrLED1()->fadeOut(100);
    pd.adrLED2()->fadeOut(100);
    trigger =1;
  }
  if ( pd.pinState()->J126(6) ){ //Middle Ramp 
    pd.adrLED1()->color("cyan");
    pd.adrLED2()->color("cyan");
    delay(200);
    pd.adrLED1()->fadeOut(100);
    pd.adrLED2()->fadeOut(100);
    trigger =1;
  }
  if ( pd.pinState()->J126(7) ){ //Shields
    pd.adrLED1()->color("red");
    pd.adrLED2()->color("blue");
    delay(200);
    pd.adrLED1()->fadeOut(100);
    pd.adrLED2()->fadeOut(100);
    trigger =1;
  }
  if ( pd.pinState()->J126(8) ){ //Autofire
//    trigger=1;
  }
  if ( pd.pinState()->J126(13) ){ // Exit Underground
    pd.adrLED1()->color("blue");
    pd.adrLED2()->color("blue");
    delay(200);
    pd.adrLED1()->fadeOut(100);
    pd.adrLED2()->fadeOut(100);
    trigger =1;
  }
  if ( pd.pinState()->J126(14) and pd.pinState()->J126(15)) { //both left/right borg flashers are going
    pd.adrLED1()->color("red");
    pd.adrLED2()->color("red");
    delay(200);
    pd.adrLED1()->fadeOut(100);
    pd.adrLED2()->fadeOut(100);
    trigger =1;
  }
  else if ( pd.pinState()->J126(14) ){ //Right Borg ship
    pd.adrLED1()->color("red");
    pd.adrLED2()->color("red");
    delay(200);
    pd.adrLED1()->fadeOut(100);   
    pd.adrLED2()->fadeOut(100);
    trigger =1;
  }
  else if ( pd.pinState()->J126(15) ){ //Left Borg ship
    pd.adrLED1()->color("orange");
    pd.adrLED2()->color("orange");
    delay(200);
    pd.adrLED1()->fadeOut(100);
    pd.adrLED2()->fadeOut(100);
    trigger =1;
  }
  if ( pd.pinState()->J126(16)){ // Center Borg ship
    pd.adrLED1()->color("yellow");
    pd.adrLED2()->color("yellow");
    delay(200);
    pd.adrLED1()->fadeOut(100);  
    pd.adrLED2()->fadeOut(100);
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
   color="green";
  }

//end function checkPinStates
}



void attractMode() {
  pd.adrLED1()->sparkle(color,20,20);
  pd.adrLED2()->sparkle("blue",80,0);
}
