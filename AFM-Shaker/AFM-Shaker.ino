//Eric Lyons 2019
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3
//Uses pinduino library

#include <pinduino.h>
int N_LEDS = 0;
int aLEDNum1 = N_LEDS;
int aLEDNum2 = 0;

pinduino pd (aLEDNum1, aLEDNum2, "Nano");

unsigned long timeLastEvent = 0; // time last event was last triggered

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
//  if (millis()-timeLastEvent > startChaseWaitTime) {}
}

void checkPinStates(){
  int trigger =0;

  if ( pd.pinState()->J126(1) ){  //  J111-1 Right Ramp high
//    trigger =1;
  }
  if ( pd.pinState()->J126(2) ){ //  J111-2 Right ramp low
//    trigger =1;
  }
  if ( pd.pinState()->J126(3) ){ // J111-3 Right side high
//    trigger =1;
  }
  if ( pd.pinState()->J126(4) ){ // J111-4 right side low
//    trigger =1;
  }
  if ( pd.pinState()->J126(5) ){ // J111-5 center arrow
//    trigger =1;
  }
  if ( pd.pinState()->J126(6) ){ // J111-6 jets ***
    trigger =1;
    pd.port1()->high();
    delay(1000);    
  }
  if ( pd.pinState()->J126(7) ){ // J111-7 saucer dome ***
    trigger=1;
    pd.port1()->high();
    delay(1000);    
  }
  if ( pd.pinState()->J126(8) ){ // J111-8 motor bank ***
    trigger=1;
    pd.port1()->high();
    delay(1000);    
  }
  if ( pd.pinState()->J126(13) ){ // J113-1 Left slingshot ***
    trigger =1;
    pd.port1()->high();
    delay(1000);    
  }
  if ( pd.pinState()->J126(14) ) { // J113-2 right slingshot ***
    trigger =1;
    pd.port1()->high();
    delay(1000);    
  }
  if ( pd.pinState()->J126(15) ){ //  
//    trigger =1;
  }
  if ( pd.pinState()->J126(16) ){ //
//    trigger =1;
  }
 
//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   pd.port1()->low();
   pd.pinState()->reset();
   trigger =0;
   timeLastEvent = millis();
  }

//end function checkPinStates
}

