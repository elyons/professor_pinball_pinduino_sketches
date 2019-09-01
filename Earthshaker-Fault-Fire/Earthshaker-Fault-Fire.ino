//Eric Lyons 2019
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.2
//Uses pinduino library

#include <pinduino.h>
int N_LEDS = 16;
int mid = N_LEDS/2;
int aLEDNum1 = N_LEDS;
int aLEDNum2 = 0;
int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");

int fire_on = 0;
unsigned long timeLastEvent = 0; // time last event was last triggered
unsigned long startChaseWaitTime = 10000; //Amount of time to wait before chase lights start up again 1000 == 1 second

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
}

void loop(){
  pd.pinState()->update();
//   Print the pin states out to serial 
//  pd.pinState()->print();
  checkPinStates();
//  if (millis()-timeLastEvent > startChaseWaitTime) {attract_mode_on=1;}
}

void checkPinStates(){
  int trigger =0;
  if ( pd.pinState()->P11(5) && !pd.pinState()->P12(5) ){ // fault solenoid
      for (int i = 0; i <= 500; i++) { pd.adrLED1()->fire(10,10);}
      pd.adrLED1()->fadeOut(100);
      trigger = 1;
  }

  if ( pd.pinState()->P12(5) ){ // A/C relay
      trigger = 1;
  }

//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   timeLastEvent = millis();
   pd.pinState()->reset();
   trigger = 0;
  }

//end function checkPinStates
}


