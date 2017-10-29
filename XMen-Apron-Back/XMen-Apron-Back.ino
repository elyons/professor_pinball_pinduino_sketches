//Eric Lyons 2015
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.2
//Uses pinduino library

#include <pinduino.h>
int N_LEDS = 27;
int R_START = 13;

int aLEDNum1 = N_LEDS;
int aLEDNum2 = 0;
int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");

int bg_on = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 60000; //Amount of time to wait before chase lights start up again 1000 == 1 second
int bgWhiteTime = 500; // time after last event to turn all LEDs to white
int bgOn=1;
String color = "white"; //attract color

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
}

void loop(){
  if (bg_on){backgroundChase();}
  pd.pinState()->update();
//   Print the pin states out to serial 
//  pd.pinState()->print();
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) {bg_on=1;}
    if (millis()-timeLastEvent > bgWhiteTime && !bg_on) {
      pd.adrLED1()->color("white", 255);
  }
}

void checkPinStates(){
  int trigger =0;
  
  if ( pd.pinState()->J6(1) ){
      pd.adrLED1()->color("blue", 255);
      delay(50);
      pd.adrLED1()->clear();
      trigger =1;
  }
  if ( pd.pinState()->J6(2) ){ }
  if ( pd.pinState()->J6(3) ){ 
    pd.adrLED1()->clear();
    pd.adrLED1()->color("blue", 255);
    delay(300);
  }
  if ( pd.pinState()->J6(4) ){ 
    pd.adrLED1()->clear();
    pd.adrLED1()->spreadInFromPoint2Color (R_START, "blue", "sky", 300);
    delay(300);
    pd.adrLED1()->fadeOut(200);
    trigger=1;
  }
  if ( pd.pinState()->J6(5) ){
    pd.adrLED1()->clear();
    pd.adrLED1()->spreadInFromPoint2Color (R_START, "sky", "blue", 300);
    delay(300);
    pd.adrLED1()->fadeOut(200);
    trigger=1;
  }
  if ( pd.pinState()->J6(6)  and bg_on==0 ){
    pd.adrLED1()->color("red",255);
    pd.adrLED1()->spreadOutFromPoint (R_START, 400);
    trigger =1;
  }
  if ( pd.pinState()->J6(7) ){
    pd.adrLED1()->clear();
    delay(50);
    pd.adrLED1()->color("yellow", 255);
    delay(100);
    pd.adrLED1()->clear();
    delay(50);
    trigger =1;
  }
  if ( pd.pinState()->J6(8) ){ 
    pd.adrLED1()->color("red", 255);
    delay(50);
    trigger =1;
  }
  if ( pd.pinState()->J7(2) ){ 
    pd.adrLED1()->color("blue", 255);
    delay(100);
    pd.adrLED1()->fadeColor2Color("blue","red",100);
    delay(50);
    pd.adrLED1()->fadeOut(100);
    delay(100);
    trigger =1;
  }
  if ( pd.pinState()->J7(3) ){
    pd.adrLED1()->fadeColor2Color("yellow","blue",200);
    pd.adrLED1()->fadeOut(100);
    //pd.adrLED1()->chase2Color("blue", "yellow", N_LEDS, 20, -1);
    trigger=1;
  }
  if ( pd.pinState()->J7(4) ){ 
      pd.adrLED1()->color("red", 255);
      delay(50);
      trigger =1;
  }
  if ( pd.pinState()->J7(6) ){
      pd.adrLED1()->color("blue", 255);
      delay(50);
      trigger =1;
  }
  if ( pd.pinState()->J7(7) ){
    pd.adrLED1()->clear();
    pd.adrLED1()->spreadInFromPoint2Color (R_START, "yellow", "red", 400);
    delay(300);
    pd.adrLED1()->fadeOut(200);
    delay(300);
    trigger=1;
  }
  if ( pd.pinState()->J7(8) ){
    pd.adrLED1()->clear();
    pd.adrLED1()->spreadInFromPoint2Color (R_START, "red", "blue", 400);
    delay(300);
    pd.adrLED1()->fadeOut(200);
    delay(300);
    trigger=1;
  }
  if ( pd.pinState()->J7(9) ){
  }
  if ( pd.pinState()->J7(10) ){
  }

//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   if (pd.pinState()->J6(6) == 0) timeLastEvent = millis();
   pd.adrLED1()->clear();
   pd.pinState()->reset();
   trigger =0;
   bg_on = 0;
  }

//end function checkPinStates
}



void backgroundChase() {
  pd.adrLED1()->sparkle(color,20);
  if (random(1000) == 0) {
    if (color == "blue") color = "red";
    else if (color == "red") color = "white";
    else if (color == "white") color = "yellow";
    else color = "blue";
  }

//  pd.adrLED1()->clear();
//  pd.adrLED1()->spreadInFromPoint2Color(R_START,"sky", "blue", 500);
//  pd.adrLED1()->fadeOut(200);
//  delay(100);
//  pd.adrLED1()->color("blue",150);
//  pd.adrLED1()->fadeOut(200);
//  delay(100);
//  pd.adrLED1()->color("blue",100);
//  pd.adrLED1()->fadeOut(200);
//  delay(400);
//  pd.adrLED1()->color("blue",100);
//  pd.adrLED1()->fadeOut(300);
//  for (int i=0; i<100; i=i+1){
//      pd.pinState()->update();
//      delay(10);
//  }  
}


