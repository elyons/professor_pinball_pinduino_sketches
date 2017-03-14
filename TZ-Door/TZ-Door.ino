//Eric Lyons 2016
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3
//Uses pinduino library

#include <pinduino.h>

int aLEDNum1 = 17; // ramp
int aLEDNum2 = 0; // gumball
int aLEDNum3 = 0;
int N_LEDS=aLEDNum1;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");

int bg_chase_on = 0;
unsigned long timeLastEvent = 0; // time last event was last triggered
long startChaseWaitTime = 120000; //Amount of time to wait before chase lights start up again 1000 == 1 second
int whiteWaitTime = 500; //Amount of time to wait before gumball goes to white

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
}

void loop(){
  for (int i = 0; i < 1000; i = i + 1) { //check pinstates for a while
    pd.pinState()->update();
  }
  
//   Print the pin states out to serial 
//  pd.pinState()->print();
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) {bg_chase_on=1;}
  if (millis()-timeLastEvent > whiteWaitTime) {
      pd.adrLED1()->color("white",255);}
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
  pd.adrLED1()->fadeOut(500);
  int skip = 0; //if game has started, 
  if (!skip) {pd.adrLED1()->fadeIn("blue", 1000);}
  if (pd.pinState()->any()) {skip =1;}
  delay(500);
  if (!skip) {pd.adrLED1()->fadeColor2Color("blue", "red", 1000);}
  delay(500);
  if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->fadeOut(1000);}
  if (pd.pinState()->any()) {skip =1;}
  for (int i=15; i >1; i=i-1){
    if (!skip) {pd.adrLED1()->chase("red", 15, i, 1);}
    if (!skip) {pd.adrLED1()->chase("red", 15, i, -1);}
    if (pd.pinState()->any()) {skip =1;}
  }
  for (int i=10; i >0; i=i-1){
    if (!skip) {pd.adrLED1()->chase2Color("blue", "red",15, 1, 1);}
    if (!skip) {pd.adrLED1()->chase2Color("red", "blue",15, 1, -1);}
    if (pd.pinState()->any()) {skip =1;}
  }
  if (!skip) {pd.adrLED1()->fadeOut(100);}  
  for (int i=10; i >0; i=i-1){
    if (!skip) {pd.adrLED1()->color("blue", 255);}
    delay(100);
    pd.adrLED1()->clear();
    delay(20*i);
    if (pd.pinState()->any()) {skip =1;}
  }
  delay (500);
  for (int i=10; i >0; i=i-1){
    if (!skip) {pd.adrLED1()->color("red", 255);}
    delay(100);
    pd.adrLED1()->clear();
    delay(50*i);
    if (pd.pinState()->any()) {skip =1;}
  }
  delay (500);
  for (int i=5; i >0; i=i-1){
    if (!skip) {pd.adrLED1()->color("blue", 255);}
    delay(100);
    pd.adrLED1()->clear();
    delay(70*i);
    if (pd.pinState()->any()) {skip =1;}
  }
  if (!skip) {pd.adrLED1()->fadeIn("white", 1000);}
  for (int i = 0; i < 5000; i = i + 1) { //check pinstates for a while
    pd.pinState()->update();
  }

}


