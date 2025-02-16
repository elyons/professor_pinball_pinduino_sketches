//Eric Lyons and Seth Hartmann 2025

//
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.2
//Uses pinduino library

#include <pinduino.h>
int N_LEDS = 39;
int mid = N_LEDS/2;
int aLEDNum1 = N_LEDS;
int aLEDNum2 = 0;


pinduino pd (aLEDNum1, aLEDNum2, "Nano");

int bg_on = 1;

unsigned long timeLastEvent = 0; // time last event was last triggered
unsigned long startChaseWaitTime = 20000; //Amount of time to wait before chase lights start up again 1000 == 1 second
String color = "yellow"; //attract color
int bg_style = 1;

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.pinState()->reset();
}

void loop(){
  if (bg_on){backgroundChase();}
    for (int i=0; i<500; i=i+1) { //check pinstates for a while    
      pd.pinState()->update();
    }
//  Print the pin states out to serial 
//  pd.pinState()->print();
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) {bg_on=1;}
}

///////////////////////////////////////////
///FLASHER AND COIL TABLE FOR P11 and P12
///////////////////////////////////////////
  //P11-1 01A Outhole
  //P11-1 01C PinBot Flasher
  //P11-3 02A Ball Release Shooter Lane
  //P11-3 02C Dracular Flasher
  //P11-4 03A Catapult
  //P11-4 03C Marilyn Flasher
  //P11-5 04A Middle 3-bank Drop Target
  //P11-5 04C Santa Flasher
  //P11-6 05A Top Eject Hole
  //P11-6 05C Gorbie Flasher
  //P11-7 06A Right 3-bank Drop Target
  //P11-7 06C Left Ramp Flasher
  //P11-8 07A Spinout Kickbig
  //P11-8 07C Right Ramp Flasher
  //P11-9 08A Right Lock (Eject Hole)
  //P11-9 08C Spinout Flasher

  //P12-1 Top Ball Gate
  //P12-2 Insert Gen Illumin Relay
  //P12-4 Playfield Gen Illum
  //P12-5 A/C Select Relay
  //P12-6 Bell
  //P12-7 Knocker
  //P12-8 JACKPOT Flasher
  //P12-9 JOYRIDE Flasher

/// Note on A/C Select Relay:  P12-5 (solenoid 12)
/// 
/// P12-5 Off:  Relay connects the circuit A side of P11 and all of P12
/// P12-5 On:   Relay connects the circuit C side of P11
/// 
/// 
/// From the manual for Taxi: https://www.ipdb.org/files/2505/Williams_1988_Taxi_Manual.pdf
///   In its de-energized state, the Relay connects the 'circuit A power' 
///   to 16 "controlled" and "switched" solenoids (identified in the table
///   with no suffix letter or the letter A, after the solenoid number).
/// 
///   When the game program determines that the Solenoid A/C Select Relay (sol. 12)
///   must be energized, the relay connects 'circuit C power' to the eight group C 
///   solenoids (01C through 08C). 

///////////////////////////////////////////
////////////       END        /////////////
///////////////////////////////////////////
  
