//Eric Lyons and Philip Forrester  2019
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3
//Uses pinduino library

#include <pinduino.h>
int N_LEDS = 0;
int aLEDNum1 = N_LEDS;
int aLEDNum2 = 0;

pinduino pd (aLEDNum1, aLEDNum2, "Nano");

unsigned long timeLastEvent = 0; // time last event was last triggered
unsigned long attractModeTime = 3000; // time of no activity and game is in attract mode

void setup() {
  Serial.begin(115200);
  // pd.adrLED1()->clear();
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

  if ( pd.pinState()->J126(1) && millis()-timeLastEvent < attractModeTime){  //  J111-1 Right Ramp high
    trigger =1;
    pd.port1()->high();
    delay(75);    
    pd.port1()->low();
    delay(300); 
  }
  if ( pd.pinState()->J126(2) && millis()-timeLastEvent < attractModeTime){ //  J111-2 Right ramp low
    trigger =1;
    pd.port1()->high();
    delay(75);    
    pd.port1()->low();
    delay(300); 
  }
  if ( pd.pinState()->J126(3) && millis()-timeLastEvent < attractModeTime){ // J111-3 Right side high
    trigger =1;
    pd.port1()->high();
    delay(75);    
    pd.port1()->low();
    delay(300); 
  }
  if ( pd.pinState()->J126(4) && millis()-timeLastEvent < attractModeTime){ // J111-4 right side low
   // trigger =1;
   // pd.port1()->high();
   // delay(100);    
   // pd.port1()->low();
   // delay(150); 
  }
  if ( pd.pinState()->J126(5) && millis()-timeLastEvent < attractModeTime){ // J111-5 center arrow
  //  trigger =1;
  }
  if ( pd.pinState()->J126(6) && millis()-timeLastEvent < attractModeTime){ // J111-6 jets ***
    trigger =1;
    pd.port1()->high();
    delay(75);    
    pd.port1()->low();
    delay(300);      
  }
  if ( pd.pinState()->J126(7) && millis()-timeLastEvent < attractModeTime){ // J111-7 saucer dome ***
    trigger =1;
    pd.port1()->high();
    delay(100);    
    pd.port1()->low();
    delay(250); 
  }
  if ( pd.pinState()->J126(8) ){ // J111-8 motor bank ***
    // trigger=1;
  }
  if ( pd.pinState()->J126(13) ){ // J113-1 Left slingshot ***
    trigger =1;
//    pd.port1()->high();
//    delay(1000);    
  }
  if ( pd.pinState()->J126(14) && millis()-timeLastEvent < attractModeTime) { // J109-1 Left Ramp Left ***
    trigger =1;
    pd.port1()->high();
    delay(75);    
    pd.port1()->low();
    delay(300); 
  }
  if ( pd.pinState()->J126(15) && millis()-timeLastEvent < attractModeTime){ // J109-2 Left Ramp Right ***
    trigger =1;
    pd.port1()->high();
    delay(75);    
    pd.port1()->low();
    delay(300); 
  }
  if ( pd.pinState()->J126(16) && millis()-timeLastEvent < attractModeTime){ // J109-3 Left Side High ***
    trigger =1;
    pd.port1()->high();
    delay(75);    
    pd.port1()->low();
    delay(300); 
  }
 
//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   pd.pinState()->reset();
   trigger =0;
   timeLastEvent = millis();
  }

//end function checkPinStates
}
