//Eric Lyons 2016
//Updated by Andrea Lazzari 2020
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3
//Uses pinduino library

#include <pinduino.h>

int highBright=255;
int mediumBright=255;
int lowBright=255;
int aLEDNum1 = 71;
int aLEDNum2 = 27; 
int aLEDNum3 = 0;
int N_LEDS=aLEDNum1;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");

int bg_chase_on = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 30000; //Amount of time to wait before chase lights start up again 1000 == 1 second
int whiteWaitTime = 100; //Amount of time to wait before gumball goes to white

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear(); // RAMP
  pd.adrLED2()->clear(); // BOWL
  pd.adrLED3()->clear();
  pd.pinState()->reset();
}

void loop(){
  pd.pinState()->update();
  checkPinStates();
  if (bg_chase_on){backgroundChase();}
  
//   Print the pin states out to serial 
 // pd.pinState()->print();
  if (millis()-timeLastEvent > startChaseWaitTime) {bg_chase_on=1;}

}

void checkPinStates(){
  int trigger =0;
  
  if ( pd.pinState()->J126(1) ){ // Bottom left A2 (16)
    Serial.println("J126(1): Bottom Left");
    pd.pinState()->print();
    pd.adrLED1()->fadeOut(50);
    pd.adrLED2()->fadeOut(50);
    pd.adrLED2()->strip()->setBrightness(mediumBright);
    pd.adrLED2()->bullet2RGB(0,100,0, 0,0,100, 1, 14, -1);
    pd.adrLED2()->clear();
    trigger=1;
  }
  if ( pd.pinState()->J126(2) ){ //Right Ramp A3 (17)
    Serial.println("J126(2): Right Ramp");
    pd.pinState()->print();
    pd.adrLED1()->fadeOut(50);
    pd.adrLED2()->fadeOut(50);
    pd.adrLED2()->fadeInRGB(128,255,0,400);
    delay(100);
    pd.adrLED2()->fadeRGB2RGB(128,255,0, 0,0,100, 400);
    delay(100);
    pd.adrLED2()->fadeOut(200);
    trigger=1;
  }
  if ( pd.pinState()->J126(3) ){ // Left Ramp A4 (18)
    Serial.println("J126(3): Left Ramp");
  pd.pinState()->print();
     pd.adrLED1()->fadeOut(50);
    pd.adrLED2()->fadeOut(50);
    pd.adrLED2()->strip()->setBrightness(mediumBright);
   // pd.adrLED2()->bullet2RGB(0,100,0, 0,0,100, 1, 14, 1);
     pd.adrLED2()->bullet2RGB(0,100,0, 0,0,100, 1, 14, 1);
    pd.adrLED2()->clear();
    trigger=1;
  }
  if ( pd.pinState()->J126(4) ){ //Sequential GI A5
   // Serial.println("J126(4): Sequential GI");
   //   pd.pinState()->print();
  //  trigger=1;
  }
  if ( pd.pinState()->J126(5) ){ //Hologram Push motor A1 (15)
    Serial.println("J126(5): Hologram Push Motor");
  pd.pinState()->print();
 
    pd.adrLED1()->fadeOut(50);
    pd.adrLED2()->fadeOut(50);
    pd.adrLED1()->strip()->setBrightness(highBright);
    pd.adrLED2()->strip()->setBrightness(mediumBright);
    pd.adrLED1()->chase2RGB(0,200,155, 0,255,0, N_LEDS/4, 10, -1);
    pd.adrLED2()->bullet2RGB(0,255,0, 0,255,0, 1, 17, -1);
    pd.adrLED2()->bullet2RGB(0,255,0, 0,255,0, 1, 16, -1);
    pd.adrLED2()->bullet2RGB(0,255,0, 0,255,0, 1, 15, -1);
    pd.adrLED2()->bullet2RGB(0,255,0, 0,255,0, 1, 14, -1);
    pd.adrLED2()->bullet2RGB(0,255,0, 0,255,0, 1, 13, -1);
    pd.adrLED2()->bullet2RGB(0,255,0, 0,255,0, 1, 12, -1);
    pd.adrLED2()->bullet2RGB(0,255,0, 0,255,0, 1, 11, -1);
    pd.adrLED2()->bullet2RGB(0,255,0, 0,200,0, 1, 10, -1);
    pd.adrLED2()->bullet2RGB(0,200,0, 0,200,0, 1, 9, -1);
    pd.adrLED2()->bullet2RGB(0,200,0, 0,200,0, 1, 8, -1);
    pd.adrLED2()->bullet2RGB(0,150,0, 0,150,0, 1, 7, -1);
    pd.adrLED2()->bullet2RGB(0,150,0, 0,150,0, 1, 6, -1);
    pd.adrLED2()->bullet2RGB(0,100,0, 0,100,0, 1, 5, -1);
    pd.adrLED2()->bullet2RGB(0,100,0, 0,100,0, 1, 4, -1);
    pd.adrLED2()->bullet2RGB(0,100,0, 0,100,0, 1, 3, -1);
    pd.adrLED2()->bullet2RGB(0,100,0, 0,100,0, 1, 3, -1);
    pd.adrLED2()->bullet2RGB(0,100,0, 0,100,0, 1, 3, -1);
    pd.adrLED2()->bullet2RGB(0,100,0, 0,100,0, 1, 3, -1);
    pd.adrLED2()->bullet2RGB(0,100,0, 0,50,0, 1, 2, -1);
    pd.adrLED2()->bullet2RGB(0,50,0, 0,50,0, 1, 1, -1);
    pd.adrLED2()->bullet2RGB(0,50,0, 0,50,0, 1, 1, -1);
    pd.adrLED2()->bullet2RGB(0,50,0, 0,50,0, 1, 1, -1);
    pd.adrLED2()->bullet2RGB(0,50,0, 0,50,0, 1, 1, -1);
    pd.adrLED2()->bullet2RGB(0,50,0, 0,50,0, 1, 1, -1);
    pd.adrLED2()->bullet2RGB(0,50,0, 0,25,0, 1, 1, -1);
    pd.adrLED2()->bullet2RGB(0,25,0, 0,25,0, 1, 1, -1);
    pd.adrLED2()->bullet2RGB(0,25,0, 0,10,0, 1, 1, -1);
    pd.adrLED2()->bullet2RGB(0,10,0, 0,0,0, 1, 1, -1);
    pd.adrLED2()->clear();

    trigger=1;
  }
  if ( pd.pinState()->J126(6) ){ //Center Hole Flasher A0 (14)
    Serial.println("J126(6): Center Hole Flasher");
  pd.pinState()->print();
    pd.adrLED1()->fadeOut(50);
    pd.adrLED2()->fadeOut(50);
    pd.adrLED1()->strip()->setBrightness(highBright);
    pd.adrLED1()->chase2RGB(50,0,0, 255,0,50, N_LEDS/2, 4, 1);
    trigger=1;
  }
  if ( pd.pinState()->J126(7) ){ // Up/Down Ramp (UP) D13 (13)
  //pd.pinState()->print();
  //Serial.println("J126(7): Up/Down Ramp (UP)");
 
 //   pd.adrLED1()->chase2Color("red", "purple", N_LEDS, 10, 1);
//    pd.adrLED1()->color("yellow",255);
//    delay(100);
 //   trigger=1;
  }
  if ( pd.pinState()->J126(8) ){ //Sequential GI 2 D12 (12)
    //Serial.println("J126(8): Sequential GI 2");
     //pd.pinState()->print();
 
//    pd.adrLED1()->chase2Color("blue", "green", N_LEDS, 10, 1);
   // trigger=1;
  }
  if ( pd.pinState()->J126(9) ){ 
    trigger=1;
  }
  if ( pd.pinState()->J126(10) ){ 
//    
    trigger=1;
  }

  
//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   pd.adrLED1()->clear();
   pd.pinState()->reset();
   trigger =0;
   bg_chase_on = 0;
   timeLastEvent = millis();
  }
