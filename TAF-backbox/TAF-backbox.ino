//Eric Lyons 2015
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.2
//Uses pinduino library

#include <pinduino.h>
int N_LEDS = 29;
int MID = N_LEDS/2;

int aLEDNum1 = N_LEDS;
int aLEDNum2 = 0;
int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3);

int bg_chase_on = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 30000; //Amount of time to wait before chase lights start up again 1000 == 1 second

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
    pd.adrLED1()->clear();
    pd.adrLED1()->spreadInFromPoint2Color (MID, "yellow", "red", 400);
    delay(300);
    pd.adrLED1()->fadeOut(200);
    delay(300);
    trigger=1;
//    pd.adrLED1()->color("blue", 255);
//    delay(50);
//    pd.adrLED1()->clear();
//    trigger =1;
  }
  if ( pd.pinState()->J6(2) ){ 
    pd.adrLED1()->clear();
    pd.adrLED1()->spreadInFromPoint2Color (MID, "blue", "red", 400);
    delay(300);
    pd.adrLED1()->fadeOut(200);
    delay(300);
    trigger=1;
  }
  if ( pd.pinState()->J6(3) ){ 
    pd.adrLED1()->clear();
    delay(300);
    pd.adrLED1()->color("purple", 255);
    delay(300);
    pd.adrLED1()->color("blue", 255);
    delay(300);
    trigger=1;
  }
  if ( pd.pinState()->J6(4) ){ 
    pd.adrLED1()->clear();
    delay(300);  
    pd.adrLED1()->color("purple", 255);
    delay(100);
    pd.adrLED1()->fadeColor2Color("purple","red",500);
    delay(50);
    pd.adrLED1()->fadeOut(100);
    delay(300);
    trigger =1;
  }
  if ( pd.pinState()->J6(5) ){
    pd.adrLED1()->clear();
    pd.adrLED1()->spreadInFromPoint2Color (MID, "purple", "green", 400);
    delay(300);
    pd.adrLED1()->fadeOut(200);
    delay(300);
    trigger=1;
  }
  if ( pd.pinState()->J6(6)  and bg_chase_on==0 ){
    pd.adrLED1()->color("white",255);
    delay(100);
    pd.adrLED1()->color("red",255);
    delay(100);
    pd.adrLED1()->color("white",255);
    delay(100);
    pd.adrLED1()->color("red",255);
    delay(100);
    trigger=1;
  }
  if ( pd.pinState()->J6(7) ){
    pd.adrLED1()->clear();
    delay(50);
    pd.adrLED1()->color("yellow", 255);
    delay(100);
    pd.adrLED1()->clear();
    delay(50);
    trigger=1;
  }
  if ( pd.pinState()->J6(8) ){ 
    pd.adrLED1()->clear();
    delay(50);
    pd.adrLED1()->color("red", 255);
    delay(100);
    pd.adrLED1()->clear();
    delay(50);
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
  pd.adrLED1()->color("purple", 150);

//end function checkPinStates
}



void backgroundChase() {
  pd.adrLED1()->clear();
  pd.adrLED1()->spreadInFromPoint2Color(MID,"purple", "red", 500);
  delay(1000);
  pd.adrLED1()->fadeOut(1000);
  for (int i=0; i<100; i=i+1){
      pd.pinState()->update();
      delay(10);
  }  
}


