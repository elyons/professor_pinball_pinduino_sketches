//Eric Lyons 2022
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3
//Uses pinduino library

/* Notes and other updates
 */

#include <pinduino.h>

int aLEDNum1 = 27;  //Number of LEDs for a strip with 60 LEDs permeter 
int aLEDNum2 = 0;  // 
int LEDMid = 13; // Midpoint in LED string


pinduino pd (aLEDNum1, aLEDNum2, "Nano");

int attractModeOn = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
int startAttractMode = 40000; //Amount of time to wait before chase lights start up again 1000 == 1 second
int bgWhiteTime = 50; // delay before setting LEDs to white when game is in play
int flashDelay = 300;
String color1 = "blue"; // for attract mode
String color2 = "cyan"; // for attract mode

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
}

void loop(){
//   Print the pin states out to serial 
//  pd.pinState()->print();
  if (attractModeOn){attractMode();}
  pd.pinState()->update();
  checkPinStates();
  if (millis()-timeLastEvent > startAttractMode) {attractModeOn=1;} // Turn on attract mode
  if (millis()-timeLastEvent > bgWhiteTime && attractModeOn==0) { pd.adrLED1()->colorRGB(255, 255, 255); } // set LEDs to white after an event is triggered and ball is in play
}

void checkPinStates(){
  int trigger =0;
  
  if ( pd.pinState()->J6(1) ) //Stan Flashers
  {
     pd.adrLED1()->clear();
     pd.adrLED2()->color("blue");
     delay (flashDelay);
     trigger =1;
  }
  
  if ( pd.pinState()->J6(2) ) //Chef Flashers
  { 
     pd.adrLED1()->clear();
     pd.adrLED1()->color("red");
     delay(flashDelay);
     trigger =1; 
  }
  
  if ( pd.pinState()->J6(3) ) // Kenny insert flasher
  { 
     pd.adrLED1()->clear();
     pd.adrLED1()->color("orange");
     delay(flashDelay);
     trigger =1; 
  }
  
  if ( pd.pinState()->J6(4) ) // Kyle flashers
  {
     pd.adrLED1()->clear();
     pd.adrLED1()->color("green");
     delay (flashDelay);
     trigger =1; 
  }
  
  if ( pd.pinState()->J6(5) ) // Cartman flasher
  { 
     pd.adrLED1()->clear();
     pd.adrLED1()->color("cyan");
     delay (flashDelay); 
     trigger =1; 
 
   }
   
  if ( pd.pinState()->J6(6)) // Kenny figure flashers
  {
     pd.adrLED1()->clear();
     pd.adrLED1()->color("orange");
     delay(flashDelay);
     trigger =1; 
   }
  
  if ( pd.pinState()->J6(7) ) // Mr Hankey/Toilet
  {
     for (int i = 0; i <= 4; i++)
      {
        pd.adrLED1()->clear();
        pd.adrLED1()->color("red");
        delay (50);
      }
     trigger =1;
  }
  
  if ( pd.pinState()->J6(8) )  // Super VUK flash
  { 
     pd.adrLED1()->clear();
     pd.adrLED1()->color("yellow");
     delay(flashDelay);
     trigger =1;
  }

///J7

  if ( pd.pinState()->J7(2) ) // Right Slingshot
  {
    trigger = 1; // if right sling is activated, the program will know that there is a ball in play
  }

  if ( pd.pinState()->J7(3) ) // Top VUK flasher
  {
     pd.adrLED1()->clear();
     pd.adrLED1()->color("purple");
     delay(flashDelay);
     trigger =1;
  }

//  if ( pd.pinState()->J7(4) ) // Kenny left
//  { 
//     pd.adrLED1()->clear();
//     trigger =1;
//  }
  
//  if ( pd.pinState()->J7(6) ) // Kenny right
//  {
//     pd.adrLED1()->clear();
//     trigger =1;
//  }
  
//  if ( pd.pinState()->J7(7) ) // 
//  {
//  }
//  
//  if ( pd.pinState()->J7(8) ) //
//  {
//  }
//
//  if ( pd.pinState()->J7(9) ) //
//  {
//  }
//
//  if ( pd.pinState()->J7(10) ) //
//  {
//  }

//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) 
  {
   pd.adrLED1()->clear();
   pd.adrLED2()->color("white");
   pd.pinState()->reset();
   trigger =0;
   attractModeOn = 0;
   timeLastEvent = millis();
  }
//  if (millis() - timeLastEvent > 500) {
//    pd.adrLED1()->color("blue", 200);  // LED1 string defaults to blue color when nothing happening
//    pd.adrLED2()->color("white", 200);
//  }

//end function checkPinStates
}



void attractMode() {
  if (int(random(1000)) == 0) {
    if (color1 == "red") {color1="blue";}
    else color1="red";
  }
  if (random(1000) == 0) {
    if (color2 == "red") {color2="cyan";}
    else color2="red";
  }
  pd.adrLED1()->sparkle(color1, 20);
  pd.adrLED1()->sparkle(color2, 20);
  pd.adrLED1()->sparkle("white", 200, 20);
}
