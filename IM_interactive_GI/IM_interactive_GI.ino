//Eric Lyons 2015
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.2
//Uses pinduino library

/// ---=====  NOTE ====---
/// The LED string I used had the red and green channels switched.  
/// No idea why
/// So: adrLED1
/// Green -> red
/// Red -> green
/// Purple -> cyan
/// Cyan -> purple


#include <pinduino.h>
int N_LEDS = 30;
int aLEDNum1 = N_LEDS;
int aLEDNum2 = N_LEDS;
int aLEDNum3 = 1;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3);

// J6-1:  Flash Iron Monger 2x (BLK-BRN)
// J6-2:  Flash Right ramp top (BLK-RED)
// J6-3:  Flash War Machine x3 (BLK-ORG)
// J6-4:  Flash Monger chest (BLK-YEL)
// J6-5:  Flash Whiplash x2 (BLK-GRN)
// J6-6:  Flash Mark VI x2 (BLK-BLU)
// J6-7:  Flash Left Ramp Bottom (BLK-VIO)
// J6-8:  Flash Right ramp bottom (BLK-GRY)
// J7-6:  Flash: pop bumper (VIO-WHT)
// J7-7:  Flash: Left rampex top (VIO-GRN)
// J7-8:  Flash: War Machine front (VIO-BLU)
// J7-9:  Flash: Monger Center Lane (VIO-BLK)
// pin 9:  Iron Monger Motor (VIO-ORG)
// pin 10: Coil Right Sling (VIO-RED)
// pin 11: Coil Left Slign (VIO-BRN)
// pin 12: Coil Optional (VIO-GRY)

int bg_chase_on = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 30000; //Amount of time to wait before chase lights start up again 1000 == 1 second
int bgWhiteTime = 50;
String chaseColor = "red"; // var to hold bg chase color

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
}

void loop(){
//  if (bg_chase_on){backgroundChase();}
  pd.pinState()->update();
//   Print the pin states out to serial 
//  pd.pinState()->print();
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) {bg_chase_on=1;}
  if (millis()-timeLastEvent > bgWhiteTime) {
    pd.adrLED1()->color("white", 255);
    pd.adrLED2()->color("white", 255);
  }
}

void checkPinStates(){
  int trigger =0;
  
  if ( pd.pinState()->J6(1) ){
//    pd.adrLED1()->color("blue", 1);
//    pd.adrLED2()->color("purple", 1);
//    pd.fadeInAllAdr(200);
//    delay(200);
//    pd.fadeOutAllAdr(200);
      pd.adrLED2()->fadeIn("purple", 300);
      delay(120);
      pd.adrLED2()->fadeOut(300);
    trigger = 1; 
  }
  if ( pd.pinState()->J6(2) ){
    pd.adrLED1()->color("blue", 255);
    pd.adrLED2()->color("red", 255);
    delay(500);
    trigger = 1; 
  }
  if ( pd.pinState()->J6(3) ){ 
    pd.adrLED1()->color("green", 255);
    pd.adrLED2()->color("cyan", 255);    
    delay(500);
    trigger = 1; 
  }
  if ( pd.pinState()->J6(4) ){ //Monger chest
  }
  if ( pd.pinState()->J6(5) ){ // whiplash
    pd.adrLED1()->color("white", 255);
    pd.adrLED2()->color("cyan", 255);
    delay(500);
    trigger = 1; 
  }
  if ( pd.pinState()->J6(6) ){ // Make VI
    pd.adrLED1()->color("blue", 255);
    pd.adrLED2()->color("white", 255);
    delay(500);
    trigger = 1; }
  if ( pd.pinState()->J6(7) ){ //Left ramp bottom
    pd.adrLED1()->color("red", 255);
    pd.adrLED2()->color("red", 255);
    delay(500);
    trigger = 1; 
  }
  if ( pd.pinState()->J6(8) ){ //Right ramp bottom
    pd.adrLED1()->color("red", 255);
    pd.adrLED2()->color("red", 255);
    delay(500);
    trigger = 1;
  }
  if ( pd.pinState()->J7(6) ){ //pops
    pd.adrLED1()->color("green", 255);
    pd.adrLED2()->color("white", 255);
    delay(50);
    trigger = 1; 
  }
  if ( pd.pinState()->J7(7) ){ //Left ramp top
    pd.adrLED1()->color("white", 255);
    pd.adrLED2()->color("red", 255);
    delay(500);
    trigger = 1; 
  }
  if ( pd.pinState()->J7(8) ){//War Machine front
    pd.adrLED1()->color("green", 255);
    pd.adrLED2()->color("cyan", 255);
    delay(500);
    trigger = 1; 
  }
  if ( pd.pinState()->J7(9) ){//monger center lane
  }

//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
//   pd.adrLED1()->clear();
//   pd.adrLED2()->clear();
   pd.pinState()->reset();
   trigger =0;
   bg_chase_on = 0;
   timeLastEvent = millis();
  }
