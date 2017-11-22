//Eric Lyons 2015
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3
//Uses pinduino library

/// ---=====  NOTE ====---
/// The LED string I used had the red and green channels switched.  
/// No idea why
/// So: adrLED1
/// Green -> red
/// Red -> green
/// Purple -> cyan
/// Cyan -> purple


#include <pinduino.h>
int N_LEDS = 30;
int aLEDNum1 = 50;
int aLEDNum2 = 30;
int aLEDNum3 = 1;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");

int bg_chase_on = 1;
int disc_motor = 0; // flag for sensing disc motor
int disc_motor_wait = 10000;//time to wait with no disc motor activity to reset disc_motor_flag
int zuse = 0; // flag for sensing zuse
int zuse_wait = 500;//time to wait with no zuse activity to reset zuse flag
unsigned long timeLastEvent = 0; // time last event was last triggered
unsigned long discEvent = 0; // time since disc lights last went
int startChaseWaitTime = 10000; //Amount of time to wait before chase lights start up again 1000 == 1 second
int bgWhiteTime = 50;
int bgTime = 10000; // time till lights are set to background color
String bgColor = "blue";


void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
}

void loop(){
  if (bg_chase_on){backgroundChase();}
  for (int i=0; i<1000; i=i+1) {     
    pd.pinState()->update();
  }
//   Print the pin states out to serial 
//  pd.pinState()->print();
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) {bg_chase_on=1;}
  if (!pd.pinState()->J6(7) && !pd.pinState()->J6(8) && millis()-discEvent > bgTime) {bgColor="blue";}

  if (millis()-timeLastEvent > bgWhiteTime && !bg_chase_on) {
    pd.adrLED1()->color("white", 255);
    pd.adrLED2()->color("white", 255);
  }
  if (!pd.pinState()->J6(6) && millis()-timeLastEvent > disc_motor_wait) { disc_motor=0;}
  if ( millis()-timeLastEvent > zuse_wait) { zuse=0;}
  if ( millis()-timeLastEvent > 2000){pd.pinState()->reset();} // reset pin states if nothing has been triggered for 2 seconds

}

void checkPinStates(){
  int trigger =0;
  
  if ( pd.pinState()->J6(2) )
    { // flashes if quora his hit and nothing else
      // let monitor for a bit longer to see if something else goes 
      // used to sense disc
      for (int i=0; i<1000; i=i+1) {     
        pd.pinState()->update();
      }
    }
 
   if (pd.pinState()->J7(3) ) { // Video Game
    pd.adrLED1()->color("cyan", 255);
    pd.adrLED2()->color("blue", 255);
    delay(200);
    pd.fadeOutAllAdr(100);
    trigger = 1;
  }
  
  if ( pd.pinState()->J6(1)  && pd.pinState()->J7(8) ) { // light cycle
    pd.adrLED2()->clear();
    pd.adrLED1()->bullet2Color("yellow", "yellow", 50, 0, 1);
//    pd.adrLED1()->chase2Color("blue", "bue", 50, 1, -1);
    trigger =1;    
  }
  if (  pd.pinState()->J7(4)  && pd.pinState()->J7(9) ) { // light cycle
    pd.adrLED2()->clear();
//    pd.adrLED1()->chase2Color("yellow", "yellow", 50, 1, 1);
    pd.adrLED1()->bullet2Color("blue", "bue", 50, 0, -1);
    trigger =1;    
  }
  
  if ( !zuse && pd.pinState()->J6(4) && ! pd.pinState()->J7(4) ) { // zuse
    pd.adrLED1()->clear();
    pd.adrLED2()->clear();
    delay(30);
    for (int i=0; i<3; i=i+1) {
      pd.adrLED1()->color("blue", 255);
      pd.adrLED2()->color("white", 255);
      delay(30);
      pd.adrLED1()->clear();
      pd.adrLED2()->clear();
      delay(30);
    }  
    trigger =1;
    zuse = 1;
   }
   
   if ( pd.pinState()->J6(2) && !pd.pinState()->J6(3) && ! pd.pinState()->J6(5)){//quora
    pd.adrLED2()->color("blue", 255);
    pd.adrLED1()->fadeColor2Color("red", "green",50);
    pd.fadeOutAllAdr(500);
    trigger = 1; 
  }
   if (pd.pinState()->J6(2) && pd.pinState()->J6(3) ) {// disc open and hit
     for (int i=0; i<3; i=i+1) {
       pd.fadeAllAdrColor2Color("blue", "yellow",50);
       pd.fadeAllAdrColor2Color("yellow", "blue",50);
     }
    trigger = 1;
  } 
  
  if ( pd.pinState()->J6(5) ){ // recognizer
    pd.adrLED2()->clear();
    pd.adrLED1()->spreadInFromPoint2Color(20, "green","green", 300);
    pd.adrLED2()->color("red", 255);
    delay(500);
    trigger = 1; 
  }
  if ( pd.pinState()->J6(6) && !disc_motor){ // Disc motor
    //want this to run when the disc starts up
    pd.adrLED1()->clear();
    pd.adrLED2()->clear();
    pd.adrLED1()->chase2Color("green", "green", 10, 10, 1);
    pd.adrLED1()->chase2Color("blue", "white", 10, 10, -1);
    pd.adrLED2()->fadeIn("red", 200);
    pd.adrLED1()->fadeIn("blue", 200);
    pd.adrLED1()->fadeColor2Color("blue","green", 500);
    delay(1000);
    disc_motor=1;
    trigger = 1; 
  }

  if ( pd.pinState()->J6(7) ){ //RED disc left (flashers under disc)
    bgColor="orange";
    discEvent = millis();   
  }
  
  if ( pd.pinState()->J6(8) ){ //RED disc right (flashers under disc)
    bgColor="red";
    discEvent = millis();   
  }
  
//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   pd.pinState()->reset();
   trigger = 0;
   bg_chase_on = 0;
   timeLastEvent = millis();
  }
}



void backgroundChase() {
  if (bgColor == "red" || bgColor == "orange") {pd.adrLED1()->sparkle("green",20,5);}
  else {pd.adrLED1()->sparkle(bgColor,20,5);}
  pd.adrLED2()->sparkle(bgColor,20,5);
}