void checkPinStates(){
  int trigger =0;

//////////////////////////////////////
////////      P11-A/C        /////////
//////////////////////////////////////

  //P11-1 01A Outhole
  if ( pd.pinState()->P11(1) && !pd.pinState()->P12(5)){ 
    trigger = 1; 
  }

  //P11-1 01C PinBot Flasher
  if ( pd.pinState()->P11(1) && pd.pinState()->P12(5)){ 
    trigger = 1; 
  }
 
  //P11-3 02A Ball Release Shooter Lane
  if ( pd.pinState()->P11(3) && !pd.pinState()->P12(5)){ 
    trigger = 1; 
  }
  
  //P11-3 02C Dracular Flasher
  if ( pd.pinState()->P11(3) && pd.pinState()->P12(5)){ 
    trigger = 1; 
  }
  
  //P11-4 03A Catapult
  if ( pd.pinState()->P11(4) && !pd.pinState()->P12(5)){ 
    trigger = 1; 
  }
  
  //P11-4 03C Marilyn Flasher
  if ( pd.pinState()->P11(4) && pd.pinState()->P12(5)){ 
    trigger = 1; 
  }
  
  //P11-5 04A Middle 3-bank Drop Target
  if ( pd.pinState()->P11(5) && !pd.pinState()->P12(5)){ 
    trigger = 1; 
  }
  
  //P11-5 04C Santa Flasher
  if ( pd.pinState()->P11(5) && pd.pinState()->P12(5)){ 
    trigger = 1; 
  }
  
  //P11-6 05A Top Eject Hole
  if ( pd.pinState()->P11(6) && !pd.pinState()->P12(5)){ 
    trigger = 1; 
  }
  
  //P11-6 05C Gorbie Flasher
  if ( pd.pinState()->P11(6) && pd.pinState()->P12(5)){ 
    trigger = 1; 
  }
  
  //P11-7 06A Right 3-bank Drop Target
  if ( pd.pinState()->P11(7) && !pd.pinState()->P12(5)){ 
    trigger = 1; 
  }
  
  //P11-7 06C Left Ramp Flasher
  if ( pd.pinState()->P11(7) && pd.pinState()->P12(5)){ 
    trigger = 1; 
  }
  
  //P11-8 07A Spinout Kickbig
  if ( pd.pinState()->P11(8) && !pd.pinState()->P12(5)){ 
    trigger = 1; 
  }
 
  //P11-8 07C Right Ramp Flasher
  if ( pd.pinState()->P11(8) && pd.pinState()->P12(5)){ 
    trigger = 1; 
  }
  
  //P11-9 08A Right Lock (Eject Hole)
  if ( pd.pinState()->P11(9) && !pd.pinState()->P12(5)){ 
    trigger = 1; 
  }
  
  //P11-9 08C Spinout Flasher
  if ( pd.pinState()->P11(9) && pd.pinState()->P12(5)){ 
    trigger = 1; 
  }

//////////////////////////////////////
////////          P12        /////////
//////////////////////////////////////
  
  //P12-1 Top Ball Gate
  if ( pd.pinState()->P12(1) && !pd.pinState()->P12(5)){ 

    trigger =1;
  }

  //P12-2 Insert Gen Illumin Relay
  if ( pd.pinState()->P12(2) && !pd.pinState()->P12(5)){

//    trigger =1; // Probably good to leave this alone 
  }

  //P12-4 Playfield Gen Illum
  if ( pd.pinState()->P12(4) && !pd.pinState()->P12(5)){ 

//    trigger =1; // Probably good to leave this alone
  }

  //P12-5 A/C Select Relay  DO NOT USE FOR A LIGHTING EFFECT 

  //P12-6 Bell
  if ( pd.pinState()->P12(6) && !pd.pinState()->P12(5)){ 

    trigger =1;
  }

  //P12-7 Knocker
  if ( pd.pinState()->P12(7) && !pd.pinState()->P12(5)){ 
  
    trigger=1;
  }

  ///P12-8 JACKPOT Flasher
  if ( pd.pinState()->P12(8) && !pd.pinState()->P12(5)){ 

    trigger=1;
  }

  //P12-9 JOYRIDE Flasher
  if ( pd.pinState()->P12(9) && !pd.pinState()->P12(5)){ 

    trigger =1;
  }

  //Note:  Sys 11 games have particularly "noisy" power on these circuits.  Can use this function to clear out pinstates for a fresh sweep
 if (pd.pinState()->P12(5)){ 
    trigger =1;
  }

  


//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   timeLastEvent = millis();
   pd.adrLED1()->clear();
   pd.pinState()->reset();
   trigger = 0;
   bg_on = 0;
  }

//end function checkPinStates
}

void backgroundChase() {
  if (bg_style) {
    pd.adrLED1()->sparkle(color,20,30);
    if (random(1000) == 0) {
        if (color == "yellow") color = "orange";
        else if (color == "orange") color = "red";
        else color = "yellow";
    }
  }
  else {
    pd.adrLED1()->dataStreamNoTail2Color("yellow", "red", 20, 20, 1);
  }
  if (random(1000) == 0) {
    if (bg_style) { bg_style = 0;}
    else {bg_style = 1;}
  }
}
