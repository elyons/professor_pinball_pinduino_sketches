//Eric Lyons2019
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3
//Uses pinduino library

/* Scott's notes for SMVE Pinduino application
 */

#include <pinduino.h>
int R_start = 35;  // right ramp entrance
int R_stop = 0;
int L1_start = 36; // left ramp entrance
int L1_stop = 60;
int L2_start = 61; // left side ramp entrance
int L2_stop = 75;

int aLEDNum1 = 76;  // backpanel led count is 15 and undercabinet led count is 35 each on two parallel strings.  Backpanel and undercabinet lights are on same string so go with the higher led count number here
int aLEDNum2 = 16;  // trough led count is 9.  Trough led's are on their own string so there is more flexibility to color them white to provide more while light on the playfield between the flippers

int LED1FlashDelay = 50;  // variable to input flash delays for LED1 (does not affect BGChase function)
int LED2FlashDelay = 50;  // variable to input flash delays for LED2

String color1 = "red";
String color2 = "blue";
String color3 = "green";

pinduino pd (aLEDNum1, aLEDNum2, "Nano");

int attractModeOn = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
int startAttractMode = 30000; //Amount of time to wait before chase lights start up again 1000 == 1 second

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
     pd.adrLED1()->clear();
     pd.adrLED2()->color("blue");
     pd.adrLED1()->bullet("blue", 7, 3, 1, L1_start, L1_stop);
     pd.adrLED1()->bullet("blue", 7, 3, -1, L2_start, L2_stop);
     trigger =1;
  }
  
  if ( pd.pinState()->J6(2) ) //Sandman arrow flasher
  { 
     pd.adrLED1()->clear();
     pd.adrLED2()->color("orange");
     pd.adrLED1()->color("yellow");
     delay(100);
     pd.adrLED1()->bullet("yellow", 3, 2, 1, R_start, R_stop);
     pd.adrLED1()->bullet("yellow", 3, 2, -1, L2_start, L2_stop);
     pd.adrLED1()->bullet("yellow", 3, 2, -1, L1_start, L1_stop);
     trigger =1; 
  }
  
  if ( pd.pinState()->J6(3) ) // Sandman dome flasher
  { 
     pd.adrLED1()->clear();
     pd.adrLED1()->bullet("yellow", "orange", 5, 5, -1, R_start, R_stop);
     pd.adrLED1()->bullet("orange", "yellow", 5, 5, 1, R_start, R_stop);
     delay (200);
     trigger =1; 
  }
  
  if ( pd.pinState()->J6(4) ) // green goblin flashers
  {
     pd.adrLED1()->clear();
     pd.adrLED2()->color("green");
     pd.adrLED1()->bullet("green", 20, 2, 1, L2_start, L2_stop);
     pd.adrLED1()->bullet("green", 20, 2, -1, R_start, R_stop);
     pd.adrLED1()->bullet("green", 20, 2, 1, L1_start, L1_stop);
     delay (200);
     trigger =1; 
  }
  
  if ( pd.pinState()->J6(5) ) // backpanel left flasher
  { 
     pd.adrLED1()->clear();
     pd.adrLED2()->color("blue");
     pd.adrLED1()->bullet("blue", 10, 4, 1, L2_start, L2_stop);
     pd.adrLED1()->bullet("blue", 10, 4, -1, L1_start, L1_stop);
     trigger =1; 
 
   }
   
  if ( pd.pinState()->J6(6)) // backpanel right flasher
  {
     pd.adrLED1()->clear();
     pd.adrLED2()->color("red");
     pd.adrLED1()->bullet("red", 12, 8, -1, R_start, R_stop);
     trigger =1;
  }
  
  if ( pd.pinState()->J6(7) ) // pop flashers
  {
     pd.adrLED1()->clear();
     pd.adrLED1()->color(color1);
     pd.adrLED2()->color(color2);
     if (color1 == "red") {color1="blue";}
     else color1="red";
     if (color2 == "white") {color2="blue";}
     else color2="white";  
     delay (50);
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
     delay (200);
     trigger =1;
  }
  
  if ( pd.pinState()->J7(6) ) //sandman motor relay
  {
     pd.adrLED1()->clear();
     pd.adrLED2()->color("yellow");   
     pd.adrLED1()->bullet("yellow", 20, 2, -1, L1_start, L1_stop);
     pd.adrLED1()->bullet("yellow", 20, 2, 1, R_start, R_stop);
     pd.adrLED1()->bullet("yellow", 20, 2, -1, L2_start, L2_stop);
     trigger =1;
  }
  
  if ( pd.pinState()->J7(7) ) // doc ock flasher
  {
     pd.adrLED1()->clear();
     pd.adrLED2()->color("red");
     for (int i=0; i<4; i++) {
      pd.adrLED1()->bullet("red", 3,  2,  -1, R_start, R_stop);
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
     delay (200);
     trigger =1;
  }

//  if ( pd.pinState()->J7(10) )
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
    if (color2 == "red") {color2="blue";}
    else color2="red";
  }
  if (random(1000) == 0) {
    if (color3 == "green") {color3="yellow";}
    else color3="green";
  }
  pd.adrLED1()->sparkle(color1, 20);
  pd.adrLED1()->sparkle(color2, 20);
  pd.adrLED1()->sparkle("white", 200, 20);
  pd.adrLED2()->sparkle(color3, 20);
}