//end function checkPinStates
}



void backgroundChase() {

  pd.adrLED1()->strip()->setBrightness(mediumBright);
  pd.adrLED2()->strip()->setBrightness(mediumBright);
  pd.adrLED1()->sparkle("mint",20);
  //pd.adrLED2()->sparkleRGB(255,0,50,20);
  pd.adrLED2()->sparkle("lavender",20);
  if (random(500) == 0) {
    Serial.println("BG Chase Random trigger");   
    pd.adrLED1()->fadeOut(50);
    pd.adrLED2()->fadeOut(50);
    pd.adrLED1()->strip()->setBrightness(mediumBright);
    pd.adrLED2()->strip()->setBrightness(mediumBright);
     pd.adrLED1()->chase2RGB(0,200,155, 0,255,0, N_LEDS/4, 10, -1);
    pd.adrLED2()->bullet2RGB(0,255,0, 0,255,0, 1, 17, -1);
    pd.adrLED2()->bullet2RGB(0,255,0, 0,255,0, 1, 16, -1);
    pd.adrLED2()->bullet2RGB(0,255,0, 0,255,0, 1, 15, -1);
    pd.adrLED2()->bullet2RGB(0,255,0, 0,255,0, 1, 14, -1);
    pd.adrLED2()->bullet2RGB(0,255,0, 0,255,0, 1, 13, -1);
    pd.adrLED2()->bullet2RGB(0,255,0, 0,255,0, 1, 12, -1);
    pd.adrLED2()->bullet2RGB(0,255,0, 0,255,0, 1, 11, -1);
    pd.adrLED2()->bullet2RGB(0,255,0, 0,200,0, 1, 10, -1);
    pd.adrLED2()->bullet2RGB(0,200,0, 0,200,0, 1, 9, -1);
    pd.adrLED2()->bullet2RGB(0,200,0, 0,200,0, 1, 8, -1);
    pd.adrLED2()->bullet2RGB(0,150,0, 0,150,0, 1, 7, -1);
    pd.adrLED2()->bullet2RGB(0,150,0, 0,150,0, 1, 6, -1);
    pd.adrLED2()->bullet2RGB(0,100,0, 0,100,0, 1, 5, -1);
    pd.adrLED2()->bullet2RGB(0,100,0, 0,100,0, 1, 4, -1);
    pd.adrLED2()->bullet2RGB(0,100,0, 0,100,0, 1, 3, -1);
    pd.adrLED2()->bullet2RGB(0,100,0, 0,100,0, 1, 3, -1);
    pd.adrLED2()->bullet2RGB(0,100,0, 0,100,0, 1, 3, -1);
    pd.adrLED2()->bullet2RGB(0,100,0, 0,100,0, 1, 3, -1);
    pd.adrLED2()->bullet2RGB(0,100,0, 0,50,0, 1, 2, -1);
    pd.adrLED2()->bullet2RGB(0,50,0, 0,50,0, 1, 1, -1);
    pd.adrLED2()->bullet2RGB(0,50,0, 0,50,0, 1, 1, -1);
    pd.adrLED2()->bullet2RGB(0,50,0, 0,50,0, 1, 1, -1);
    pd.adrLED2()->bullet2RGB(0,50,0, 0,50,0, 1, 1, -1);
    pd.adrLED2()->bullet2RGB(0,50,0, 0,50,0, 1, 1, -1);
    pd.adrLED2()->bullet2RGB(0,50,0, 0,25,0, 1, 1, -1);
    pd.adrLED2()->bullet2RGB(0,25,0, 0,25,0, 1, 1, -1);
    pd.adrLED2()->bullet2RGB(0,25,0, 0,10,0, 1, 1, -1);
    pd.adrLED2()->bullet2RGB(0,10,0, 0,0,0, 1, 1, -1);
  }
}
