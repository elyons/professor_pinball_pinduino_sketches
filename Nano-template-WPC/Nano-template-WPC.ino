//Eric Lyons 2016
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3
//Uses pinduino library

#include <pinduino.h>

int aLEDNum1 = 50;
int aLEDNum2 = 50;

pinduino pd (aLEDNum1, aLEDNum2, "Nano");

int bg_chase_on = 0;
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 20000; //Amount of time to wait before chase lights start up again 1000 == 1 second
int whiteWaitTime = 1000; //Amount of time to wait before gumball goes to white

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
  if (millis()-timeLastEvent > whiteWaitTime) { pd.adrLED1()->fadeIn("white", 200);}
  if (bg_chase_on){backgroundChase();}
}

void checkPinStates(){
  int trigger =0;
  
  if ( pd.pinState()->J126(1) ){
    pd.adrLED1()->color("blue",255);
    pd.adrLED2()->color("blue",255);
    delay(500);
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
  if ( pd.pinState()->J126(5) ){ 
    trigger=1;
  }
  if ( pd.pinState()->J126(6) ){ 
    trigger=1;
  }
  if ( pd.pinState()->J126(7) ){ 
//    trigger=1;
  }
  if ( pd.pinState()->J126(8) ){ 
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
  if ( pd.pinState()->J126(13) ){ //extended WPC with extra 4-pin plug
    trigger=1;
  }
  if ( pd.pinState()->J126(14) ){  //extended WPC with extra 4-pin plug
    trigger=1;
  }
  if ( pd.pinState()->J126(15) ){  //extended WPC with extra 4-pin plug
    trigger=1;
  }
  if ( pd.pinState()->J126(16) ){  //extended WPC with extra 4-pin plug
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


