//Eric Lyons 2017
//Note to self:  Play more pinball!
//Testing BumperLights by Herbet Holler.  Each BumberLight has 10 LEDs and three were wired in series 
//for this test

//Interfaced for pinduino shield v0.3 
//Uses pinduino library

#include <pinduino.h>
int N_LEDS = 30;
int aLEDNum1 = N_LEDS;
int aLEDNum2 = 0;
int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");



int bg_chase_on = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 30000; //Amount of time to wait before chase lights start up again 1000 == 1 second
String chaseColor = "red"; // var to hold bg chase color

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
}

void loop(){
  if (bg_chase_on){backgroundChase();}
  pd.pinState()->update();
//   Print the pin states out to serial 
//  pd.pinState()->print();
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) {bg_chase_on=1;}
}

void checkPinStates(){
  int trigger =0;
  if ( pd.pinState()->J126(1) ){
    pd.adrLED1()->color("red");
    delay(200);
    trigger = 1; 
  }
  if ( pd.pinState()->J126(2) ){
    pd.adrLED1()->color("green");
    delay(200);
    trigger = 1; 
  }
  if ( pd.pinState()->J126(3) ){ 
    pd.adrLED1()->color("blue");
    delay(200);
    trigger = 1; 
  }
  if ( pd.pinState()->J126(4) ){
    pd.adrLED1()->color("orange");
    delay(200);
    trigger = 1; 
  }
  if ( pd.pinState()->J126(5) ){
    pd.adrLED1()->color("yellow");
    delay(200);
    trigger = 1; 
  }
  if ( pd.pinState()->J126(6) ){ 
    pd.adrLED1()->color("purple");
    delay(200);
    trigger = 1; 
  }
  if ( pd.pinState()->J126(7) ){
    pd.adrLED1()->color("lime");
    delay(200);
    trigger = 1; 
  }
  if ( pd.pinState()->J126(8) ){
    pd.adrLED1()->bullet2Color("blue", "white", 10,20, -1);
    trigger = 1; 
  }
  if ( pd.pinState()->J126(9) ){ 
    pd.adrLED1()->bullet2Color("green", "mint", 10,20, 1);
    trigger = 1; 
  }
  if ( pd.pinState()->J126(10) ){
    pd.adrLED1()->bullet2Color("red", "white", 10,20, -1);
    trigger = 1; 
  }
  if ( pd.pinState()->J126(11) ){
    pd.adrLED1()->bullet2Color("blue", "red", 10,20, 1);
    trigger = 1; 
  }
  if ( pd.pinState()->J126(12) ){ 
    pd.adrLED1()->bullet2Color("green", "yellow", 10,20, -1);
    trigger = 1; 
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
  pd.adrLED1()->fadeIn("white", 1000);
  delay(1000);
  pd.adrLED1()->fadeColor2Color("white", "red", 1000);
  delay(1000);
  pd.adrLED1()->fadeColor2Color("red", "green", 1000);
  delay(1000);
  pd.adrLED1()->fadeColor2Color("green", "blue", 1000);
  delay(1000);
  pd.adrLED1()->fadeColor2Color("blue", "yellow", 1000);
  delay(1000);
  pd.adrLED1()->fadeColor2Color("yellow", "purple", 1000);
  delay(1000);
  pd.adrLED1()->fadeColor2Color("purple", "cyan", 1000);
  delay(1000);
  pd.adrLED1()->fadeColor2Color("cyan", "orange", 1000);
  delay(1000);
  pd.adrLED1()->fadeColor2Color("orange", "lime", 1000);
  delay(1000);
  pd.adrLED1()->fadeColor2Color("lime", "sky", 1000);
  delay(1000);
  pd.adrLED1()->fadeColor2Color("sky", "mint", 1000);
  delay(1000);
  pd.adrLED1()->fadeColor2Color("mint", "magenta", 1000);
  delay(1000);
  pd.adrLED1()->fadeColor2Color("magenta", "lavender", 1000);
  delay(1000);
  pd.adrLED1()->fadeColor2Color("lavender", "black", 1000);
  delay(1000);
  pd.adrLED1()->fadeOut(100);  

  pd.adrLED1()->bullet2Color("blue", "blue", 20,20, -1);
  pd.adrLED1()->bullet2Color("blue", "blue", 20,10, 1);
  pd.adrLED1()->bullet2Color("red", "red", 20,20, -1);
  pd.adrLED1()->bullet2Color("red", "red", 20,10, 1);
  pd.adrLED1()->bullet2Color("yellow", "yellow", 20,20, -1);
  pd.adrLED1()->bullet2Color("yellow", "yellow", 20,10, 1);
  pd.adrLED1()->bullet2Color("blue", "red", 20,30, -1);
  pd.adrLED1()->bullet2Color("red", "blue", 20,20, 1);
  pd.adrLED1()->bullet2Color("green", "red", 5,40, -1);
  pd.adrLED1()->bullet2Color("red", "green", 5,10, 1);
  pd.adrLED1()->chase2Color("green", "red", 100,10, -1);
  pd.adrLED1()->chase2Color("red", "green", 100,10, 1);

  delay(1000);
}

