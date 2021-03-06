//Eric Lyons and John Weir 2020
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.2 and v0.3
//Uses pinduino library

/// ---=====  NOTE ====---
/// This program modifies the previous walking dead code to track the lighting of heads in the fishtake topper


#include <pinduino.h>
int aLEDNum1 = 12; //apron
int aLEDNum2 =38; //ramps
int aLEDNum3 = 0;


int counter=1;// fish ramp counter left head
int counter2=1;// fish ramp counter middle head
pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");

int bg_on = 1; //attract effect
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 20000; //Amount of time to wait before chase lights start up again 1000 == 1 second
int bgWhiteTime = 50;
String color=("yellow") ;

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
}

void loop(){
  if (bg_on){attract_mode();}

 //Print the pin states out to serial 
//  pd.pinState()->print();
  pd.pinState()->update();
  
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) {bg_on=1;}
  if (millis()-timeLastEvent > bgWhiteTime && !bg_on) {
    pd.adrLED1()->fire(20,10);
    pd.adrLED2()->fire(20,10); 
  }
}

void checkPinStates(){
  int trigger = 0;

  if ( pd.pinState()->J6(1)){ // pop flashers
    pd.adrLED1()->color("yellow");
    pd.adrLED2()->color("yellow");
    delay(100);
   trigger = 1; 
  }

  if ( pd.pinState()->J6(2) ){ //Prison (TOP)
    pd.adrLED1()->fadeColor2Color("red","yellow",750);
    pd.adrLED2()->fadeColor2Color("red","yellow",750);
         delay(100);
    trigger = 1; 
  }

  if ( pd.pinState()->J6(3) ){ // Prison Bottom x2
   pd.adrLED1()->color("red");
   pd.adrLED2()->color("red");
   delay(100);
   trigger=1;
  }

  if ( pd.pinState()->J6(4) ){ // Left Dome
    pd.adrLED1()->color("white");
    pd.adrLED2()->color("blue");
    delay(100);
   trigger=1;
  }

  if ( pd.pinState()->J6(5) ){ // Right Dome
    pd.adrLED1()->color("white");
    pd.adrLED2()->color("green");
    delay(100);
    trigger=1;
  }

  if ( pd.pinState()->J6(7) ){ // Left Loop
    pd.adrLED1()->color("yellow");
    pd.adrLED2()->bullet2Color("white", "red", 20, 2, -1);
    delay(100);
    trigger=1;
  }
  

  if ( pd.pinState()->J6(8) ){ // Center Loop
    pd.adrLED1()->colorRGB(255,255,30); 
    pd.adrLED2()->bullet2Color("white", "orange", 20, 2, -1); 
    delay(100);
    trigger=1;
  }
     
  if (pd.pinState()->J7(2)== 0 ){counter = 0;}//when flasher turns off reset counter for next time it  turns on
  if ( pd.pinState()->J7(2)   &&  counter  == 0){  //left head
    pd.adrLED1()->color("yellow");
    pd.adrLED2()->bullet2Color("yellow", "red", 20, 2, -1);
    pd.adrLED2()->bullet2Color("red", "yellow", 20, 2, 1);
    delay(100);
    trigger=1;
    counter=1;
    pd.adrLED1()->clear();
    pd.adrLED2()->clear();
   }

  if (pd.pinState()->J7(3)== 0 ){counter2 = 0;} //when flasher turns off reset counter for next time it  turns on 
  if ( pd.pinState()->J7(3)   &&  counter2  == 0){    //middle head
    pd.adrLED1()->color("red");
    pd.adrLED2()->bullet2Color("red", "yellow", 20, 2, -1);
    pd.adrLED2()->bullet2Color("yellow", "red", 20, 2, 1); 
    delay(100);
    trigger=1;
    counter2 = 1;
    pd.adrLED1()->clear();
    pd.adrLED2()->clear();
  }

  if ( pd.pinState()->J7(8)  ){  //right head
    pd.adrLED1()->color("green");
    pd.adrLED2()->bullet2Color("green", "yellow", 20, 2, -1);
    pd.adrLED2()->bullet2Color("yellow", "green", 20, 2, 1);
    delay(100);
     trigger=1;
  }
  
  if ( pd.pinState()->J7(4) ){ // Well Walker
    pd.adrLED1()->color("yellow");
    pd.adrLED2()->spreadInFromPoint2Color(19,"orange","red",100) ;
    delay(100);
    trigger=1;
  }

  if ( pd.pinState()->J7(5) ){ // Right Spinner
    pd.adrLED1()->color("white");
    pd.adrLED2()->color("white");
    delay(100);
    trigger=1;
  }

  if ( pd.pinState()->J7(7) ){ // Crossbow motor
    pd.adrLED1()->fire(20,10);
    pd.adrLED2()->fadeOut(50);
    pd.adrLED2()->bullet2Color("white", "yellow", 20, 2, -1); 
    trigger=1;
    delay(100);
  }

//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
    pd.pinState()->reset();
    trigger = 0;
    bg_on = 0;
    timeLastEvent = millis();  
  }

//end function checkPinStates
}

void attract_mode() {
  pd.adrLED1()->sparkle(color,20);
  pd.adrLED2()->sparkle(color,20);
  if (random(1000) == 0) {
    if (color == "yellow") color = "red";
    else color = "yellow";
   }  
}
