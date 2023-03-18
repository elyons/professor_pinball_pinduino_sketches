//Elyan MATTALIANO 2020
//A BIG thanks to Eric LYONS !
//Note to self: Play more pinball!
//Interfaced for pinduino shield v0.3
//Uses pinduino library

#include <pinduino.h>
int N_LEDS = 32;
int O_LEDS = 147;
int R_START = 16;
int O_START = 73;

int aLEDNum1 = N_LEDS;
int aLEDNum2 = O_LEDS;

String color1 = "blue";
String color2 = "blue";

int bgWhiteTime = 1500;
pinduino pd (aLEDNum1, aLEDNum2, "Nano");

int attractModeOn = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
int startAttractMode = 30000; //Amount of time to wait before chase lights start up again 1000 == 1 second

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.pinState()->reset(); }  

void loop(){
  if (attractModeOn){attractMode();}
  pd.pinState()->update();
  checkPinStates();
  if (millis()-timeLastEvent > startAttractMode) {attractModeOn=1;} }

void checkPinStates(){
  int trigger =0;

//J111 

  pd.adrLED1()->color("red");
  
  if ( pd.pinState()->J126(1) ) { // J111 INLANE FLASHERS 
  pd.adrLED1()->fadeOut(50);
  pd.adrLED1()->fadeIn("blue",50);
  pd.adrLED1()->color("blue"); 
  pd.adrLED2()->explosion(1, "blue", 147);
  pd.adrLED1()->fadeOut(50);
  trigger =1; }
  
  if ( pd.pinState()->J126(2) ) { // J111 FINAL BATTLE FLASHER   
  pd.adrLED2()->explosion(1, "red", 147);
  trigger =1; }
  
  if ( pd.pinState()->J126(3) ) { // J111 LEFT LOOP FLASHER
  pd.adrLED2()->color("red");
  trigger =1; }  
  
  if ( pd.pinState()->J126(4) ) { // J111 BAZAAR FLASHER  
  pd.adrLED1()->fadeOut(50);
  pd.adrLED1()->fadeIn("purple",50);
  pd.adrLED1()->color("purple"); 
  trigger =1; }
  
  if ( pd.pinState()->J126(5) ) { // J111 RAMP DIVERTER   
  pd.adrLED1()->fadeIn("blue",50);
  pd.adrLED2()->spreadInFromPoint2Color (O_START, "orange", "purple", 100);
  pd.adrLED2()->spreadOutFromPoint(147, 100);
  pd.adrLED1()->fadeOut(50);
  trigger=1; }
  
  if ( pd.pinState()->J126(6)) { // J111 RUB LAMP FLASHER  
  pd.adrLED1()->fadeIn("blue",50);
  pd.adrLED2()->multiBullet("blue", 10, 0, 1, 1);
  pd.adrLED1()->fadeOut(50);
  trigger =1; }
  
  if ( pd.pinState()->J126(7) ) // J111 LAMP FLASHER SOUS LAMPE
  if (millis() - timeLastEvent > 1000 ){
  pd.adrLED1()->fadeIn("blue",10);
  pd.adrLED1()->color("blue");  
  pd.adrLED2()->chase("blue",10,0,1);  // LED1 string defaults to blue color when nothing happening
  trigger =1; }  
  
  if ( pd.pinState()->J126(8) ) { // J111 RIGHT LOOP FLASHER
  pd.adrLED2()->spreadInFromPoint2Color (O_START, "purple", "blue", 100);
  pd.adrLED2()->spreadOutFromPoint(147, 100);
  trigger =1; }
  
//J108
  
  if ( pd.pinState()->J126(13) ) { //extended WPC with extra 4-pin plug  J108 START TALE FLASHERS   
  pd.adrLED2()->fire(10, 50);
  trigger=1; }
    
  if ( pd.pinState()->J126(14) ) { //extended WPC with extra 4-pin plug  J108 JET FLASHERS 
  trigger=1; }
   
  if ( pd.pinState()->J126(15) ) { //extended WPC with extra 4-pin plug  J108 TOP LOOP FLASHER
  pd.adrLED1()->color("blue");
  pd.adrLED2()->color("red");
  trigger =1; }
  
  if ( pd.pinState()->J126(16) ) { //extended WPC with extra 4-pin plug  J108 RAMP FLASHER 
  pd.chaseAllAdr2RGBFromPoint(1, 0,0,255, 255,0,0, 10, 0);
  trigger=1; }
  
//trigger is to take care of any cleanup after a sequence has been triggered.  
  if (trigger) {
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.pinState()->reset();
  trigger = 0;
  attractModeOn = 0;
  timeLastEvent = millis(); }
  
  } //end function checkPinStates
  
void attractMode(){
  if (int(random(250)) == 0) {
    if (color1 == "blue") {color1="red";}
    else color1="blue";
  }
  if (int (random(250)) == 0) {
    if (color2 == "blue") {color2="purple";}
    else color2="blue";
  }
  pd.adrLED2()->sparkle(color2, 15);
  pd.adrLED2()->sparkle(color1, 15);

  //pd.adrLED2()->sparkle("blue", 25, 0);
  for (int i=0; i<50; i=i+1){
  checkPinStates();} }
