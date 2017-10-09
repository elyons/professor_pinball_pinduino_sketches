//Eric Lyons 2016
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3
//Uses pinduino library

#include <pinduino.h>

int aLEDNum1 = 28;
int aLEDNum2 = 50;

pinduino pd (aLEDNum1, aLEDNum2, "Nano");

int bg_chase_on = 0;
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 20000; //Amount of time to wait before chase lights start up again 1000 == 1 second
int whiteWaitTime = 200; //Amount of time to wait before gumball goes to white

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.pinState()->reset();
}

void loop(){
  for (int i = 0; i < 500; i = i + 1) { //check pinstates for a while
    pd.pinState()->update();
  }
//   Print the pin states out to serial 
//  pd.pinState()->print();
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) { bg_chase_on=1; }
  if (millis()-timeLastEvent > whiteWaitTime) { pd.adrLED1()->color("white", 255);}
  if (bg_chase_on){backgroundChase();}
}

void checkPinStates(){
  int trigger =0;
  
  if ( pd.pinState()->J126(1) ){
    pd.adrLED1()->color("yellow",255); // boat right flasher yellow
    delay(300);
    trigger=1;
  }
  if ( pd.pinState()->J126(2) ){ 
    pd.adrLED1()->color("red",255);
    delay(500);
    trigger=1;
  }
  if ( pd.pinState()->J126(3) ){ 
    pd.adrLED1()->color("green",255);
    delay(500);
    trigger=1;
  }
  if ( pd.pinState()->J126(4) ){ 
    pd.adrLED1()->color("blue",255);
    delay(500);
    trigger=1;
  }
  if ( pd.pinState()->J126(5) ){ //Venice Beach ramp and right two ramp domes
    pd.adrLED1()->color("sky",255);
    delay(300);
    trigger=1;
  }
  if ( pd.pinState()->J126(6) ){ // left tital wave and earthquake insert flashers
    pd.adrLED1()->color("yellow",255);
    delay(300);
    trigger=1;
  }
  if ( pd.pinState()->J126(7) ){ //right tital wave (not registering)
    pd.adrLED1()->color("blue",255);
    delay(500);
    trigger=1;
  }
  if ( pd.pinState()->J126(8) ){ 
    pd.adrLED1()->color("green",255); // pop inserts
    delay(200);
    trigger=1;
  }
  if ( pd.pinState()->J126(9) ){ 
    pd.adrLED1()->color("green",255);
    delay(500);
    trigger=1;
  }
  if ( pd.pinState()->J126(10) ){ 
    pd.adrLED1()->color("blue",255);
    delay(500);
    trigger=1;
  }
  if ( pd.pinState()->J126(11) ){ 
    pd.adrLED1()->color("red",255);
    delay(500);
    trigger=1;
  }
  if ( pd.pinState()->J126(12) ){ 
    pd.adrLED1()->color("blue",255);
    delay(500);
    trigger=1;
  }
  if ( pd.pinState()->J126(13) ){ // Flash: dome flashers on back panel
    pd.adrLED1()->color("red",255);
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
  if ( pd.pinState()->J126(16) ){  //extended WPC with extra 4-pin plug
    pd.adrLED1()->color("green",255);
    delay(300);
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
  pd.adrLED1()->clear();
  pd.adrLED1()->color("white",255);
  pd.adrLED2()->color("white",255);
  for (int i = 0; i < 20000; i = i + 1) { //check pinstates for a while
    pd.pinState()->update();
  }
  pd.adrLED1()->fadeOut(1000);
  pd.pinState()->update();
  delay(500);
  pd.pinState()->update(); 
  pd.adrLED1()->fadeIn("blue",500);
  pd.pinState()->update();
  pd.adrLED1()->fadeColor2Color("blue","purple",500);
  pd.pinState()->update();
  pd.adrLED1()->fadeColor2Color("purple","red",500);
  pd.pinState()->update();
  pd.adrLED1()->fadeColor2Color("red","orange",500);
  pd.pinState()->update();
  pd.adrLED1()->fadeColor2Color("orange","yellow",500);
  pd.pinState()->update();
  pd.adrLED1()->fadeColor2Color("yellow","green",500);
  pd.pinState()->update();
  pd.adrLED1()->fadeColor2Color("green","blue",500);
  pd.pinState()->update();
  pd.adrLED1()->fadeOut(500);
  pd.pinState()->update();
  delay(500);
  pd.pinState()->update();
}


