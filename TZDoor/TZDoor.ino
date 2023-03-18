//Eric Lyons 2016
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3
//Uses pinduino library

#include <pinduino.h>

int aLEDNum1 = 17; // translite
int aLEDNum2 = 0; 
int aLEDNum3 = 0;
int N_LEDS=aLEDNum1;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");

int bg_chase_on = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
long startChaseWaitTime = 1000; //Amount of time to wait before chase lights start up again 1000 == 1 second
String  color = "white";

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
  if (millis()-timeLastEvent > startChaseWaitTime) {bg_chase_on=1;}
  if (bg_chase_on){backgroundChase();}
}

void checkPinStates(){
  int trigger =0;
  
  if ( pd.pinState()->J126(1) ){ // Bumpers
    pd.adrLED1()->color("red", 255);
    delay(300);
    pd.adrLED1()->clear();
    delay(20);
    trigger=1;
  }
  if ( pd.pinState()->J126(2) ){ //Power Payoff
    pd.adrLED1()->color("blue", 255);
    delay(300);
    pd.adrLED1()->clear();
    delay(20);
    trigger=1;
  }
  if ( pd.pinState()->J126(3) ){ // Mini Playfield
    pd.adrLED1()->fadeIn("red", 1000);
    delay(1000);
    pd.adrLED1()->fadeOut(500);
    trigger=1;
  }
  if ( pd.pinState()->J126(4) ){ //Upper left ramp
    pd.adrLED1()->fadeOut(200);
    pd.adrLED1()->chase2Color("white", "white",N_LEDS, 8, -1);
    pd.adrLED1()->chase2Color("white", "blue",N_LEDS, 8, 1);
    pd.adrLED1()->chase2Color("blue", "blue",N_LEDS, 8, -1);
    pd.adrLED1()->chase2Color("blue", "white",N_LEDS, 8, 1);
    trigger=1;
  }
  if ( pd.pinState()->J126(5) ){ //Left Magnet
    trigger=1;
  }
  if ( pd.pinState()->J126(6) ){ // Upper right Magenet
    trigger=1;
  }
  if ( pd.pinState()->J126(7) ){ // Lower right magnet
//    pd.adrLED1()->chase2ColorFromPoint(N_LEDS/2,"blue","white", 10,5);
    trigger=1;
  }
  if ( pd.pinState()->J126(8) ){ //Gumball motor
    pd.adrLED1()->fadeIn("red", 500);
    pd.adrLED1()->fadeColor2Color("red","blue",500);
    pd.adrLED1()->fadeColor2Color("blue","green",500);
    pd.adrLED1()->fadeColor2Color("green","red",500);
    pd.adrLED1()->fadeOut(500);
    trigger=1;
  }
  if ( pd.pinState()->J126(9) ){ 
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
  pd.adrLED1()->sparkle(color,20);
  if (random(1000) == 0) {
      if (color == "white") color = "blue";
      else if (color == "blue") color = "red";
      else color = "blue";

  }

}


