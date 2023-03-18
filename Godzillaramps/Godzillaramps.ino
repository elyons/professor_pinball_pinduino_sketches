//Eric Lyons 2020
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3
//Uses pinduino library

//Controls two sets of LEDs -- one down the outside of each ramp

#include <pinduino.h>

int aLEDNum1 = 118;  // Godzilla ramp, exists left 
int aLEDNum2 = 64;  // Right ramp

String color1 = "green";
String color2 = "green";
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

void loop() {
  //   Print the pin states out to serial
  //  pd.pinState()->print();
  if (attractModeOn) {
    attractMode();
  }
  pd.pinState()->update();
  checkPinStates();
  if (millis() - timeLastEvent > startAttractMode) {
    attractModeOn = 1;
  }
}

void checkPinStates() {
  int trigger = 0;

  if ( pd.pinState()->J6(1) ) //Pops
  {
    pd.adrLED1()->color("green");
    pd.adrLED2()->color("green");
    delay(50);
    pd.adrLED1()->color("yellow");
    pd.adrLED2()->color("yellow");
    delay(50);
    trigger = 1;
  }
  if ( pd.pinState()->J6(2) ) //Top Left (2x yellow dome)
  {
    pd.adrLED1()->bullet("yellow", 40,  4,  1);
    trigger = 1;
  }

  if ( pd.pinState()->J6(3) ) // Center Playfield (taxi insert)
  {
    pd.fadeInAllAdr("yellow", 500);
    delay(200);
    pd.fadeOutAllAdr(500);
    trigger = 1;

  }

  //  if ( pd.pinState()->J6(4) ) // Right ramp insert (white footprint insert)
  //  {
  //     pd.adrLED2()->clear();
  //     pd.adrLED2()->bullet("white", "red", 8,  4,  -1);
  //     trigger = 1;
  //  }

  if ( pd.pinState()->J6(5) ) // Right ramp insert (Light Gozilla multiball insert)
  {
    pd.adrLED1()->bullet("yellow", "red", 40,  2,  1);
    trigger = 1;
  }

  if ( pd.pinState()->J6(6)) // Right ramp insert (Score does matter)
  {
    pd.adrLED1()->bullet("green", 40,  2,  1);
    trigger = 1;
  }

  if ( pd.pinState()->J6(7) ) // Sling/kicker flashers (helicopter insert)
  {
    pd.adrLED1()->color("green");
    pd.adrLED2()->color("green");
    delay(100);
    trigger = 1;
  }

  if ( pd.pinState()->J6(8) ) // Top right flashers 2x red dome
  {
    pd.adrLED2()->bullet("green", "green", 40,  4,  1);
    trigger = 1;
  }

  ///J7

  if ( pd.pinState()->J7(2) ) // Godzilla ramp mouth diverter
  {
    pd.adrLED1()->color("green");
    pd.adrLED2()->color("green");
    delay(500);
    trigger = 1;
  }

  if ( pd.pinState()->J7(3) ) // Left ramp middle -- green dome
  {
    pd.adrLED1()->color("green");
    delay(200);
    trigger = 1;
  }

  if ( pd.pinState()->J7(4) ) // Right ramp middle -- green dome
  {
    pd.adrLED2()->color("green");
    delay(200);
    trigger = 1;
  }

  if ( pd.pinState()->J7(6) ) //Inner left orbit playfield flashers (2x)
  {
    pd.chaseAllAdr2RGBFromPoint(90, 0,255,0,0,255,0, 10, 0);    
    trigger = 1;
  }

  //  if ( pd.pinState()->J7(7) ) // not used
  //  {
  //  }

  //  if ( pd.pinState()->J7(8) ) //not used
  //  {
  //  }

  //  if ( pd.pinState()->J7(9) ) // not used
  //  {
  //  }

  //  if ( pd.pinState()->J7(10) ) // not used
  //  {
  //  }

  //trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger)
  {
    pd.adrLED1()->clear();
    pd.adrLED2()->clear();
    pd.pinState()->reset();
    trigger = 0;
    attractModeOn = 0;
    timeLastEvent = millis();
  }

  //end function checkPinStates
}



void attractMode() {
  pd.adrLED1()->sparkle(color1, 20);
  pd.adrLED2()->sparkle(color2, 20);
}
