//Eric Lyons 2021
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3
//Uses pinduino library

#include <pinduino.h>
const int TOPPER = 18;
int RAMP = 67;
int MID = RAMP/2;

int aLEDNum1 = RAMP;
int aLEDNum2 = TOPPER;

pinduino pd (aLEDNum1, aLEDNum2, "Nano");

int attractMode_on = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
unsigned long timeLastTopperEvent = 0; // time last topper light was updated
int attractWaitTime = 30000; //Amount of time to wait before attract mode starts up again 1000 == 1 second

//stuff for the topper lights
int topperArray[TOPPER]; //initialize empty array for tracking topper lights.  If light is turned on, set array value for that position to 1.  
int topperWaitTime = 1000; //Amount of time to wait between updating topper

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.pinState()->reset();
  clearTopper();
}

void loop(){
  if (attractMode_on){attractMode();}
  pd.pinState()->update();
//   Print the pin states out to serial 
  //pd.pinState()->print();
  checkPinStates();
  if (millis()-timeLastEvent > attractWaitTime) {attractMode_on=1;} // turn on attract mode
  if (millis()-timeLastTopperEvent > topperWaitTime) {updateTopper();} // time to check topper
  
}


void updateTopper() {
  //check to see if all the lights are on
  int topperAllOn = checkTopper();
//  Serial.println(topperAllOn);
  if (topperAllOn) { // turn off all lights if all are on
    clearTopper();
  }
  else { // pick a random number until one is found that is not a lit topper light
    int pos = random(0,TOPPER); 
    while (topperArray[pos]==1) {pos = random(0,TOPPER);}
    topperArray[pos]=1;
  }
  setTopperLights(); // light up topper
  timeLastTopperEvent=millis(); // record when this happened
}

void clearTopper() {
  for (int i=0; i<TOPPER; i=i+1) {
    topperArray[i]=0;
  }
}

void setTopperLights() {
  for (int i=0; i<TOPPER; i=i+1) {
    if (topperArray[i]==1) {
      pd.adrLED2()->strip()->setPixelColor(i, 255, 255, 255);
    }
    else {
      pd.adrLED2()->strip()->setPixelColor(i, 0, 0, 0);
    }
  }
  pd.adrLED2()->strip()->show();
}

int checkTopper() { // check if all topper lights are one
  int count = 0; 
  for (int i=0; i<TOPPER; i=i+1) {
    if (topperArray[i]) {count=count+1;}
//    Serial.print(topperArray[i]);
  }
  if (count == TOPPER) {return 1;}
  return 0;
}

void checkPinStates(){
  int trigger =0;
  
  if ( pd.pinState()->J6(1) ){ // wheel
    pd.adrLED1()->clear();
    pd.adrLED1()->chase2ColorFromPoint(MID, "white", "blue", 4, 2);
    trigger =1;
  }
  if ( pd.pinState()->J6(2) ){ // backpanel left
    trigger =1;
  }
  if ( pd.pinState()->J6(3) ){ //mid left
    pd.adrLED1()->clear();
    pd.adrLED1()->chase2Color("purple", "blue", 4, 2, -1);
    trigger =1;
  }
  if ( pd.pinState()->J6(4) ){ //upper right
  }
  if ( pd.pinState()->J6(5) ){ // might right
    pd.adrLED1()->clear();
    pd.adrLED1()->chase2Color("yellow", "red", 4, 2, -1);
    trigger =1;
  }
  if ( pd.pinState()->J6(6)){ // pop
    pd.adrLED1()->clear();
    pd.adrLED1()->color("sky");
    delay(50);
    pd.adrLED1()->clear();
    trigger =1;
  }
  if ( pd.pinState()->J6(7) ){ // upper left
    trigger =1;
  }
  if ( pd.pinState()->J6(8) ){ //backpanel right
    trigger =1;
  }

///J7

  if ( pd.pinState()->J7(2) ){ // left sling
    trigger=1;
  }
  if ( pd.pinState()->J7(3) ){ // right sling
    trigger=1;
  }
  if ( pd.pinState()->J7(4) ){ // contestant 1
    pd.adrLED1()->clear();
    pd.adrLED1()->color("red");
    delay(50);
    pd.adrLED1()->clear();
    trigger =1;
  }
  if ( pd.pinState()->J7(6) ){ // contestant 2
    pd.adrLED1()->clear();
    pd.adrLED1()->color("yellow");
    delay(50);
    pd.adrLED1()->clear();
    trigger =1;
  }
  if ( pd.pinState()->J7(7) ){ // contestant 3
    pd.adrLED1()->clear();
    pd.adrLED1()->color("blue");
    delay(50);
    pd.adrLED1()->clear();
    trigger =1;
  }
  if ( pd.pinState()->J7(8) ){ // mini-ramp post
    trigger=1;
  }
  if ( pd.pinState()->J7(9) ){ // left ramp post
    trigger=1;
  }
  if ( pd.pinState()->J7(10) ){ //not used
  }

//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   pd.adrLED1()->clear();
   pd.pinState()->reset();
   trigger =0;
   attractMode_on = 0;
   timeLastEvent = millis();
  }

//end function checkPinStates
}



void attractMode() {
  pd.adrLED1()->fire(20,10);
}
