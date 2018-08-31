//Mike Ott 2018

#include <pinduino.h>
#include <AddressableStrip.h>


int N_LEDS = 40;
int N_LEDS2 = 59;
int aLEDNum1 = N_LEDS;
int aLEDNum2 = N_LEDS2;
int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");

// J6-1:  Flash: Under Right Ramp (stars) x3, Backbox Insert (BLK-BRN)
// J6-2:  Flash: Under Right Ramp (stars) x3, Backbox  (BLK-RED)
// J6-3:  Flash: Under Right Ramp (stars) x3, Backbox (BLK-ORG)
// J6-4:  Flash: Pop Bumber Area, Backpanel, Backbox Insert (BLK-YEL)
// J6-5:  Flash: Upper Right Playfield, Lower Right Playfield, Backpanel (BLK-GRN)
// J6-6:  Flash: Upper Left Playfield, Lower Left Playfield, Backpanel (BLK-BLU)
// J6-7:  Flash: Pop Bumper Area, Backpanel, Backbox Insert (BLK-VIO)
// J6-8:  Flash: Rocket Area, Backox Insert (BLK-GRY)

// J7-2:  Coil: 5-Ball Trough Lock Ball (VIO-BRN)
// J7-3:  Coil: Up/Down Ramp (VIO-RED)
// J7-4:  Coil: Moon Motor Relay (VIO-ORG)
// J7-6:  Coil: Rocket Motor Relay (VIO-YEL)
// J7-7:  Coil: TRAP DOOR (VIO-GRN)
// J7-8:  Coil: 8 BALL LOCK PLUNGER (VIO-BLU)
// J7-9:  Coil: UP DOWN POST (VIO-BLK)

int bg_chase_on = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
unsigned long startChaseWaitTime = 8000; //Amount of time to wait before chase lights start up again 1000 == 1 second
String chaseColor = "mint"; //attract color
int bg_style = 1;

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
}

void loop() {
  SetChaseColor();
  if (bg_chase_on) {
    backgroundChase();
  }
  pd.pinState()->update();
  //   Print the pin states out to serial
  // pd.pinState()->print();
  checkPinStates();

  if (millis() - timeLastEvent > startChaseWaitTime) {
    bg_chase_on = 1;
  }
}

