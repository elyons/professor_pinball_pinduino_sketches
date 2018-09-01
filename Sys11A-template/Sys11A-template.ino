//Eric Lyons 2018
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3
//Uses pinduino library

#include <pinduino.h>
int N_LEDS = 50;
int mid = N_LEDS/2;
int aLEDNum1 = N_LEDS;
int aLEDNum2 = N_LEDS;
int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");

int attract_on = 1; // flag for running attract mode
unsigned long timeLastEvent = 0; // time last event was last triggered
unsigned long startChaseWaitTime = 20000; //Amount of time to wait before chase lights start up again 1000 == 1 second
String color = "white"; //attract color
int attract_style = 1;

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
}

void loop(){
  if (attract_on){attractMode();}
  pd.pinState()->update();
//   Print the pin states out to serial 
  pd.pinState()->print();
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) {attract_on=1;}
}

void checkPinStates(){
  int trigger =0;
  //Note:  P11-2 and P12-3 are key pins

  //P11-1
  if ( pd.pinState()->P11(1) ) {
    pd.adrLED1()->color("red",255);
    pd.adrLED2()->color("blue",255);
    delay(1000);
    trigger = 1; 
  }
  //P11-3
  if ( pd.pinState()->P11(3) ) {
    pd.adrLED2()->color("blue",255);
    pd.adrLED1()->color("red",255);
    delay(1000);
    trigger = 1; 
  }
  //P11-4
  if ( pd.pinState()->P11(4) ) {
    pd.adrLED1()->color("red",255);
    pd.adrLED2()->color("blue",255);
    delay(1000);
    trigger = 1; 
  }
  //P11-5
  if ( pd.pinState()->P11(5) ) {
    pd.adrLED1()->color("red",255);
    pd.adrLED2()->color("blue",255);
    delay(1000);
    trigger = 1; 
  }
  //P11-6
  if ( pd.pinState()->P11(6) ) {
    pd.adrLED1()->color("red",255);
    pd.adrLED2()->color("blue",255);
    delay(1000);
    trigger = 1; 
  }
  //P11-7
  if ( pd.pinState()->P11(7) ) {
    pd.adrLED1()->color("red",255);
    pd.adrLED2()->color("blue",255);
    delay(1000);
    trigger = 1; 
  }
  //P11-8
  if ( pd.pinState()->P11(8) ) {
    pd.adrLED1()->color("red",255);
    pd.adrLED2()->color("blue",255);
    delay(1000);
    trigger = 1; 
  }
  //P11-9
  if ( pd.pinState()->P11(9) ) {
    pd.adrLED1()->color("red",255);
    pd.adrLED2()->color("blue",255);
    delay(1000);
    trigger = 1; 
  }

  //P12-1
  if ( pd.pinState()->P12(1) ) {
    pd.adrLED1()->color("red",255);
    pd.adrLED2()->color("blue",255);
    delay(1000);
    trigger = 1; 
  }
  //P12-2
  if ( pd.pinState()->P12(2) ) {
    pd.adrLED1()->color("red",255);
    pd.adrLED2()->color("blue",255);
    delay(1000);
    trigger = 1; 
  }
  //P12-4
  if ( pd.pinState()->P12(4) ) {
    pd.adrLED1()->color("red",255);
    pd.adrLED2()->color("blue",255);
    delay(1000);
    trigger = 1; 
  }
  //P12-5
  if ( pd.pinState()->P12(5) ) {
    pd.adrLED1()->color("red",255);
    pd.adrLED2()->color("blue",255);
    delay(1000);
    trigger = 1; 
  }
  //P12-6
  if ( pd.pinState()->P12(6) ) {
    pd.adrLED1()->color("red",255);
    pd.adrLED2()->color("blue",255);
    delay(1000);
    trigger = 1; 
  }
  //P12-7
  if ( pd.pinState()->P12(7) ) {
    pd.adrLED1()->color("red",255);
    pd.adrLED2()->color("blue",255);
    delay(1000);
    trigger = 1; 
  }
  //P12-8
  if ( pd.pinState()->P12(8) ) {
    pd.adrLED1()->color("red",255);
    pd.adrLED2()->color("blue",255);
    delay(1000);
    trigger = 1; 
  }
  //P12-9
  if ( pd.pinState()->P12(9) ) {
    pd.adrLED1()->color("red",255);
    pd.adrLED2()->color("blue",255);
    delay(1000);
    trigger = 1; 
  }

//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   timeLastEvent = millis();
   pd.adrLED1()->clear();
   pd.adrLED2()->clear();
   pd.pinState()->reset();
   trigger = 0;
   attract_on = 0;
  }

//end function checkPinStates
}

void attractMode() {
  if (attract_style) {
    pd.adrLED1()->sparkle(color,20,30);
    pd.adrLED2()->sparkle(color,20,30);
    if (random(1000) == 0) {
        if (color == "white") color = "red";
        else if (color == "red") color = "blue";
        else color = "white";
    }
  }
  else {
    pd.adrLED1()->dataStreamNoTail2Color("blue", "red", 20, 20, 1);
    pd.adrLED2()->dataStreamNoTail2Color("blue", "red", 20, 20, 1);
  }
  if (random(1000) == 0) {
    if (attract_style) { attract_style = 0;}
    else {attract_style = 1;}
  }
}
