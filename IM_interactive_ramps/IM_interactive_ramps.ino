//Eric Lyons 2015
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3 
// (now using Arduino Nano and LEDs mounted on the side of the ramps)
//Uses pinduino library

#include <pinduino.h>
int N_LEDS = 95;
int aLEDNum1 = N_LEDS;
int aLEDNum2 = 0;
int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");

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
String chaseColor = "red"; // var to hold bg chase color

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
}

void loop(){
  if (bg_chase_on){backgroundChase();}
  pd.pinState()->update();
//   Print the pin states out to serial 
//  pd.pinState()->print();
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) {bg_chase_on=1;}
}

void checkPinStates(){
  int trigger =0;
  
  if ( pd.pinState()->J6(1) ){
    pd.adrLED1()->fadeIn("purple", 300);
    delay(20);
    pd.adrLED1()->fadeOut(300);
    delay(20);
    trigger = 1; 
  }
  if ( pd.pinState()->J6(2) ){
    pd.adrLED1()->chase2Color("red", "yellow", N_LEDS/4,3,1);
    trigger = 1; 
  }
  if ( pd.pinState()->J6(3) ){ 
    pd.adrLED1()->chase2Color("cyan", "red", N_LEDS/6, 0, 1);
    trigger = 1; 
  }
  if ( pd.pinState()->J6(4) ){ //Monger chest
  }
  if ( pd.pinState()->J6(5) ){ // whiplash
    pd.adrLED1()->fadeInRGB(30, 255, 30, 100);
    pd.adrLED1()->spreadOutToPoint(N_LEDS/2, 100);
    pd.adrLED1()->spreadInFromPointRGB(N_LEDS/2,60, 255, 60, 50);
    delay(200);
    pd.adrLED1()->fadeOut(200);
    trigger =1;
  }
  if ( pd.pinState()->J6(6) ){ // Mark VI
    pd.adrLED1()->fadeInRGB(100,100,255, 200);
    delay(20);
    pd.adrLED1()->fadeOut(200);
    trigger =1;
  }
  if ( pd.pinState()->J6(7) ){ //Left ramp bottom
    pd.adrLED1()->chase2Color("red", "yellow", N_LEDS/4, 3, -1);
    trigger =1;
  }
  if ( pd.pinState()->J6(8) ){ //Right ramp bottom
    pd.adrLED1()->chase2Color("red", "yellow", N_LEDS/4, 3, -1);
    trigger =1;
  }
  if ( pd.pinState()->J7(6) ){ //pops
    for (int i = 0; i < 14; i = i + 1) {
      pd.adrLED1()->explosionRGB (random(N_LEDS), 255,random(100)+50,0, random(10)+5);
      pd.adrLED1()->fadeOut(50);
    }
    trigger =1;
  }
  if ( pd.pinState()->J7(7) ){ //Left ramp top
    pd.adrLED1()->chase2Color("yellow", "blue", N_LEDS/4, 3, 1);
    trigger =1;
  }
  if ( pd.pinState()->J7(8) ){//War Machine front
    pd.adrLED1()->chase2Color("cyan", "red", N_LEDS/6, 0, 1);
    trigger=1;
  }
  if ( pd.pinState()->J7(9) ){//monger center lane
  }

//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   pd.adrLED1()->clear();
   pd.pinState()->reset();
   trigger =0;
   bg_chase_on = 0;
   timeLastEvent = millis();
  }

//end function checkPinStates
}



void backgroundChase() {
  pd.adrLED1()->chase(chaseColor, 6, 15, 1);
  if (chaseColor == "red") {chaseColor="yellow";}
  else {chaseColor = "red";}
}

