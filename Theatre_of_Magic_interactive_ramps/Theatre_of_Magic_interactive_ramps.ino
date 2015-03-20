//Eric Lyons 2015
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.2
//Uses pinduino library

#include <pinduino.h>
int N_LEDS = 132;
int R_START = 57;

int aLEDNum1 = N_LEDS;
int aLEDNum2 = 0;
int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3);

//J6-3 Sprit Ring
//J6-4 Saw
//J6-5 Jets
//J6-6 Trunk

int backgroundOn = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 20000; //Amount of time to wait before chase lights start up again 1000 == 1 second

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
  
  if ( pd.pinState()->J6(3) ){ 
    pd.adrLED1()->spreadInFromPoint2Color (R_START, "red", "yellow", 0);
    pd.adrLED1()->fadeOut(50);
    trigger=1;
    pd.pinState()->resetJ6(3);  
  }
  if ( pd.pinState()->J6(4) ){ 
    pd.adrLED1()->chase2Color("red", "yellow",N_LEDS/8, 0, 1);
    trigger =1;
    pd.pinState()->resetJ6(4);  
  }
  if ( pd.pinState()->J6(5) ){
    for (int i =0; i <  pd.pinState()->J6(5); i++) {
      pd.adrLED1()->color("yellow",200);
      delay(30); 
      pd.adrLED1()->clear();
      pd.pinState()->update();
      delay(30); 
    }
    trigger =1;
    pd.pinState()->resetJ6(5);  

  }
  if ( pd.pinState()->J6(6)  and backgroundOn==0 ){
    pd.adrLED1()->chase2Color("red", "yellow",N_LEDS/8, 0, -1);
    trigger =1;
    pd.pinState()->resetJ6(6);  
  }
 
//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   pd.adrLED1()->clear();
//   pd.pinState()->reset();
   trigger =0;
   backgroundOn = 0;
   timeLastEvent = millis();
  }

//end function checkPinStates
}



void background() {
  int skip = 0; //if game has started, 
  for (int i=0; i<500; i=i+1){
      pd.pinState()->update();
      if (pd.pinState()->any()) {skip =1;}
      if (!skip) {delay(10);}
  }  
  if (!skip) {pd.adrLED1()->spreadInFromPoint2Color(R_START,"yellow", "red", 1000);}
  if (pd.pinState()->any()) {skip =1;}
  for (int i=0; i<200; i=i+1){
      pd.pinState()->update();
      if (pd.pinState()->any()) {skip =1;}
      if (!skip) {delay(10);}
  }  
  if (!skip) {pd.adrLED1()->chase2Color("yellow", "red",2*N_LEDS, 0, 1);}
  if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->spreadInFromPoint2Color(R_START,"red", "yellow", 1000);}
  if (pd.pinState()->any()) {skip =1;}
  for (int i=0; i<200; i=i+1){
      pd.pinState()->update();
      if (pd.pinState()->any()) {skip =1;}
      if (!skip) {delay(10);}
  }  
  if (!skip) {pd.adrLED1()->chase2Color("red", "yellow",2*N_LEDS, 0, -1);}
  if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->chase2Color("red", "yellow",N_LEDS/8, 25, 1);}
  if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->chase2Color("yellow", "red",N_LEDS/8, 25, -1);}
  if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->chase2Color("red", "yellow",N_LEDS/8, 20, 1);}
  if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->chase2Color("yellow", "red",N_LEDS/8, 20, -1);}
  if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->chase2Color("red", "yellow",N_LEDS/8, 15, 1);}
  if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->chase2Color("yellow", "red",N_LEDS/8, 15, -1);}
  if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->chase2Color("red", "yellow",N_LEDS/8, 10, 1);}
  if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->chase2Color("yellow", "red",N_LEDS/8, 10, -1);}
  if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->chase2Color("red", "yellow",N_LEDS/8, 7, 1);}
  if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->chase2Color("yellow", "red",N_LEDS/8, 7, -1);}
  if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->chase2Color("red", "yellow",N_LEDS/8, 5, 1);}
  if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->chase2Color("yellow", "red",N_LEDS/8, 5, -1);}
}


