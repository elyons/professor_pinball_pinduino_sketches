//Eric Lyons 2018
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3
//Uses pinduino library

#include <pinduino.h>

int aLEDNum1 = 44; // ramp
int aLEDNum2 = 3; // gumball
int aLEDNum3 = 0;
int N_LEDS=aLEDNum1;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");

int bg_chase_on = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 20000; //Amount of time to wait before chase lights start up again 1000 == 1 second
int whiteWaitTime = 100; //Amount of time to wait before gumball goes to white
String color = "white";


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
//  if (millis()-timeLastEvent > whiteWaitTime) {
//    pd.adrLED2()->color("white", 200);
//}
  if (bg_chase_on){backgroundChase();}

}

void checkPinStates(){
  int trigger =0;
  
  if ( pd.pinState()->J126(1) ){ // Bumpers
    pd.adrLED2()->color("blue",255);
    pd.adrLED1()->chaseRGB(50,50,50,1, 5, -1);
    pd.adrLED1()->chaseRGB(50,50,50,1, 5, 1);
    trigger=1;
  }
  if ( pd.pinState()->J126(2) ){ //Power Payoff
    pd.adrLED2()->color("red",255);
    pd.adrLED1()->spreadInFromPoint2RGB (1, 50,50,50, 0,0,255, 300);
    delay(500);
    pd.adrLED1()->fadeOut(500);    
    trigger=1;
  }
  if ( pd.pinState()->J126(3) ){ // Mini Playfield
    pd.adrLED2()->color("blue",255);
    pd.adrLED1()->spreadInFromPoint2RGB(N_LEDS/2,50,50,50, 0,0,255, 700);
    delay(100);
    pd.adrLED1()->fadeOut(500);
    trigger=1;
  }
  if ( pd.pinState()->J126(4) ){ //Upper left ramp
    pd.adrLED2()->color("orange",255); // orange
    pd.adrLED1()->chase2Color("white", "blue",N_LEDS, 8, -1);
    trigger=1;
  }
  if ( pd.pinState()->J126(5) ){ //Left Magnet
  }
  if ( pd.pinState()->J126(6) ){ // Upper right Magenet
  }
  if ( pd.pinState()->J126(7) ){ // Lower right magnet
  }
  if ( pd.pinState()->J126(8) ){ //Gumball motor
    pd.adrLED2()->fadeColor2Color("red","orange",200);
    pd.adrLED2()->fadeColor2Color("orange","blue",200);
    pd.adrLED2()->fadeColor2Color("orange","red",200);
    delay(200);
    pd.adrLED2()->fadeOut(200);
    trigger=1;
  }
  if ( pd.pinState()->J126(9) ){ 
    pd.adrLED2()->color("yellow",255);
    trigger=1;
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
  pd.adrLED2()->sparkle(color,20);
  if (random(1000) == 0) {
    if (color == "white") color = "blue";
    else if (color == "blue") color = "red";
    else color = "white";
  }
}


