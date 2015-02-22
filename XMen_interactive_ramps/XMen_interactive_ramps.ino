//Eric Lyons 2015
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.2
//Uses pinduino library

#include <pinduino.h>
int N_LEDS = 151;
int R_START = 82;

int aLEDNum1 = N_LEDS;
int aLEDNum2 = 0;
int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3);

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
int startChaseWaitTime = 15000; //Amount of time to wait before chase lights start up again 1000 == 1 second

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
  }
  if ( pd.pinState()->J6(2) ){ 
  }
  if ( pd.pinState()->J6(3) ){ 
    pd.adrLED1()->chase2RGB(0,0,255, 255,255,255,N_LEDS/6, 0, -1);
    trigger =1;
  }
  if ( pd.pinState()->J6(4) ){ 
    pd.adrLED1()->spreadInFromPointRGB(R_START,100, 100, 255, 0);
    pd.adrLED1()->fadeOut(100);
    trigger =1;
  }
  if ( pd.pinState()->J6(5) ){
    pd.adrLED1()->spreadInFromPointRGB(R_START,255, 100, 0, 0);
    pd.adrLED1()->fadeOut(100);
    trigger =1;
  }
  if ( pd.pinState()->J6(6)  and bg_chase_on==0 ){
    pd.adrLED1()->color("red",255);
    pd.adrLED1()->spreadOutFromPoint (R_START, 0);
    trigger =1;
  }
  if ( pd.pinState()->J6(7) ){
    pd.adrLED1()->color("yellow", 255);
    delay(20);
    pd.adrLED1()->clear();
    trigger =1;
  }
  if ( pd.pinState()->J6(8) ){ 
    pd.adrLED1()->color("red", 255);
    delay(20);
    trigger =1;
  }
  if ( pd.pinState()->J7(6) ){ 
      trigger =1;
  }
  if ( pd.pinState()->J7(2) ){
      pd.adrLED1()->chase2Color("blue", "yellow", N_LEDS/8, 0, -1);
      trigger=1;
  }
  if ( pd.pinState()->J7(3) ){ 
      pd.adrLED1()->chase2Color("red", "blue",N_LEDS/8, 0, 1);
      trigger =1;
  }
  if ( pd.pinState()->J7(4) ){
      pd.adrLED1()->chase2Color("yellow", "blue",N_LEDS/4, 0, 1);
      trigger =1;
  }
  if ( pd.pinState()->J7(7) ){
  }
  if ( pd.pinState()->J7(8) ){
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
   pd.adrLED1()->clear();
   pd.pinState()->reset();
   trigger =0;
   bg_chase_on = 0;
   timeLastEvent = millis();
  }

//end function checkPinStates
}



void backgroundChase() {
  pd.adrLED1()->spreadInFromPoint2Color(R_START,"sky", "blue", 10);
  pd.adrLED1()->fadeOut(100);
  delay(10);
  pd.adrLED1()->color("blue",150);
  pd.adrLED1()->fadeOut(50);
  delay(100);
  pd.adrLED1()->color("blue",100);
  pd.adrLED1()->fadeOut(50);
  delay(200);
  pd.adrLED1()->color("blue",50);
  pd.adrLED1()->fadeOut(200);
  for (int i=0; i<100; i=i+1){
      pd.pinState()->update();
      delay(10);
  }  
}


