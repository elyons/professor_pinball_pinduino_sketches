//Eric Lyons 2016
//Interfaced for pinduino shield v0.3
//Uses pinduino library

//Initial Config for The Getaway High Speed II - Mike_M
//Revised 2019.05.15 by Mr_Tantrum (Chris Zumwalt)
//Single 47 LED Strip Chase around supercharger

#include <pinduino.h>

int aLEDNum1 = 47;

pinduino pd (aLEDNum1, "Nano");

int bg_chase_on = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 400; //Amount of time to wait before chase lights start up again 1000 == 1 second
String color = "red";

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.pinState()->reset();
}

void loop() {
  pd.pinState()->update();

  //  Print the pin states out to serial
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
    pd.adrLED1()->chaseRGB(255,0,0, 12, 2, 1);
    pd.adrLED1()->chaseRGB(0,0,255, 12, 2, -1);
    pd.adrLED1()->chaseRGB(255,0,0, 12, 2, 1);
    pd.adrLED1()->chaseRGB(0,0,255, 12, 2, -1);
    pd.adrLED1()->chaseRGB(255,0,0, 12, 2, 1);
    pd.adrLED1()->chaseRGB(0,0,255, 12, 2, -1);
    trigger = 1;
  }
  if ( pd.pinState()->J126(2) ) {  //supercharger flasher
    pd.adrLED1()->bullet("red", 10, 2, 1);
    delay(10);
    trigger = 1;
  }
  if ( pd.pinState()->J126(3) ) { //left slingshot flasher
    pd.adrLED1()->explosion(23,"red",47);
    pd.adrLED1()->explosion(23,"blue",47);
    pd.adrLED1()->explosion(23,"red",47);
    pd.adrLED1()->explosion(23,"blue",47);
    pd.adrLED1()->explosion(23,"red",47);
    trigger = 1;
  }
  if ( pd.pinState()->J126(4) ) { //free ride flasher
  }
  if ( pd.pinState()->J126(5) ) { //left ramp flasher
  }
  if ( pd.pinState()->J126(6) ) {  //left bank flasher
    pd.adrLED1()->RGBBand(35, 255,0,0, 24);
    delay(150);
    pd.adrLED1()->clear();
    pd.adrLED1()->RGBBand(13, 0,0,255, 12);
    delay(150);
    pd.adrLED1()->clear();
    pd.adrLED1()->RGBBand(35, 255,0,0, 24);
    delay(150);
    pd.adrLED1()->clear();
    pd.adrLED1()->RGBBand(13, 0,0,255, 12);
    delay(150);
    pd.adrLED1()->clear();
    pd.adrLED1()->RGBBand(35, 255,0,0, 24);
    delay(150);
    pd.adrLED1()->clear();
    pd.adrLED1()->RGBBand(13, 0,0,255, 12);
    delay(150);
    pd.adrLED1()->clear();
    pd.adrLED1()->RGBBand(35, 255,0,0, 24);
    delay(150);
    pd.adrLED1()->clear();
    pd.adrLED1()->RGBBand(13, 0,0,255, 12);
    delay(150);
    pd.adrLED1()->clear();
    pd.adrLED1()->RGBBand(35, 255,0,0, 24);
    delay(150);
    pd.adrLED1()->clear();
    pd.adrLED1()->RGBBand(13, 0,0,255, 12);
    delay(150);
    pd.adrLED1()->clear();
    trigger = 1;
  }
  if ( pd.pinState()->J126(7) ) { //flipper flasher
  }
  if ( pd.pinState()->J126(8) ) { //right slingshot flasher
    pd.adrLED1()->explosion(23,"red",47);
    pd.adrLED1()->explosion(23,"blue",47);
    pd.adrLED1()->explosion(23,"red",47);
    pd.adrLED1()->explosion(23,"blue",47);
    pd.adrLED1()->explosion(23,"red",47);
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
  pd.adrLED1()->sparkleRGB(100,100,100, 20);
}
