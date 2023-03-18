//Paul (ApplePie) 2017
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3
//Uses pinduino library

/* Paul's notes for ACDC Premium Pinduino application
 * 1) LED1 powers two 2812B 35 30LED/M strips wired in parallel under the cabinet
 * 2) LED2 is in the topper with 60LED/m narrow strip and 39 LED's
 */

#include <pinduino.h>
int R_START = 18;  // midpoint of the undercabinet led strip, used in the fadeinfrompoint command

int aLEDNum1 = 35;  // led count is 35 each on two parallel strings.  
int aLEDNum2 = 39;  // LED 2 is in the topper
int aLEDNum3 = 0;

int LED1FlashDelay = 50;  // variable to input flash delays for LED1 (does not affect BGChase function)


pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");

int bg_chase_on = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 30000; //Amount of time to wait before chase lights start up again 1000 == 1 second

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
//  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop(){
  if (bg_chase_on)
  {backgroundChase();}
  
  pd.pinState()->update();
//   Print the pin states out to serial 
//  pd.pinState()->print();
  
  checkPinStates();
  
  if (millis()-timeLastEvent > startChaseWaitTime) 
  {bg_chase_on=1;}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void checkPinStates(){
  int trigger =0;
  
  if ( pd.pinState()->J6(1) )  // Pop bumpers
  {
     pd.adrLED1()->color("lavender", 255);
     delay(LED1FlashDelay);
     pd.adrLED1()->clear();
     delay(LED1FlashDelay);
     trigger =1;
  }
  
  if ( pd.pinState()->J6(2) )  // bell arrow flasher
  { 
     pd.adrLED1()->color("red", 255);
     delay(LED1FlashDelay);
     pd.adrLED1()->clear();
     delay(LED1FlashDelay);
     trigger =1; 
  }
  
  if ( pd.pinState()->J6(3) )  //  Left ramp left side flasher (lightning bolt)
  { 
     pd.adrLED1()->color("cyan", 255);
     delay(LED1FlashDelay);
     pd.adrLED1()->clear();
     delay(LED1FlashDelay);
     pd.adrLED2()->color("cyan", 255);  // get topper to change to new color and stay that way until next change
     trigger =1; 
  }
  
  if ( pd.pinState()->J6(4) )  //   Left ramp right side flasher (lightning bolt)
  {
     pd.adrLED1()->color("cyan", 255);
     delay(LED1FlashDelay);
     pd.adrLED1()->clear();
     delay(LED1FlashDelay);
     pd.adrLED2()->color("cyan", 255);  // get topper to change to new color and stay that way until next change
     trigger =1;
  }
  
  if ( pd.pinState()->J6(5) )  // Right ramp right side flasher (lightning bolt)
  { 
     pd.adrLED1()->color("cyan", 255);
     delay(LED1FlashDelay);
     pd.adrLED1()->clear();
     delay(LED1FlashDelay);
     pd.adrLED2()->color("cyan", 255);  // get topper to change to new color and stay that way until next change
     trigger =1;
 
   }
   
  if ( pd.pinState()->J6(6))  // Right ramp flasher (under ramp)
  {
     pd.adrLED1()->color("blue", 255);
     delay(LED1FlashDelay);
     pd.adrLED1()->clear();
     delay(LED1FlashDelay);
     trigger =1;
  }
  
  if ( pd.pinState()->J6(7) )    // right side flasher (cannon?)
  {
     pd.adrLED1()->color("red", 255);
     delay(LED1FlashDelay);
     pd.adrLED1()->clear();
     delay(LED1FlashDelay);
     trigger =1;
  }
  
  if ( pd.pinState()->J6(8) )    // cannon motor  
  { 
     pd.adrLED1()->color("red", 255);
     delay(LED1FlashDelay);
     pd.adrLED1()->clear();
     delay(LED1FlashDelay);
     pd.adrLED2()->color("red", 255);  // get topper to change to new color and stay that way until next change
     trigger =1;
  }

///J7

  if ( pd.pinState()->J7(2) )  // Train Flasher
  {
     pd.adrLED1()->color("blue", 255);
     delay(LED1FlashDelay);
     pd.adrLED1()->clear();
     delay(LED1FlashDelay);
     pd.adrLED2()->color("blue", 255);  // get topper to change to new color and stay that way until next change
     trigger =1;
  }
  
  if ( pd.pinState()->J7(3) )
  {
  }
  
  if ( pd.pinState()->J7(4) )
  { 
  }
   
  if ( pd.pinState()->J7(6) )  // left ramp flasher (under ramp)
  {
     pd.adrLED1()->color("red", 255);
     delay(LED1FlashDelay);
     pd.adrLED1()->clear();
     delay(LED1FlashDelay);
     trigger =1;
  }
  
  if ( pd.pinState()->J7(7) )  // left side flasher
  {
     pd.adrLED1()->color("blue", 255);
     delay(LED1FlashDelay);
     pd.adrLED1()->clear();
     delay(LED1FlashDelay);
     trigger =1;
  }
  
/*  if ( pd.pinState()->J7(8) )  // back panel flasher
  {
     pd.adrLED1()->color("orange", 255);
     delay(LED1FlashDelay);
     pd.adrLED1()->clear();
     delay(LED1FlashDelay);
     trigger =1;
  }
*/

  if ( pd.pinState()->J7(9) )  // top eject flasher
  {
     pd.adrLED1()->color("orange", 255);
     delay(LED1FlashDelay);
     pd.adrLED1()->clear();
     delay(LED1FlashDelay);
     pd.adrLED2()->color("yellow", 255);  // get topper to change to new color and stay that way until next change
     trigger =1;
  }

  if ( pd.pinState()->J7(10) )
  {
  }

//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) 
  {
   pd.adrLED1()->clear();
   //pd.adrLED2()->clear();
   pd.pinState()->reset();
   trigger =0;
   bg_chase_on = 0;
   timeLastEvent = millis();
  }
  if (millis() - timeLastEvent > 500) 
  {
    pd.adrLED1()->color("red", 200);  // LED1 string defaults to red color when nothing happening
  }

  /*if (millis() - timeLastEvent > 3000) 
  {
    pd.adrLED2()->color("red", 200);  // not currently using this code
  }
  */
//end function checkPinStates
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void backgroundChase() 
{
  int skip = 0; //if game has started, 
  
  pd.adrLED1()->clear();
  //pd.adrLED2()->clear();
  pd.adrLED1()->spreadInFromPoint(R_START,"red",500);  // testing undercabinet lighting effects here.  Most noticeable on long LED strips
  pd.adrLED2()->spreadInFromPoint(R_START,"red",500);
 
  for (int i=0; i<50; i=i+1)
  {
      pd.pinState()->update();
      if (pd.pinState()->any()) 
      {skip =1;}
      if (!skip) 
      {delay(10);}
  }  

  if (!skip){pd.adrLED1()->fadeOut(200);}
  pd.pinState()->update();
  if (pd.pinState()->any()){skip =1;} if (!skip){delay(50);}
  pd.pinState()->update();if (pd.pinState()->any()){skip =1;}
  if (!skip){pd.adrLED1()->spreadInFromPoint(R_START,"red",500);pd.adrLED2()->spreadInFromPoint(R_START,"red",500);}
  pd.pinState()->update();if (pd.pinState()->any()){skip =1;}
  if (!skip) {pd.adrLED1()->fadeOut(200);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {delay(100);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->spreadInFromPoint(R_START,"blue",500);pd.adrLED2()->spreadInFromPoint(R_START,"blue",500);}  
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->fadeOut(200);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {delay(100);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->spreadInFromPoint(R_START,"yellow",500);pd.adrLED2()->spreadInFromPoint(R_START,"yellow",500);}  
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->fadeOut(200);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {delay(100);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->spreadInFromPoint(R_START,"red",500);pd.adrLED2()->spreadInFromPoint(R_START,"red",500);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->fadeOut(200);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {delay(100);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->spreadInFromPoint(R_START,"blue",500);pd.adrLED2()->spreadInFromPoint(R_START,"blue",500);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->fadeOut(200);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {delay(100);}
    pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
    if (!skip) {pd.adrLED1()->spreadInFromPoint(R_START,"yellow",500);pd.adrLED2()->spreadInFromPoint(R_START,"yellow",500);}  
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->fadeOut(200);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {delay(100);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->spreadInFromPoint(R_START,"red",500);pd.adrLED2()->spreadInFromPoint(R_START,"red",500);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->fadeOut(200);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {delay(100);}
    pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->spreadInFromPoint(R_START,"blue",500);pd.adrLED2()->spreadInFromPoint(R_START,"blue",500);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->fadeOut(200);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {delay(100);}
    pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
    if (!skip) {pd.adrLED1()->spreadInFromPoint(R_START,"yellow",500);pd.adrLED2()->spreadInFromPoint(R_START,"yellow",500);}  
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->fadeOut(200);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {delay(100);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->spreadInFromPoint(R_START,"red",500);pd.adrLED2()->spreadInFromPoint(R_START,"red",500);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->fadeOut(200);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {delay(100);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->spreadInFromPoint(R_START,"blue",500);pd.adrLED2()->spreadInFromPoint(R_START,"blue",500);}
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
  if (!skip) {pd.adrLED1()->fadeOut(300);}
  
  for (int i=0; i<100; i=i+1)
  {
    pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
    if (!skip) {delay(10);}
  }  
  
  pd.pinState()->update(); if (pd.pinState()->any()) {skip =1;}
 
}


