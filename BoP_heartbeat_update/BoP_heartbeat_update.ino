//Rob Lewewllyn and Eric Lyons 2021
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.2 and v0.3
//Uses pinduino library

/// ---=====  NOTE ====---
/// 

#include <pinduino.h>
int aLEDNum1 = 46;  //ramp
int aLEDNum2 = 7;   //head

pinduino pd (aLEDNum1, aLEDNum2, "Nano");

int bg_on = 1;                    //attract effect
unsigned long timeLastEvent = 0;  // time last event was last triggered
int startChaseWaitTime = 30000;   //Amount of time to wait before chase lights start up again 1000 == 1 second
int bgWhiteTime = 500;
unsigned long lastBoob = 0;       // time since boobs last went off
unsigned long lastHelmet = 0;     // time since Helmet last went off
const unsigned long timeBetweenBoobHelmetFlash = 500; //the time in ms between boobs and helmet at start of metamorphasis sequence

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.pinState()->reset();
}

void loop(){
  if (bg_on){background();}
  for (int i=0; i<500; i=i+1) { //check pinstates for a while    
    pd.pinState()->update();
  }
//   Print the pin states out to serial 
//   pd.pinState()->print();
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) {bg_on=1;}
  if (millis()-timeLastEvent > bgWhiteTime && !bg_on) {
    pd.adrLED1()->clear();
    pd.adrLED2()->color("white");
  }
}

void checkPinStates(){
  int trigger =0;
  
  if ( pd.pinState()->J126(1) ){ // billion
    for (int i=0; i<10; i++) {
     pd.adrLED2()->chase2Color("red", "blue", 1,  20,  -1);
     pd.adrLED2()->chase2Color("blue", "red", 1,  20,  1);
    }
    trigger = 1; 
  }

 if ( pd.pinState()->J126(2) ){ //left ramp shuttle
    pd.adrLED2()->color("blue", 255);
    pd.adrLED1()->chase2Color("purple","blue", 2,  10,  -1);
    pd.adrLED2()->fadeOut(1000);
    trigger = 1; 
  }

  if ( pd.pinState()->J126(3) ){ //jackpot
    pd.adrLED1()->chase2ColorFromPoint(23, "green", "red", 10,5);
    trigger = 1; 
  }
  if ( pd.pinState()->J126(4) ){ // right shuttle skill shot
    pd.adrLED2()->color("red", 255);
    pd.adrLED2()->fadeOut(200);
    trigger=1;
  }
  if ( pd.pinState()->J126(5) ){ // left helmet
    pd.adrLED2()->color("yellow", 255);
    delay(100);
    pd.adrLED2()->clear();    
    trigger = 1; 
  }
  
  if ( pd.pinState()->J126(6) ){ // right helmet
    pd.adrLED2()->color("purple", 255);
    delay(100);
    pd.adrLED2()->clear();    
    trigger = 1; 
  }
  
  if ( pd.pinState()->J126(7) ){ //right boob
    pd.adrLED2()->color("red", 255);
    delay(100);
    pd.adrLED2()->clear();
    trigger = 1; 
  }
  if ( pd.pinState()->J126(8) && ! pd.pinState()->J126(7) ){ // 8==left boob, 7==right boob
    pd.adrLED2()->color("blue", 255);
    pd.adrLED1()->chase2Color("red", "orange", 60,  1,  -1);
    pd.adrLED2()->clear();
    trigger = 1;
  }
  //check to see if metamorphasis has started.  If so, run the metamorphasis effects.
  bool metamorphasisStarted = metamorphasisCheck();
  if (metamorphasisStarted) {metamorphasisEffect();}

  //trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   pd.pinState()->reset();
   trigger =0;
   bg_on = 0;
   timeLastEvent = millis();
  }
//end function checkPinStates
}


void background() {
  pd.adrLED2()->fadeOut(500);
  pd.adrLED2()->clear();
  delay(500);
  pd.adrLED1()->chase2Color("red", "orange", 35,  5,  -1);
  delay(200);
  for (int i=0; i<10; i++) {
     int cor = i*15;
     int time = 110-cor;
     if (time < 20){time = 20;}
     pd.adrLED2()->chase("red", 1,  time,  -1);
    }  
  pd.adrLED2()->fadeIn("red", 500);
  pd.adrLED2()->fadeColor2Color("red", "purple", 500);
  delay(300);
  pd.adrLED2()->fadeColor2Color("purple", "white", 500);
  delay(300);
  pd.adrLED2()->fadeColor2Color("white", "blue", 500);
  delay(300);
}

// robs new heartbeat bit
//function returns boolean value for checking if game is in metamorphasis
bool metamorphasisCheck() { // Has metamorphasis sequence begun
  unsigned long currentTime = millis ();
  if (pd.pinState()->J126(8) && pd.pinState()->J126(7) ){// 8==left boob, 7==right boob
     lastBoob = currentTime;
  }
  if (pd.pinState()->J126(6) && pd.pinState()->J126(5) ){// 6==left helmet, 5==right helmet
    lastHelmet = currentTime;
  }
  if (lastHelmet - lastBoob <= timeBetweenBoobHelmetFlash){
    return(true);
  }
  return(false);
}
// robs new heartbeat bit ends

void metamorphasisEffect() {
  //add stuff ehre for the lighting effects for metamorphasis
  
}


