//Eric Lyons 2015
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.2
//Uses pinduino library

#include <pinduino.h>
int N_LEDS = 300;
int aLEDNum1 = N_LEDS;
int aLEDNum2 = 0;
int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");

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
  pd.pinState()->print();
  checkPinStates();
}

void checkPinStates(){
  int trigger =0;
  
  if ( pd.pinState()->J6(1) ){
    pd.adrLED1()->color("red",255);
    delay(1000);
    trigger = 1; 
  }
  if ( pd.pinState()->J6(2) ){
    pd.adrLED1()->color("red",255);
    delay(1000);
    trigger = 1; 
  }
  if ( pd.pinState()->J6(3) ){ 
    pd.adrLED1()->color("red",255);
    delay(1000);
    trigger = 1; 
  }
  if ( pd.pinState()->J6(4) ){ 
    pd.adrLED1()->color("red",255);
    delay(1000);
    trigger =1;
  }
  if ( pd.pinState()->J6(5) ){ 
    pd.adrLED1()->color("red",255);
    delay(1000);
    trigger =1;
  }
  if ( pd.pinState()->J6(6) ){ 
    pd.adrLED1()->color("red",255);
    delay(1000);
    trigger =1;
  }
  if ( pd.pinState()->J6(7) ){ 
    pd.adrLED1()->color("red",255);
    delay(1000);
    trigger =1;
  }
  if ( pd.pinState()->J6(8) ){ 
    pd.adrLED1()->color("red",255);
    delay(1000);
    trigger =1;
  }
  if ( pd.pinState()->J7(2) ){ 
    pd.adrLED1()->color("red",255);
    delay(1000);
    trigger =1;
  }
  if ( pd.pinState()->J7(3) ){ 
    pd.adrLED1()->color("red",255);
    delay(1000);
    trigger =1;
  }
  if ( pd.pinState()->J7(4) ){ 
    pd.adrLED1()->color("red",255);
    delay(1000);
    trigger =1;
  }
  if ( pd.pinState()->J7(6) ){ 
    pd.adrLED1()->color("red",255);
    delay(1000);
    trigger =1;
  }
  if ( pd.pinState()->J7(7) ){ 
    pd.adrLED1()->color("red",255);
    delay(1000);
    trigger =1;
  }
  if ( pd.pinState()->J7(8) ){
    pd.adrLED1()->color("red",255);
    delay(1000);
    trigger=1;
  }
  if ( pd.pinState()->J7(9) ){
    pd.adrLED1()->color("red",255);
    delay(1000);
    trigger=1;
  }
  if ( pd.pinState()->J7(10) ){ 
    pd.adrLED1()->color("red",255);
    delay(1000);
    trigger =1;
  }


//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   pd.adrLED1()->clear();
   pd.pinState()->reset();
   trigger =0;
  }

//end function checkPinStates
}

