//Eric Lyons 2016
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3 (Nano!)
//Uses pinduino library

#include <pinduino.h>
int N_LEDS = 132;
int N_LEDS2 = 59;
int R_START = 57;

int aLEDNum1 = N_LEDS;
int aLEDNum2 = N_LEDS2;
int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");

//J124-1 Sprit Ring
//J124-2 Saw
//J124-3 Jets
//J124-5 Trunk

int backgroundOn = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 20000; //Amount of time to wait before chase lights start up again 1000 == 1 second
String color1 = "orange"; //attract color
String color2 = "cyan"; //attract color

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
}

void loop(){
  if (backgroundOn){background();}
  pd.pinState()->update();
//   Print the pin states out to serial 
//  pd.pinState()->print();
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) {backgroundOn=1;}
}

void checkPinStates(){
  int trigger =0;
  
  if ( pd.pinState()->J126(1) ){  //  trunk motor
    pd.adrLED2()->color("green");
    pd.adrLED1()->fadeIn("red",50);
    pd.adrLED1()->fadeOut(50);
    trigger =1;
  }
  if ( pd.pinState()->J126(2) ){ //  trunk motor
    pd.adrLED2()->color("green");
    pd.adrLED1()->fadeIn("red",50);
    pd.adrLED1()->fadeOut(50);
    trigger =1;
  }
  if ( pd.pinState()->J126(4) ){ // return lane flasher
    pd.adrLED2()->color(50,255,0);
    pd.adrLED1()->chase2Color("red", "orange",N_LEDS/15, 0, 1);
    trigger =1;
  }
  if ( pd.pinState()->J126(5) ){ //top kickout
    pd.adrLED2()->spreadInFromPoint2Color(N_LEDS2/2, "yellow", "cyan", 0);
    trigger =1;
  }
  if ( pd.pinState()->J126(8) ){ // trap door flasher
    pd.adrLED2()->colorRGB(0,255,255);
    pd.adrLED1()->chase2ColorFromPoint( R_START, "purple", "red", 10, 0); 
    pd.adrLED1()->fadeOut(50);
    trigger=1;
  }
  if ( pd.pinState()->J126(13) ){  //spirit ring flasher
    pd.adrLED2()->colorRGB(0,0,255);
    pd.adrLED1()->spreadInFromPoint2Color (R_START, "red", "blue", 0);
    pd.adrLED1()->fadeOut(50);
    trigger=1;
  }
  if ( pd.pinState()->J126(14) ){ // sow flasher
    pd.adrLED2()->color("green");
    pd.adrLED1()->chase2Color("red", "yellow",N_LEDS/8, 0, 1); 
    trigger =1;
  }
  if ( pd.pinState()->J126(15) ){ // jet flasher
    pd.adrLED2()->colorRGB(255,255,0);
    pd.adrLED1()->spreadInFromPoint2Color(R_START, "yellow", "red", 0);
    pd.adrLED1()->fadeOut(50);
    trigger =1;
  }
  if ( pd.pinState()->J126(16)){ // trunk flasher
    pd.adrLED2()->chase2ColorFromPoint( N_LEDS2/2, "cyan", "blue", 30, 0); 
    pd.adrLED2()->color("green");
    pd.adrLED1()->chase2Color("red", "yellow",N_LEDS/8, 0, -1);
    trigger =1;
  }
 
//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   pd.adrLED1()->clear();
   pd.pinState()->reset();
   trigger =0;
   backgroundOn = 0;
   timeLastEvent = millis();
   pd.adrLED2()->color("white");
  }

//end function checkPinStates
}



void background() {
  pd.adrLED1()->sparkle(color1,20,20);
  pd.adrLED2()->sparkle(color2,20,20);
 
  if (random(1000) == 0) {
    if (color1 == "orange") {color1 = "red"; color2="blue";}
    if (color1 == "red") {color1 = "yellow"; color2="green";}
    if (color1 == "yellow") {color1 = "purple"; color2="yellow";}
    else {color1 = "orange"; color2="cyan";}
  }
}
