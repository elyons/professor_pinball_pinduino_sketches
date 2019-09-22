//Eric Lyons 2016
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3
//Uses pinduino library

#include <pinduino.h>

int aLEDNum1 = 28;
int aLEDNum2 = 35;

pinduino pd (aLEDNum1, aLEDNum2, "Nano");

int bg_chase_on = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 20000; //Amount of time to wait before chase lights start up again 1000 == 1 second
int whiteWaitTime = 200; //Amount of time to wait before gumball goes to white
String color = "cyan";

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.pinState()->reset();
  pd.adrLED1()->color("white", 255);
}

void loop(){
  pd.pinState()->update();
//   Print the pin states out to serial 
//  pd.pinState()->print();
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) { bg_chase_on=1; }
  if (millis()-timeLastEvent > whiteWaitTime && bg_chase_on ==0) { pd.adrLED1()->color("white", 255);}
  if (bg_chase_on){backgroundChase();}
}

void checkPinStates(){
  int trigger =0;
  
  if ( pd.pinState()->J126(1) ){
    pd.adrLED1()->color("yellow",255); // boat right flasher yellow
    pd.adrLED2()->bullet2Color("blue", "white", 30,7,-1);
    trigger=1;
  }
  if ( pd.pinState()->J126(2) ){ 
    trigger=1;
  }
  if ( pd.pinState()->J126(3) ){ 
    trigger=1;
  }
  if ( pd.pinState()->J126(4) ){ 
    trigger=1;
  }
  if ( pd.pinState()->J126(5) ){ //Venice Beach ramp and right two ramp domes
    pd.adrLED1()->color("sky",255);
    pd.adrLED2()->bullet2Color("white", "blue", 30,7,1);
    delay(300);
    trigger=1;
  }
  if ( pd.pinState()->J126(6) ){ // left tital wave and earthquake insert flashers
    pd.adrLED1()->color("yellow",255);
    delay(300);
    trigger=1;
  }
  if ( pd.pinState()->J126(7) ){ //right tital wave 
    pd.adrLED1()->color("blue",255);
    delay(500);
    trigger=1;
  }
  if ( pd.pinState()->J126(8) ){ 
    pd.adrLED1()->color("green",255); // pop inserts
//    pd.adrLED2()->color("green",255); // pop inserts
    delay(200);
    trigger=1;
  }
  if ( pd.pinState()->J126(9) ){ 
    trigger=1;
  }
  if ( pd.pinState()->J126(10) ){ 
    trigger=1;
  }
  if ( pd.pinState()->J126(11) ){ 
    trigger=1;
  }
  if ( pd.pinState()->J126(12) ){ 
    trigger=1;
  }
  if ( pd.pinState()->J126(13) ){ // Flash: dome flashers on back panel
    pd.adrLED1()->color("red",255);
    pd.adrLED2()->spreadInFromPoint2RGB (14, 150,150,150, 0,0,255, 300);
    delay(500);
    pd.adrLED2()->fadeOut(500);    

    delay(200);
    trigger=1;
  }
  if ( pd.pinState()->J126(14) ){  //Flash:  shark and left boat right light -- red
    //pd.adrLED1()->color("red",255);
    pd.adrLED1()->spreadInFromPoint2Color (14, "red", "blue", 100);
    delay(500);
    trigger=1;
  }
  if ( pd.pinState()->J126(15) ){  //Flash:  shark flipper
    pd.adrLED1()->color("blue",255);
    delay(300);
    trigger=1;
  }
  if ( pd.pinState()->J126(16) ){  
    trigger=1;
  }

  
//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   pd.adrLED1()->clear();
   pd.adrLED2()->clear();
   pd.pinState()->reset();
   trigger =0;
   bg_chase_on = 0;
   timeLastEvent = millis();
  }
//end function checkPinStates
}



void backgroundChase() {
    pd.adrLED1()->sparkle(color,10);
    pd.adrLED2()->sparkle(color,10);
    if (random(1000) == 0) {
    if (color == "cyan") color = "blue";
    else if (color == "blue") color = "sky";
    else color = "white";
  }
}


