//Paul (ApplePie) 2017
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3
//Uses pinduino library

/* Paul's notes for SMVE Pinduino application
 * 1) LED1 powers three 2812B 30 LED/M strips in parallel.  One with 14 LED's behind the backbox facing the wall and two more under the cabinet with 35 LED's each
 * 2) LED is in the ball trough area with 9 LED's from a 60LED/M strip
 */

#include <pinduino.h>
int R_START = 25;  // midpoint of the undercabinet led strip, used in the fadeinfrompoint command

int aLEDNum1 = 50;  // backpanel led count is 15 and undercabinet led count is 35 each on two parallel strings.  Backpanel and undercabinet lights are on same string so go with the higher led count number here
int aLEDNum2 = 0;  // trough led count is 9.  Trough led's are on their own string so there is more flexibility to color them white to provide more while light on the playfield between the flippers
int aLEDNum3 = 0;

int LED1FlashDelay = 50;  // variable to input flash delays for LED1 (does not affect BGChase function)

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");

int bg_chase_on = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 30000; //Amount of time to wait before chase lights start up again 1000 == 1 second
int bgWhiteTime = 500; //Amount of time to wait before gumball goes to white

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
}

void loop(){
  if (bg_chase_on){backgroundChase();}
//   Print the pin states out to serial 
  pd.pinState()->print();
  pd.pinState()->update();
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) {bg_chase_on=1;}
//  if (millis()-timeLastEvent > bgWhiteTime && !bg_chase_on) {
//    pd.adrLED1()->color("white", 255);
 // }

}

void checkPinStates(){
  int trigger =0;
  
  if ( pd.pinState()->J6(1) ) // left:spinner
  {
     pd.adrLED1()->color("green", 255);
     delay(LED1FlashDelay);
     pd.adrLED1()->clear();
     delay(LED1FlashDelay);
     trigger =1;
  }
  
  if ( pd.pinState()->J6(2) ) // back panel 1
  { 
     pd.adrLED1()->color("yellow", 255);
     delay(LED1FlashDelay);
     pd.adrLED1()->clear();
     delay(LED1FlashDelay);
     trigger =1; 
  }
  
  if ( pd.pinState()->J6(3) )// back panel 2
  { 
     pd.adrLED1()->color("blue", 255);
     delay(LED1FlashDelay);
     pd.adrLED1()->clear();
     delay(LED1FlashDelay);
     trigger =1; 
  }
  
  if ( pd.pinState()->J6(4) ) // back panel 3
  {
     pd.adrLED1()->color("green", 255);
     delay(LED1FlashDelay);
     pd.adrLED1()->clear();
     delay(LED1FlashDelay);
     trigger =1; 
  }
  
  if ( pd.pinState()->J6(5) ) // back panel 4
  { 
     pd.adrLED1()->color("red", 255);
     delay(LED1FlashDelay);
     pd.adrLED1()->clear();
     delay(LED1FlashDelay);
     trigger =1; 
 
   }
   
  if ( pd.pinState()->J6(6)) // back panel 5
  {
     pd.adrLED1()->color("purple", 255);
     delay(LED1FlashDelay);
     pd.adrLED1()->clear();
     delay(LED1FlashDelay);
     trigger =1;
  }
  
  if ( pd.pinState()->J6(7) ) // right VUK
  {
     pd.adrLED1()->color("red", 255);
     delay(LED1FlashDelay);
     pd.adrLED1()->clear();
     delay(LED1FlashDelay);
     trigger =1;
  }
  
  if ( pd.pinState()->J6(8) )
  { 

  }

///J7

  if ( pd.pinState()->J7(3) )
  {
  }
  if ( pd.pinState()->J7(4) ) // jail latch
  { 
     pd.adrLED1()->color("blue", 255);
     delay(LED1FlashDelay);
     pd.adrLED1()->clear();
     delay(LED1FlashDelay);
     trigger =1;
  }
  
  if ( pd.pinState()->J7(6) )
  {
  }
  
  if ( pd.pinState()->J7(7) )
  {
  }
  
  if ( pd.pinState()->J7(8) ) // left sling
  {
     pd.adrLED1()->color("green", 255);
     delay(LED1FlashDelay);
     pd.adrLED1()->clear();
     delay(LED1FlashDelay);
     trigger =1;
  }

  if ( pd.pinState()->J7(9) ){ // right sling
     pd.adrLED1()->color("green", 255);
     delay(LED1FlashDelay);
     pd.adrLED1()->clear();
     delay(LED1FlashDelay);
     trigger =1;
  }

  if ( pd.pinState()->J7(10) )
  {
  }

//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) 
  {
   pd.adrLED1()->clear();
   pd.adrLED2()->clear();
   pd.pinState()->reset();
   trigger =0;
   bg_chase_on = 0;
   timeLastEvent = millis();
  }
  if (millis() - timeLastEvent > 500) {
    pd.adrLED1()->color("white", 200);  // LED1 string defaults to blue color when nothing happening
  }

//end function checkPinStates
}



void backgroundChase() {
  int skip = 0; //if game has started, 
  pd.adrLED1()->clear();
  pd.adrLED2()->color("white", 255);  //keep trough white
  pd.adrLED1()->spreadInFromPoint(R_START,"red",500);  // testing undercabinet lighting effects here.  Most noticeable on long LED strips
  for (int i=0; i<50; i=i+1){
      pd.pinState()->update();
      if (pd.pinState()->any()) {skip =1;}
      if (!skip) {delay(10);}
  }  
  if (!skip) {pd.adrLED1()->fadeOut(200);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {delay(50);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->color("red",255);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->fadeOut(200);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {delay(50);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->color("red",255);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->fadeOut(200);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {delay(50);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->color("red",255);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->fadeOut(200);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {delay(50);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->color("red",255);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->fadeOut(200);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {delay(50);}
    pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->color("red",255);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->fadeOut(200);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {delay(50);}
    pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->color("red",255);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->fadeOut(200);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {delay(50);}
    pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->color("red",255);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->fadeOut(200);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {delay(50);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->color("red",255);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->fadeOut(300);}
  for (int i=0; i<100; i=i+1){
      pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
      if (!skip) {delay(10);}
  }  
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
}


