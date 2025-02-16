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
String color = "white"; //attract color
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
///////////////////////////////////////////
////////////       END        /////////////
///////////////////////////////////////////
  
void checkPinStates(){
  int trigger =0;

  //P11-1 01A
  if ( pd.pinState()->J6(1) && pd.pinState()->P12(8)  && !pd.pinState()->P12(4) && !pd.pinState()->P12(5)){ // outhole P11-1
  // Trigger an event so pinduino attact mode shuts off.
//    pd.adrLED1()->color("red",255);
//    delay(1000);
    trigger = 1; 
  }

  
  //P11-3
  if ( pd.pinState()->P11(3) && pd.pinState()->P12(8) && !pd.pinState()->P12(4) && !pd.pinState()->P12(5)){ // upper playfield and top flashers (2)
    pd.adrLED1()->chase2ColorFromPoint(mid, "white", "red", 10, 5);
    trigger = 1; 
  }

  //P11-4
  if ( pd.pinState()->P11(4) && pd.pinState()->P12(8) && !pd.pinState()->P12(4) && !pd.pinState()->P12(5)){ //left backglass flasher
  }

  //P11-5
  if ( pd.pinState()->J6(4) && pd.pinState()->P12(8) && !pd.pinState()->P12(4) && !pd.pinState()->P12(5)){ // right backglass flasher
  }

  //P11-6
  if ( pd.pinState()->P11(6) && pd.pinState()->P12(8) && !pd.pinState()->P12(4) && !pd.pinState()->P12(5)){ //lower playfield and top flashers (1)
    pd.adrLED1()->chase2ColorFromPoint(mid, "white", "blue", 10, 5);
    trigger = 1; 
  
  }

  //P11-7
  if ( pd.pinState()->P11(7) && pd.pinState()->P12(8) && !pd.pinState()->P12(4) && !pd.pinState()->P12(5)){ //energy flasher
    pd.adrLED1()->color("red",255);
    delay(200);
    trigger =1;
  }

  //P11-8
  if ( pd.pinState()->P11(8) && pd.pinState()->P12(8) && !pd.pinState()->P12(4) && !pd.pinState()->P12(5)){ //left playfield flasher
    pd.adrLED1()->chase2ColorFromPoint(mid, "white", "blue", 10, 5);
    trigger =1;
  }

  //P11-9
  if ( pd.pinState()->P11(9) && pd.pinState()->P12(8) && !pd.pinState()->P12(4) && !pd.pinState()->P12(5)){ //sun flasher
    pd.adrLED1()->fadeIn("red",200);
    delay(100);
    pd.adrLED1()->fadeOut(200);
  }

  //P12-1
  if ( pd.pinState()->P12(1) ){ //backglass face
  }

  //P12-2
  if ( pd.pinState()->P12(2) ){ // right eye playfield face flasher
  }

  //P12-4
  if ( pd.pinState()->P12(4) ){ // blackglass GI
  }

  //P12-5
  if ( pd.pinState()->P12(5) ){ //playfield GI
  }

  //P12-6
  if ( pd.pinState()->P12(6) && !pd.pinState()->P12(4) && !pd.pinState()->P12(5) && !pd.pinState()->P12(8)){ //visor motor
    pd.adrLED1()->bullet2Color("blue", "red", 40, 10, 1);
    pd.adrLED1()->bullet2Color("red", "blue", 40, 10, -1);
    trigger =1;
  }

  //P12-7
  if ( pd.pinState()->P12(8) ){ // solenoid select relay
//    pd.adrLED1()->color("purple",255);
//    delay(1000);
//    trigger=1;
  }

  //P12-8
  if ( pd.pinState()->P12(8) ){ // top flasher (3)
    pd.adrLED1()->bullet("red", 3, 10,  1);
    pd.adrLED1()->bullet("red", 3, 10,  -1);
    trigger=1;
  }

  //P12-9
  if ( pd.pinState()->P12(9) ){ // top flasher (4)
    pd.adrLED1()->bullet("blue", 3, 10,  1);
    pd.adrLED1()->bullet("blue", 3, 10,  -1);
    trigger =1;
  }

  //clear out if there is noise due to coils
 if ( pd.pinState()->P12(4) && pd.pinState()->P12(5) && pd.pinState()->P12(6) && pd.pinState()->P12(8)){ 
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
        if (color == "white") color = "red";
        else if (color == "red") color = "blue";
        else color = "white";
    }
  }
  else {
    pd.adrLED1()->dataStreamNoTail2Color("blue", "red", 20, 20, 1);
  }
  if (random(1000) == 0) {
    if (bg_style) { bg_style = 0;}
    else {bg_style = 1;}
  }
}
