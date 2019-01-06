//Eric Lyons 2019
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.2
//Uses pinduino library

#include <pinduino.h>
int N_LEDS = 23;
int mid = N_LEDS/2;
int aLEDNum1 = N_LEDS;
int aLEDNum2 = 0;
int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");

int attract_mode_on = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
unsigned long startChaseWaitTime = 20000; //Amount of time to wait before chase lights start up again 1000 == 1 second
String color = "red"; //attract color

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
}

void loop(){
  if (attract_mode_on){attractMode();}
  pd.pinState()->update();
//   Print the pin states out to serial 
  pd.pinState()->print();
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) {attract_mode_on=1;}
}

void checkPinStates(){
  int trigger =0;

  //P11-1: outhole 
  if ( pd.pinState()->P11(1)){ // 
  // Trigger an event so pinduino attact mode shuts off.
    trigger = 1; 
  }
  

  //P11-6: cup flashers
  if ( pd.pinState()->P11(7) ){ //
    pd.adrLED1()->fadeIn("red", 500);
    delay(200);
    pd.adrLED1()->fadeOut(500);
    trigger =1;
  }

  //P11-9: DINE-TIME Flashers
  if ( pd.pinState()->P11(9) ){
    pd.adrLED1()->fadeIn("blue", 500);
    delay(200);
    pd.adrLED1()->fadeOut(500);
    trigger =1;
  }

  //P12-1: right ramp flashers
  if ( pd.pinState()->P12(1) ){ 
    pd.adrLED1()->bullet2Color("red", "blue", 1, 20, 1);
    pd.adrLED1()->bullet2Color("blue", "red", 1, 20, -1);
    trigger =1;
  }


  


//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   timeLastEvent = millis();
   pd.adrLED1()->clear();
   pd.pinState()->reset();
   trigger = 0;
   attract_mode_on = 0;
  }

//end function checkPinStates
}

void attractMode() {
  pd.adrLED1()->sparkle(color,20,30);
  if (random(1000) == 0) {
      if (color == "red") color = "purple";
      else if (color == "purple") color = "blue";
      else color = "red";
  }
}