//   delay(100);
//   pd.adrLED1()->color("white", 255);
//   pd.adrLED2()->color("white", 255);

//end function checkPinStates
}



void backgroundChase() {
    pd.adrLED1()->color("white", 255);
    pd.adrLED2()->color("white", 255);
    delay(10000);
    int delay_time = 100;
    int fade_time = 200;
    for (int i=0; i<4; i=i+1) {     
      pd.adrLED1()->color("white", 255);
      pd.adrLED2()->color("white", 255);
      delay(delay_time);
      pd.adrLED1()->fadeOut(fade_time);
      pd.adrLED1()->color("green", 255);
      pd.adrLED2()->fadeOut(fade_time);
      pd.adrLED2()->color("red", 255);
      delay(delay_time);
      pd.adrLED1()->fadeOut(fade_time);
      pd.adrLED1()->color("blue", 255);
      pd.adrLED2()->fadeOut(fade_time);
      pd.adrLED2()->color("blue", 255);
      delay(delay_time);
      pd.adrLED1()->fadeOut(fade_time);
      pd.adrLED1()->color("red", 255);
      pd.adrLED2()->fadeOut(fade_time);
      pd.adrLED2()->color("green", 255);
      delay(delay_time);
      pd.adrLED1()->fadeOut(fade_time);
      pd.adrLED1()->color("yellow", 255);
      pd.adrLED2()->fadeOut(fade_time);
      pd.adrLED2()->color("yellow", 255);
      delay(delay_time);
      pd.adrLED1()->fadeOut(fade_time);
      pd.adrLED1()->color("purple", 255);
      pd.adrLED2()->fadeOut(fade_time);
      pd.adrLED2()->color("cyan", 255);
      delay(delay_time);
      pd.adrLED1()->fadeOut(fade_time);
      pd.adrLED1()->color("cyan", 255);
      pd.adrLED2()->fadeOut(fade_time);
      pd.adrLED2()->color("purple", 255);
      delay(delay_time);
      pd.adrLED1()->fadeOut(fade_time);
      delay_time = delay_time * 1.25;
      fade_time = fade_time * 1.25;
    }
    pd.adrLED1()->color("white", 255);
    pd.adrLED2()->color("white", 255);
    delay(1000);
    pd.adrLED1()->fadeColor2Color("white", "green", 5000);
    pd.adrLED2()->fadeColor2Color("white", "red", 5000);
    delay(1000);
    pd.adrLED1()->fadeColor2Color("green", "blue", 5000);
    pd.adrLED2()->fadeColor2Color("red", "blue", 5000);
    delay(1000);
    pd.adrLED1()->fadeColor2Color("blue", "red", 5000);
    pd.adrLED2()->fadeColor2Color("blue", "green", 5000);
    delay(1000);
    pd.adrLED1()->fadeColor2Color("red", "green", 5000);
    pd.adrLED2()->fadeColor2Color("green", "red", 5000);
    delay(1000);
    pd.adrLED1()->chase2Color("green", "blue", 50,  100,  -1);
    pd.adrLED2()->chase2Color("red", "blue", 50,  100,  -1);
    pd.adrLED1()->chase2Color("blue", "red", 50,  100,  1);
    pd.adrLED2()->chase2Color("blue", "green", 50,  100,  1);
  }

