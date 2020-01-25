//Eric Lyons2019
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3
//Uses pinduino library

/* Scott's notes for SMVE Pinduino application
 */

#include <pinduino.h>

int aLEDNum1 = 60;  // GI lights
int aLEDNum2 = 48;  // side rails

String color1 = "green";
String color2 = "blue";
String color3 = "red";

pinduino pd (aLEDNum1, aLEDNum2, "Nano");

int attractModeOn = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
int startAttractMode = 40000; //Amount of time to wait before chase lights start up again 1000 == 1 second

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
  if (millis()-timeLastEvent > startAttractMode) {attractModeOn=1;}
}

void checkPinStates(){
  int trigger =0;
  
  if ( pd.pinState()->J6(1) ) //Venom Flashers
  {
//    pd.adrLED1()->clear();
//    pd.adrLED1()->color("blue");
    delay(400);
    trigger =1; 
  }
  if ( pd.pinState()->J6(2) ) //Sandman arrow flasher
  { 
//     pd.adrLED1()->clear();
//     pd.adrLED1()->color("yellow");
     pd.adrLED2()->clear();
     pd.adrLED2()->bullet("red", "yellow", 8,  4,  -1, 0, aLEDNum1);
//     pd.adrLED2()->color("yellow");
//     delay(300);
     trigger =1; 
  }
  
  if ( pd.pinState()->J6(3) ) // Sandman dome flasher
  { 
     pd.adrLED1()->clear();
     pd.adrLED1()->color("yellow");
     pd.adrLED2()->color("yellow");
     delay(200);
     trigger =1; 
 
  }
  
  if ( pd.pinState()->J6(4) ) // green goblin flashers
  {
      pd.adrLED1()->clear();
      pd.adrLED1()->color("red");
     pd.adrLED2()->color("green");
     delay(200);
     trigger =1; 
 }
  
  if ( pd.pinState()->J6(5) ) // backpanel left flasher
  { 
//     pd.adrLED1()->clear();
//     pd.adrLED1()->color("blue");
     pd.adrLED2()->color("blue");
     delay(400);
     trigger =1; 
 
   }
   
  if ( pd.pinState()->J6(6)) // backpanel right flasher
  {
     pd.adrLED1()->clear();
     pd.adrLED1()->color("green");
//     pd.adrLED2()->color("red");
//     delay(500);
     pd.adrLED2()->bullet("red", "blue", 100,  0,  1, 0, aLEDNum1);
     trigger =1; 
  }
  
  if ( pd.pinState()->J6(7) ) // pop flashers
  {
     pd.adrLED1()->clear();
     pd.adrLED1()->color(color1);
     pd.adrLED2()->color(color2);
     if (color1 == "green") {color1="blue";}
     else color1="green";
     if (color2 == "white") {color2="blue";}
     else color2="white";  
     delay(50);
     trigger =1;
  }
  
  if ( pd.pinState()->J6(8) )
  { 

  }

///J7

//  if ( pd.pinState()->J7(2) ) // left sling
//  {
//  }
//  if ( pd.pinState()->J7(3) ) // right sling
//  {
//  }
  if ( pd.pinState()->J7(4) ) // green goblin coil
  { 
     pd.adrLED1()->clear();
     pd.adrLED1()->color("green");
     pd.adrLED2()->color("green");
     delay(50);
     trigger =1;
  }
  
  if ( pd.pinState()->J7(6) ) //sandman motor relay
  {
     pd.adrLED1()->clear();
     pd.adrLED1()->color("yellow");   
     delay(500);
     trigger =1;
  }
  
  if ( pd.pinState()->J7(7) ) // doc ock flasher
  {
     pd.adrLED1()->color("blue");
     for (int i=0; i<3; i++) {
      pd.adrLED2()->bullet("red", 20,  0,  1, 0, aLEDNum1);
     }
     trigger =1;
  }
  
//  if ( pd.pinState()->J7(8) ) //loop diverter
//  {
//  }

  if ( pd.pinState()->J7(9) ){ // sandman flashers
     pd.adrLED1()->clear();
     pd.adrLED1()->color("yellow");
     pd.adrLED2()->color("yellow");
     delay(100);
     trigger =1;
  }

//  if ( pd.pinState()->J7(10) )
//  {
//  }

//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) 
  {
   pd.adrLED1()->clear();
   pd.adrLED2()->clear();
   pd.adrLED1()->color("white");
   pd.adrLED2()->colorRGB(180,255,255); // My LED strips were a bit pink when set to white, so dialing back the red
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
    if (color1 == "green") {color1="blue";}
    else color1="green";
  }
  if (random(1000) == 0) {
    if (color2 == "green") {color2="blue";}
    else color2="green";
  }
  if (random(1000) == 0) {
    if (color3 == "yellow") {color3="blue";}
    else if (color3 == "blue") {color3="purple";}
    else color3="red";
  }
  pd.adrLED1()->sparkle(color1, 20);
  pd.adrLED1()->sparkle(color2, 20);
  pd.adrLED1()->sparkle("white", 200, 20);
  pd.adrLED2()->sparkle(color3, 20);
  pd.adrLED2()->sparkle("white", 200, 20);
}
