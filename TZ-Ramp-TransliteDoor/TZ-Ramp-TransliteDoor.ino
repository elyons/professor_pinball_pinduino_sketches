//Eric Lyons 2018
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3
//Uses pinduino library

#include <pinduino.h>

int aLEDNum1 = 44; // ramp
int aLEDNum2 = 17; // translite door
int aLEDNum3 = 0;
int N_LEDS=aLEDNum1;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");

int attractRampOn = 1;
int attractDoorOn = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
long startRamp = 20000; //Amount of time to wait before ramp lights start up again 1000 == 1 second
long startDoor = 1000; //Amount of time to wait before door lights start up again 1000 == 1 second
int whiteWaitTime = 100; //Amount of time to wait before gumball goes to white
String rampColor = "white";
String doorColor = "white";


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
  if (millis()-timeLastEvent > startRamp) {attractRampOn=1;}
  if (millis()-timeLastEvent > startDoor) {attractDoorOn=1;}
  if (attractRampOn){attractRamp();}
  if (attractDoorOn){attractDoor();}
}

void checkPinStates(){
  int trigger =0;
  
  if ( pd.pinState()->J126(1) ){ // Bumpers
    pd.adrLED2()->color("red");
    pd.adrLED1()->chaseRGB(50,50,50,1, 5, -1);
    pd.adrLED1()->chaseRGB(50,50,50,1, 5, 1);
    pd.adrLED2()->clear();
    trigger=1;
  }
  if ( pd.pinState()->J126(2) ){ //Power Payoff
    pd.adrLED2()->color("blue");
    pd.adrLED1()->spreadInFromPoint2RGB (1, 50,50,50, 0,0,255, 300);
    delay(500);
    pd.adrLED1()->fadeOut(500);
    pd.adrLED2()->clear();    
    trigger=1;
  }
  if ( pd.pinState()->J126(3) ){ // Mini Playfield
    pd.adrLED2()->color("red");
    pd.adrLED1()->spreadInFromPoint2RGB(N_LEDS/2,50,50,50, 0,0,255, 700);
    delay(100);
    pd.adrLED1()->fadeOut(500);
    pd.adrLED2()->clear();    
    trigger=1;
  }
  if ( pd.pinState()->J126(4) ){ //Upper left ramp
    pd.adrLED2()->color("white");
    pd.adrLED1()->chase2Color("white", "blue",N_LEDS, 8, -1);
    pd.adrLED2()->chase2Color("white", "white",aLEDNum2, 8, -1);
    pd.adrLED2()->chase2Color("white", "blue",aLEDNum2, 8, 1);
    pd.adrLED2()->chase2Color("blue", "blue",aLEDNum2, 8, -1);
    pd.adrLED2()->chase2Color("blue", "white",aLEDNum2, 8, 1);

    trigger=1;
  }
  if ( pd.pinState()->J126(5) ){ //Left Magnet
  }
  if ( pd.pinState()->J126(6) ){ // Upper right Magenet
  }
  if ( pd.pinState()->J126(7) ){ // Lower right magnet
  }
  if ( pd.pinState()->J126(8) ){ //Gumball motor
    pd.adrLED2()->fadeIn("red", 500);
    pd.adrLED2()->fadeColor2Color("red","blue",500);
    pd.adrLED2()->fadeColor2Color("blue","green",500);
    pd.adrLED2()->fadeColor2Color("green","red",500);
    pd.adrLED2()->fadeOut(500);
    trigger=1;
  }
  if ( pd.pinState()->J126(9) ){ 
  }

  
//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   pd.adrLED1()->clear();
   pd.pinState()->reset();
   trigger =0;
   attractRampOn = 0;
   attractDoorOn = 0;
   timeLastEvent = millis();
  }
//end function checkPinStates
}



void attractRamp() {
  pd.adrLED1()->sparkle(rampColor,20);
  if (random(1000) == 0) {
    if (rampColor == "white") rampColor = "blue";
    else if (rampColor == "blue") rampColor = "red";
    else rampColor = "white";
  }
}

void attractDoor() {
  pd.adrLED2()->sparkle(doorColor,20);
  if (random(1000) == 0) {
    if (doorColor == "white") doorColor = "blue";
    else if (doorColor == "blue") doorColor = "red";
    else doorColor = "white";
  }
}


