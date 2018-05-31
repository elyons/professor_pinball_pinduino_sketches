//Eric Lyons 2016
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3
//Uses pinduino library

//Initial Config for High Speed II: Getaway
//Mike_M
//Single 47 LED Strip Chase around supercharger

#include <pinduino.h>

int aLEDNum1 = 47;

pinduino pd (aLEDNum1, "Nano");

int bg_chase_on = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 30000; //Amount of time to wait before chase lights start up again 1000 == 1 second
String color = "red";

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.pinState()->reset();
}

void loop() {
  pd.pinState()->update();
  
  //   Print the pin states out to serial
  //  pd.pinState()->print();

  checkPinStates();

  if (millis() - timeLastEvent > startChaseWaitTime) {
    bg_chase_on = 1;
  }
  if (bg_chase_on) {
    backgroundChase();
  }
}

void checkPinStates() {
  int trigger = 0;

  if ( pd.pinState()->J126(1) ) { //right bank flasher
    pd.adrLED1()->chase2ColorFromPoint(23, "yellow","red", 25,2);
    delay(5);
    trigger = 1;
  }
  if ( pd.pinState()->J126(2) ) {  //supercharger flasher
    pd.adrLED1()->bullet("red", 10, 2, 1);
    delay(10);
    trigger = 1;
  }
  if ( pd.pinState()->J126(3) ) { //left slingshot flasher
    trigger = 1;
  }
  if ( pd.pinState()->J126(4) ) { //free ride flasher
    pd.adrLED1()->bullet2Color("yellow", "red", 8, 15, -1);
    delay(5);
    trigger = 1;
  }
  if ( pd.pinState()->J126(5) ) { //left ramp flasher
    trigger = 1;
  }
  if ( pd.pinState()->J126(6) ) {  //left bank flasher
//    pd.adrLED1()->explosion(28, "lime", 47);
    pd.adrLED1()->chase2ColorFromPoint(23, "red","yellow", 25,2);
    delay(5);
    trigger = 1;
  }
  if ( pd.pinState()->J126(7) ) {
    //    trigger=1;
  }
  if ( pd.pinState()->J126(8) ) {
    trigger = 1;
  }
  if ( pd.pinState()->J126(9) ) {
    trigger = 1;
  }
  if ( pd.pinState()->J126(10) ) {
    trigger = 1;
  }
  if ( pd.pinState()->J126(11) ) {
    trigger = 1;
  }
  if ( pd.pinState()->J126(12) ) {
    trigger = 1;
  }


  //trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
    pd.adrLED1()->clear();
    pd.adrLED2()->clear();
    pd.pinState()->reset();
    trigger = 0;
    bg_chase_on = 0;
    timeLastEvent = millis();
  }
  //end function checkPinStates
}



void backgroundChase() {
  pd.adrLED1()->sparkle(color,20);
    if (random(1000) == 0) {
    if (color == "red") color = "blue";
    else if (color == "blue") color = "green";
    else if (color == "green") color = "white";
    else color = "red";
    }
  
}


