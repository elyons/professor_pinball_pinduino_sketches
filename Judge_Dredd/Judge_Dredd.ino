//Eric Lyons 2018
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.2 and v0.3
//Uses pinduino library

/// ---=====  NOTE ====---
/// 
///Major thanks and game specifications by DevilMuse (aka Bryan)


#include <pinduino.h>
int aLEDNum1 = 150; //left ramp
int aLEDNum2 = 150; //right ramp
int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");



int bg_on = 1; //attract effect
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 4000; //Amount of time to wait before chase lights start up again 1000 == 1 second
int bgWhiteTime = 500;
String color = "red";

// count ball locks
int lock_count = 0;

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
}

void loop(){
  if (bg_on){background();}
//   Print the pin states out to serial 
  pd.pinState()->update();
  pd.pinState()->print();
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) {bg_on=1;}
  if (millis()-timeLastEvent > bgWhiteTime && !bg_on) {
//    pd.adrLED1()->clear();
//    pd.adrLED2()->clear();
  }
}

void checkPinStates(){
  int trigger =0;
  if ( pd.pinState()->J126(1) ){ // Judge Fire
    //sends a pulse of light that fades from orange to red
    //first number is size of light pulse in LED pixels
    //second number is time delay in micro seconds between updating movement
    // third number of direction (use 1 or -1)

    //only for left ramp
    pd.adrLED1()->bullet2Color("orange", "red", 25,  4,  1);

   //use thos for both ramps (Note:  Due to two ramps, this runs slower, so the delay is shorter)
   //pd.chaseAllAdr2Color("orange", "red", 10, 0, 1);

    trigger = 1; 
  }

 if ( pd.pinState()->J126(2) ){ //Judge Fear
    pd.adrLED1()->bullet2Color("blue", "blue", 25,  4,  1);
    trigger = 1; 
  }

  if ( pd.pinState()->J126(3) ){ //Judge Death
    pd.adrLED1()->bullet2Color("red", "red", 25,  4,  1);
    trigger = 1; 
  }
  if ( pd.pinState()->J126(4) ){ // Judge Mortis
    pd.adrLED1()->bullet2Color("green", "green", 25,  4,  1);
    trigger=1;
  }
  if ( pd.pinState()->J126(5) ){ // Pursuit Left
    pd.adrLED1()->bullet2Color("red", "orange", 25,  4,  1);
    trigger=1;
  }
  
  if ( pd.pinState()->J126(6) ){ // Pursuit Right
    pd.adrLED1()->bullet2Color("red", "white", 2,  4,  1);
    pd.adrLED1()->bullet2Color("white", "blue", 2,  4,  -1);
    pd.adrLED1()->bullet2Color("blue", "red", 2,  4,  1);
    trigger =1;
  }
  
  if ( pd.pinState()->J126(7) ){ // Black Out
    //using RGB to specify dark blue
    pd.adrLED1()->bullet2RGB(0,0,200, 0,0,50, 25,  4,  1);
    trigger =1;
  }
  
  if ( pd.pinState()->J126(8) ){ // Cursed Earth
  }
  if ( pd.pinState()->J126(13) ){ // Lower Left
  }


  if ( pd.pinState()->J126(14) ){ // Globe
    //pulse green-gold for ecah lock
    lock_count = lock_count +1;
    for (int i = 0; i<lock_count; i++) {
       pd.adrLED1()->bullet2Color("green", "yellow", 2,  4,  1);
    }
    if (lock_count == 3) {lock_count = 0;}
    trigger =1;
  }
  
  if ( pd.pinState()->J126(15) ){ // Right Ramp
  }
  
  if ( pd.pinState()->J126(16) ){ // Insert
  }

//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   pd.pinState()->reset();
   trigger =0;
   bg_on = 0;
   timeLastEvent = millis();
  }

//end function checkPinStates
}



void background() {
  pd.adrLED1()->sparkle(color,20);
  if (random(1000) == 0) {
    if (color == "red") color = "blue";
    else if (color == "blue") color = "white";
    else color = "red";
  }
}