void checkPinStates() {
  int trigger = 0;

  if (pd.pinState()->J6(1) ) { //UNDER RIGHT RAMP FLASHER
    pd.adrLED2()->fadeIn(chaseColor, 200);
    pd.adrLED1()->equalizer("blue", "green", 35, 15, 4, 1,1);
    trigger = 1;
  }

  if ( pd.pinState()->J6(2) ) {
    pd.adrLED2()->fadeIn(chaseColor, 200);
    pd.adrLED1()->equalizer("sky", "lime", 40, 10, 3, 0,1);
    trigger = 1;
  }

  if ( pd.pinState()->J6(3) ) {
    pd.adrLED2()->fadeIn(chaseColor, 200);
    pd.adrLED1()->equalizer("sky", "lime", 40, 10, 3, 0,1);
    trigger = 1;
  }

  if ( pd.pinState()->J6(4) ) { //FLASHER - POP BUMPER AREA
    pd.adrLED1()->spreadInFromPoint(20, chaseColor, 50);
    pd.adrLED1()->spreadOutFromPoint(20, 50);
    trigger = 1;
  }

  if ( pd.pinState()->J6(5) ) { // FLASHER - UPPER AND LOWER RIGHT PLAYFIELD
    pd.adrLED2()->color(chaseColor, 255);
    pd.adrLED1()->spreadInFromPoint(5, chaseColor, 200);
    pd.adrLED1()->spreadOutFromPoint(5, 100);
    pd.adrLED2()->fadeOut(200);
    trigger = 1;
  }

  if ( pd.pinState()->J6(6) ) { // FLASHER - UPPER AND LOWER LEFT PLAYFIELD
    pd.adrLED2()->color(chaseColor, 255);
    pd.adrLED1()->spreadInFromPoint(10, chaseColor, 150);
    pd.adrLED1()->spreadOutFromPoint(10, 150);
    pd.adrLED2()->fadeOut(200);
    trigger = 1;
  }

  if ( pd.pinState()->J6(7) ) { //POP BUMPER AREA
    pd.adrLED1()->spreadInFromPoint(20, chaseColor, 200);
    pd.adrLED1()->spreadOutFromPoint(20, 200);
    trigger = 1;
  }
  if ( pd.pinState()->J6(8) ) { //Rocket Area, Backbox Insert
    pd.adrLED1()->color("red", 255);
    pd.adrLED2()->color("red", 255);
    delay(50);
    pd.adrLED1()->color("red", 100);
    pd.adrLED2()->color("orange", 255);
    delay(50);
    pd.adrLED1()->color("red", 255);
    pd.adrLED2()->color("red", 255);
    pd.adrLED1()->fadeOut(50);
    pd.adrLED2()->fadeOut(50);
    pd.adrLED1()->color("magenta", 255);
    pd.adrLED2()->color("yellow", 255);
    delay(50);
    pd.adrLED1()->color("red", 155);
    pd.adrLED2()->color("red", 255);
    pd.adrLED1()->fadeOut(50);
    pd.adrLED2()->fadeOut(50);
    SetChaseColor();
    trigger = 1;

  }

  if ( pd.pinState()->J7(2) ) { //5 BALL TROUGH LOCK
    pd.adrLED1()->equalizer("sky", "lime", 40, 15, 5, 0);
    pd.adrLED1()->equalizer("lime", "sky", 40, 15, 5, 1);
    trigger = 1;
  }
  if ( pd.pinState()->J7(3) ) { //UP DOWN RAMP
    pd.adrLED1()->spreadInFromPoint(40, chaseColor, 250);
    pd.adrLED2()->spreadInFromPoint(59, chaseColor, 250);
    delay(50);
    pd.adrLED1()->spreadOutFromPoint(40, 250);
    pd.adrLED2()->spreadOutFromPoint(59, 250);
    SetChaseColor();
    trigger = 1;
  }

  if ( pd.pinState()->J7(4) ) { //Moon Motor Relay
    pd.adrLED1()->spreadInFromPoint(1, chaseColor, 50);
    pd.adrLED2()->spreadInFromPoint(1, chaseColor, 50);
    delay(50);
    pd.adrLED1()->spreadOutFromPoint(1, 50);
    pd.adrLED2()->spreadOutFromPoint(1, 50);
    SetChaseColor();
    trigger = 1;
  }

  if ( pd.pinState()->J7(6) ) { //Rocket Motor Relay
    pd.adrLED1()->chase2ColorFromPoint(20, chaseColor, chaseColor, 6, 10);
    pd.adrLED2()->chase2ColorFromPoint(30, chaseColor, chaseColor, 20, 5);
    SetChaseColor();
    trigger = 1;
  }

  if ( pd.pinState()->J7(8) ) { //8 BALL LOCK PLUNGER
    pd.adrLED1()->color("sky", 255);
    pd.adrLED2()->color("red", 255);
    delay(50);
    pd.adrLED1()->color("red", 100);
    pd.adrLED2()->color("orange", 255);
    delay(50);
    pd.adrLED1()->color("red", 255);
    pd.adrLED2()->color("red", 255);
    pd.adrLED1()->fadeOut(50);
    pd.adrLED2()->fadeOut(50);
    pd.adrLED1()->color("magenta", 255);
    pd.adrLED2()->color("yellow", 255);
    delay(50);
    pd.adrLED1()->color("blue", 155);
    pd.adrLED2()->color("mint", 255);
    pd.adrLED1()->fadeOut(50);
    pd.adrLED2()->fadeOut(50);
    SetChaseColor();
    trigger = 1;

  }

  if ( pd.pinState()->J7(9) ) { //  UP/DOWN POST
    pd.adrLED1()->fadeIn("red", 50);
    pd.adrLED2()->fadeIn("red", 50);
    trigger = 1;
  }

  //trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
    timeLastEvent = millis();
    pd.adrLED1()->clear();
    pd.adrLED2()->clear();
    pd.pinState()->reset();
    trigger = 0;
    bg_chase_on = 0;
  }

  //end function checkPinStates
}


void backgroundChase() {
  if (bg_style <= 1) {
    pd.adrLED1()->sparkle(chaseColor, 20, 30);
    pd.adrLED2()->sparkle(chaseColor, 40, 30);
  }
  if (bg_style == 2) {
     pd.adrLED1()->dataStreamNoTail2Color("blue", "mint", 20, 20, 1);
    
  }
  if (bg_style == 3) {
   
int dir = random(2);
    if (dir > 1)dir = 0;
    int spd = random(5) * 10;
    if (spd < 10)spd = 10;
    pd.adrLED1()->equalizerRGB(random(255), random(255), random(255), random(255), random(255), random(255), random(35) + 5, spd, random(4) + 1, dir,1);

  }
  if (random(250) == 0) {
    bg_style = random(4);
    if (bg_style > 1) {
      pd.adrLED2()->fadeIn(chaseColor, 200);
    }
  }
}

void SetChaseColor() {
  if (chaseColor == "blue") {
    chaseColor = "mint";
  }
  else if (chaseColor == "mint") {
    chaseColor = "cyan";
  }
  else if (chaseColor == "cyan") {
    chaseColor = "yellow";
  }
  else if (chaseColor == "yellow") {
    chaseColor = "orange";
  }
  else if (chaseColor == "orange") {
    chaseColor = "sky";
  }
  else if (chaseColor == "sky") {
    chaseColor = "white";
  }
  else {
    chaseColor = "blue";
  }
}


