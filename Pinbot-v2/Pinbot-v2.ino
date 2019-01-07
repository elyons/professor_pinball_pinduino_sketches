//Eric Lyons 2015
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.2
//Uses pinduino library

#include <pinduino.h>
int N_LEDS = 39;
int mid = N_LEDS/2;
int aLEDNum1 = N_LEDS;
int aLEDNum2 = 0;
int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");

int bg_on = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
unsigned long startChaseWaitTime = 20000; //Amount of time to wait before chase lights start up again 1000 == 1 second
String color = "white"; //attract color

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
}

void loop(){
  backgroundChase();
  pd.pinState()->update();
//   Print the pin states out to serial 
//  pd.pinState()->print();
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) {bg_on=1;}
  else if (color == "white") {color="red";}
}

void checkPinStates(){
  int trigger =0;

  //P11-1
  if ( pd.pinState()->J6(1) && pd.pinState()->J7(8)  && !pd.pinState()->J7(4) && !pd.pinState()->J7(6)){ // outhole P11-1
  // Trigger an event so pinduino attact mode shuts off.
//    pd.adrLED1()->color("red",255);
//    delay(1000);
    trigger = 1; 
  }
  
  //P11-3
  if ( pd.pinState()->J6(2) && pd.pinState()->J7(8) && !pd.pinState()->J7(4) && !pd.pinState()->J7(6)){ // upper playfield and top flashers (2)
    pd.adrLED1()->chase2ColorFromPoint(mid, "white", "red", 10, 30);
    trigger = 1; 
  }

  //P11-4
  if ( pd.pinState()->J6(3) && pd.pinState()->J7(8) && !pd.pinState()->J7(4) && !pd.pinState()->J7(6)){ //left backglass flasher
  }

  //P11-5
  if ( pd.pinState()->J6(4) && pd.pinState()->J7(8) && !pd.pinState()->J7(4) && !pd.pinState()->J7(6)){ // right backglass flasher
  }

  //P11-6
  if ( pd.pinState()->J6(5) && pd.pinState()->J7(8) && !pd.pinState()->J7(4) && !pd.pinState()->J7(6)){ //lower playfield and top flashers (1)
    pd.adrLED1()->chase2ColorFromPoint(mid, "white", "blue", 10, 30);
    trigger = 1; 
  
  }

  //P11-7
  if ( pd.pinState()->J6(6) && pd.pinState()->J7(8) && !pd.pinState()->J7(4) && !pd.pinState()->J7(6)){ //energy flasher
    pd.adrLED1()->color("red",255);
    delay(200);
    trigger =1;
  }

  //P11-8
  if ( pd.pinState()->J6(7) && pd.pinState()->J7(8) && !pd.pinState()->J7(4) && !pd.pinState()->J7(6)){ //left playfield flasher
    pd.adrLED1()->chase2ColorFromPoint(mid, "white", "blue", 10, 30);
    trigger =1;
  }

  //P11-9
  if ( pd.pinState()->J6(8) && pd.pinState()->J7(8) && !pd.pinState()->J7(4) && !pd.pinState()->J7(6)){ //sun flasher
    pd.adrLED1()->fadeIn("red",200);
    delay(100);
    pd.adrLED1()->fadeOut(200);
  }

  //P12-1
  if ( pd.pinState()->J7(2) ){ //backglass face
  }

  //P12-2
  if ( pd.pinState()->J7(3) ){ // right eye playfield face flasher
  }

  //P12-4
  if ( pd.pinState()->J7(4) ){ // blackglass GI
  }

  //P12-5
  if ( pd.pinState()->J7(6) ){ //playfield GI
    pd.adrLED1()->clear();
    delay (2000);
  }

  //P12-6
  if ( pd.pinState()->J7(7) && !pd.pinState()->J7(4) && !pd.pinState()->J7(6) && !pd.pinState()->J7(8)){ //visor motor
    pd.adrLED1()->bullet2Color("blue", "red", 40, 10, 1);
    pd.adrLED1()->bullet2Color("red", "blue", 40, 10, -1);
    trigger =1;
  }

  //P12-7
  if ( pd.pinState()->J7(8) ){ // solenoid select relay
//    pd.adrLED1()->color("purple",255);
//    delay(1000);
//    trigger=1;
  }

  //P12-8
  if ( pd.pinState()->J7(9) ){ // top flasher (3)
//    pd.adrLED1()->bullet("red", 3, 10,  1);
//    pd.adrLED1()->bullet("red", 3, 10,  -1);
    trigger=1;
  }

  //P12-9
  if ( pd.pinState()->J7(10) ){ // top flasher (4)
//    pd.adrLED1()->bullet("blue", 3, 10,  1);
//    pd.adrLED1()->bullet("blue", 3, 10,  -1);
    trigger =1;
  }

  //clear out if there is noise due to coils
 if ( pd.pinState()->J7(4) && pd.pinState()->J7(6) && pd.pinState()->J7(7) && pd.pinState()->J7(8)){ 
    trigger =1;
  }

  


//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   timeLastEvent = millis();
   pd.pinState()->reset();
   trigger = 0;
   bg_on = 0;
  }

//end function checkPinStates
}

void backgroundChase() {
  pd.adrLED1()->sparkle(color,20,30);
  if (random(1000) == 0) {
      if (color == "white") color = "red";
      else if (color == "red") color = "blue";
      else color = "white";
  }
}
