//Eric Lyons 2015
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3
//Uses pinduino library

#include <pinduino.h>
int N_LEDS = 109;
int R_START = 67;

int aLEDNum1 = N_LEDS;
int aLEDNum2 = 0;
int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");

// pin 0:  Flash: Pop Bumper Fl. (BLK-BRN)
// pin 1:  Orbit Diverter (BLK-RED)
// pin 2:  Iceman Motor (BLK-ORG)
// pin 3:  Flash: Backpanel Left (x3) (BLK-YEL)
// pin 4:  Flash: Backpanel Left (x3) (BLK-GRN)
// pin 5:  Flash: Magneto Spot Light (BLK-BLU)
// pin 6:  Flash: Bottom Arch x2 (BLK-VIO)
// pin 7:  Flash: Magneto Figure (BLK-GRY)
// pin 8:  Flash: Disc Blue x2 (VIO-WHT)
// pin 9:  Flash: Disc Red x2 (VIO-ORG)
// pin 10: Flash: Right side (VIO-RED)
// pin 11: Flash: Left side (x2) (VIO-BRN)
// pin 12: Coil Optional (VIO-GRY)
// pin 13: Disc Motor Power (VIO-BLK)
// pin 14: Flash: Magneto Left/right x2 (VIO-BLU)
// pin 15: Flash: Wolverine (VIO-GRN)

int bg_chase_on = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 60000; //Amount of time to wait before chase lights start up again 1000 == 1 second
int bgWaitTime = 300; //Amount of time to wait before backglass turns on
int bgOn=1;
String color = "white"; //attract color
int magneto_count = 0;

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
//  Serial.println (millis()-timeLastEvent);
  checkPinStates();
  if (millis()-timeLastEvent > bgWaitTime && bgOn == 0) {
    bgOn =1;
  }
  if (millis()-timeLastEvent > startChaseWaitTime) {bg_chase_on=1;}
}

void checkPinStates(){
  int trigger =0;
  
  if ( pd.pinState()->J6(1) ){
    pd.adrLED1()->fadeOut(10);
    pd.adrLED1()->bullet2Color("red", "yellow", 3, 0, -1);
    pd.adrLED1()->bullet2Color("yellow", "red", 3, 0, 1);
//    pd.adrLED1()->chase2RGB(0,0,255, 255,255,255,N_LEDS/6, 0, 1);
    trigger =1;
  }
  if ( pd.pinState()->J6(2) ){ 
  }
  if ( pd.pinState()->J6(3) ){
    pd.adrLED1()->fadeOut(10); 
    pd.adrLED1()->chase2RGB(R_START, 0,0,255, 255,255,255, 0, -1);
    delay(200);
    pd.adrLED1()->fadeOut(100);
    trigger =1;
  }
  if ( pd.pinState()->J6(4) ){
//    pd.adrLED1()->fadeOut(10); 
//    pd.adrLED1()->spreadInFromPointRGB(R_START,100, 100, 255, 0);
//    pd.adrLED1()->fadeOut(100);
//    trigger =1;
  }
  if ( pd.pinState()->J6(5) ){
//    pd.adrLED1()->fadeOut(10);
//    pd.adrLED1()->spreadInFromPointRGB(R_START,255, 100, 0, 0);
//    pd.adrLED1()->fadeOut(100);
//    trigger =1;
  }
  if ( pd.pinState()->J6(6)  and bg_chase_on==0 ){
    if (magneto_count < 10) {
      pd.adrLED1()->fadeOut(10);
      pd.adrLED1()->bulletFromPoint2Color("red","blue", 20, 0, R_START);
//    pd.adrLED1()->color("red",255);
//      pd.adrLED1()->spreadInFromPoint (R_START, "red", 0);
//      pd.adrLED1()->spreadOutFromPoint (R_START, 0);
      trigger = 1;
      magneto_count = magneto_count +1;
    }  
  }
  if ( pd.pinState()->J6(7) ){
    pd.adrLED1()->fadeOut(10);
    pd.adrLED1()->color("yellow", 255);
    delay(100);
    pd.adrLED1()->clear();
    trigger =1;
  }
  if ( pd.pinState()->J6(8) ){
    pd.adrLED1()->fadeOut(10); 
    pd.adrLED1()->color("red", 255);
    delay(100);
    trigger =1;
  }
  if ( pd.pinState()->J7(2) ){
    pd.adrLED1()->fadeOut(10);
    pd.adrLED1()->bullet2Color("blue", "yellow", N_LEDS/10, 0, -1);
    trigger=1;
  }
  if ( pd.pinState()->J7(3) ){
    pd.adrLED1()->fadeOut(10); 
    pd.adrLED1()->bullet2Color("yellow", "blue",N_LEDS/10, 0, 1);
    trigger =1;
  }
  if ( pd.pinState()->J7(4) ){
    pd.adrLED1()->fadeOut(10);
    pd.adrLED1()->bulletFromPoint2RGB(255,0,0,0,100,0, 5, 0, R_START);
//    pd.adrLED1()->spreadInFromPoint2RGB (R_START, 255,0,0, 50,0,0, 0);
//    delay(100);
//    pd.adrLED1()->fadeOut(50);
    trigger =1;
  }
  if ( pd.pinState()->J7(6) ){
    pd.adrLED1()->fadeOut(10);
    pd.adrLED1()->bulletFromPoint2RGB(0,0,255,255,255,0, 5, 0, R_START);
//    pd.adrLED1()->spreadInFromPoint2RGB (R_START, 0,0,255, 0,0,50, 0);
//    delay(100);
//    pd.adrLED1()->fadeOut(50);
    trigger =1;
  }
  if ( pd.pinState()->J7(7) ){
    pd.adrLED1()->fadeOut(10);
    pd.adrLED1()->color("yellow");
    delay(100);
    pd.adrLED1()->fadeOut(50);
    trigger =1;
  }
  if ( pd.pinState()->J7(8) ){
    pd.adrLED1()->fadeOut(10);
    pd.adrLED1()->spreadInFromPoint2Color (R_START, "red", "blue", 0);
    pd.adrLED1()->fadeOut(100);
    trigger=1;
  }
  if ( pd.pinState()->J7(9) ){
  }
  if ( pd.pinState()->J7(10) ){
  }

//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
  if (pd.pinState()->J6(6) == 0) {
      magneto_count = 0;
      timeLastEvent = millis();
  }
   pd.adrLED1()->clear();
   pd.pinState()->reset();
   trigger = 0;
   bg_chase_on = 0;
   bgOn=0;
  }

//end function checkPinStates
}



void backgroundChase() {
  pd.adrLED1()->sparkle(color,20);
  if (random(1000) == 0) {
      if (color == "blue") color = "red";
      else if (color == "red") color = "yellow";
      else if (color == "white") color = "blue";
      else color = "white";
  }  
//  pd.adrLED1()->spreadInFromPoint2Color(R_START,"yellow", "blue", 10);
//  pd.adrLED1()->fadeOut(100);
//  delay(10);
//  pd.adrLED1()->color("blue");
//  pd.adrLED1()->fadeOut(50);
//  delay(100);
//  pd.adrLED1()->colorRGB(0,0,100);
//  pd.adrLED1()->fadeOut(50);
//  delay(200);
//  pd.adrLED1()->colorRGB(0,0,50);
//  pd.adrLED1()->fadeOut(200);
//  for (int i=0; i<100; i=i+1){
//      pd.pinState()->update();
//      delay(10);
//  }  
}


