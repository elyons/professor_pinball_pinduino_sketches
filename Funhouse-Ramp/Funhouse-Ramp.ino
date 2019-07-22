//Eric Lyons 2016
//Interfaced for pinduino shield v0.3
//Eric Lyons 2019
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3//Uses pinduino library


#include <pinduino.h>

int aLEDNum1 = 64;
int aLEDNum2 = 5;

pinduino pd (aLEDNum1, aLEDNum2, "Nano");

int attractModeOn = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 2000; //Amount of time to wait before chase lights start up again 1000 == 1 second
String color = "red";

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.pinState()->reset();
}

void loop() {
  pd.pinState()->update();
  pd.adrLED2()->color("white"); 
  //  Print the pin states out to serial
  //  pd.pinState()->print();

  checkPinStates();

  if (millis() - timeLastEvent > startChaseWaitTime) {
    attractModeOn = 1;
  }
  if (attractModeOn) {
    attractMode();
  }
}

void checkPinStates() {
  int trigger = 0;

  if ( pd.pinState()->J126(1) ) { //3 blue flashers
    pd.adrLED2()->color("blue");    
    pd.adrLED1()->chase2ColorFromPoint(32, "blue", "red", 20, 2);
    trigger = 1;
  }
  if ( pd.pinState()->J126(2) ) {  //Dummy flasher
    pd.adrLED2()->color("red");    
    pd.adrLED1()->bullet2Color("red", "orange", 15, 0, -1);
    pd.adrLED2()->color("orange");    
    pd.adrLED1()->bullet2Color("orange", "yellow", 15, 0, -1);
    pd.adrLED2()->color("yellow");
    pd.adrLED1()->bullet2Color("yellow", "green", 15, 0, -1);
    pd.adrLED2()->color("green");
    pd.adrLED1()->bullet2Color("green", "blue", 15, 0, -1);
    pd.adrLED2()->color("blue");
    pd.adrLED1()->bullet2Color("blue", "purple", 15, 0, -1);
    pd.adrLED2()->color("purple");
    pd.adrLED1()->bullet2Color("purple", "red", 15, 0, -1);
    pd.adrLED2()->color("red");
    trigger = 1;
  }
  if ( pd.pinState()->J126(3) ) { //2 clock flasher
    pd.adrLED1()->fadeIn("red", 50);
    delay(100);
    pd.adrLED1()->color("orange");
    delay(100);
    pd.adrLED1()->color("yellow");
    delay(100);
    pd.adrLED1()->color("green");
    delay(100);
    pd.adrLED1()->color("blue");
    delay(100);
    pd.adrLED1()->color("purple");
    delay(100);
    pd.adrLED1()->fadeOut(100);
   trigger = 1;
  }
  if ( pd.pinState()->J126(4) ) { //superdog
    pd.adrLED2()->color("red");
    pd.adrLED1()->fadeIn("red",10);
    delay(10);
    trigger = 1;
  }
  if ( pd.pinState()->J126(5) ) { //mouth motor    
  }
  if ( pd.pinState()->J126(6) ) {  //updown driver
  }
  if ( pd.pinState()->J126(7) ) { //3 red flasher
    pd.adrLED2()->color("red");
    pd.adrLED1()->chase2ColorFromPoint(32, "red", "orange", 20, 2);
    trigger = 1;

  }
  if ( pd.pinState()->J126(8) ) { //3 clear flasher
    pd.adrLED1()->chase2ColorFromPoint(32, "white", "yellow", 20, 2);
    trigger = 1;
  }

  //trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
    pd.adrLED1()->clear();
    pd.adrLED2()->color("white");
    pd.pinState()->reset();
    trigger = 0;
    attractModeOn = 0;
    timeLastEvent = millis();
  }
  //end function checkPinStates
}

void attractMode() {
  pd.adrLED1()->sparkle(color,20);
  if (random(1000) == 0) {
    if (color == "red") color = "blue";
    else color = "red";
  }
}

