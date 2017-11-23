//Eric Lyons 2015
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3
//Uses pinduino library


#include <pinduino.h>
int aLEDNum1 = 96;
int aLEDNum2 = 81;
int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");


int bg_chase_on = 1;
int disc_motor = 0; // flag for sensing disc motor
int disc_motor_wait = 5000;//time to wait with no disc motor activity to reset disc_motor_flag
int zuse = 0; // flag for sensing zuse
int zuse_wait = 500;//time to wait with no zuse activity to reset zuse flag
unsigned long timeLastEvent = 0; // time last event was last triggered
unsigned long discEvent = 0; // time since disc lights last went
int startChaseWaitTime = 5000;//Amount of time to wait before chase lights start up again 1000 == 1 second
int bgTime = 10000; // time till lights are set to background color
String bgColor = "blue";


void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
}

void loop(){
  for (int i=0; i<500; i=i+1) {     
    pd.pinState()->update();
  }
//   Print the pin states out to serial 
//  pd.pinState()->print();
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) {bg_chase_on=1;}
//  if (millis()-timeLastEvent > bgTime) {
//    {bgColor="blue";}
//  }
  if (!pd.pinState()->J6(6) && millis()-timeLastEvent > disc_motor_wait) { disc_motor=0;}
  if (!pd.pinState()->J6(7) && !pd.pinState()->J6(8) && millis()-discEvent > bgTime) {bgColor="blue";}
  if ( millis()-timeLastEvent > zuse_wait) { zuse=0;}
  if ( millis()-timeLastEvent > 5000){pd.pinState()->reset();} // reset pin states if nothing has been triggered for 2 seconds
  if (bg_chase_on){backgroundChase();}

}

void checkPinStates(){
  int trigger =0;

  if ( pd.pinState()->J6(2) )
    { // flashes if quora his hit and nothing else
      // let monitor for a bit longer to see if something else goes 
      // used to sense disc
      for (int i=0; i<1000; i=i+1) {     
        pd.pinState()->update();
      }
    }
  if (pd.pinState()->J7(3) ) { // Video Game
//    pd.adrLED1()->bullet2Color("black", "blue", 16, 0, 1);
    pd.adrLED1()->fadeOut(10);
    pd.adrLED2()->bullet2Color("orange", "red", 31, 0, -1);
    trigger = 1;
  }

  if ( pd.pinState()->J6(1) & pd.pinState()->J7(8) ) { // light cycle
    pd.adrLED2()->bullet2Color("yellow", "yellow", 20, 0, -1);
    pd.adrLED1()->bullet2Color("blue", "blue", 20, 0, -1);
    trigger =1;    
  }

  if (  pd.pinState()->J7(4) && pd.pinState()->J7(9) ) { // light cycle
    pd.adrLED2()->bullet2Color("yellow", "yellow", 20, 0, -1);
    pd.adrLED1()->bullet2Color("blue", "blue", 20, 0, -1);
    trigger =1;    
  }

  if ( !zuse && pd.pinState()->J6(4) && ! pd.pinState()->J7(4)){// zuse
    pd.adrLED1()->clear();
    pd.adrLED2()->clear();
    pd.chaseAllAdr2RGBFromPoint (40, 255,255,255, 0,0,255, 7, 0);
    trigger =1;
    zuse = 1;
   }
   

//   if (pd.pinState()->J6(2) && pd.pinState()->J6(3) && pd.pinState()->J6(7) && pd.pinState()->J6(8) 
   if (pd.pinState()->J6(2) && pd.pinState()->J6(3) 
     //&& ! pd.pinState()->J7(4) && ! pd.pinState()->J7(8) && ! pd.pinState()->J7(9) 
     ) {// disc open and hit
    for (int i=0; i<2; i=i+1) {     
      pd.adrLED1()->spreadInFromPoint(aLEDNum1, "orange", 1);
      pd.adrLED2()->spreadInFromPoint(aLEDNum2, "blue", 1);
      delay (1000);
      pd.fadeOutAllAdr(200);

    }    
    trigger = 1;
  } 
  
  if ( pd.pinState()->J6(5) ){ // recognizer
    pd.chaseAllAdr2Color("red", "red", 10, 0, 1);
    trigger = 1; 
  }
  
  if ( pd.pinState()->J6(6) && !disc_motor){ // Disc motor
    //want this to run when the disc starts up
    pd.adrLED1()->spreadInFromPoint(aLEDNum1, "orange", 1);
    pd.adrLED2()->spreadInFromPoint(aLEDNum2, "red", 1);
    delay (300);
    pd.fadeOutAllAdr(50);
    disc_motor=1;
    trigger = 1; 
  }

  if ( pd.pinState()->J6(2) && !pd.pinState()->J6(3) && ! pd.pinState()->J6(5)){//quora
    pd.chaseAllAdr2RGB(0,255,0, 0,25,0, 20, 0, 1);
    trigger = 1; 
  }
  if ( pd.pinState()->J6(7) ){ //RED disc left (flashers under disc)
    bgColor="orange";
    discEvent = millis();   
  }
  if ( pd.pinState()->J6(8) ){ //RED disc right (flashers under disc)
    bgColor="red";
    discEvent = millis();   
  }
  
//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   pd.pinState()->reset();
   trigger =0;
   bg_chase_on = 0;
   timeLastEvent = millis();
  }
}



void backgroundChase() {
    pd.adrLED1()->sparkle(bgColor,100,5); 
    pd.adrLED2()->sparkle(bgColor,100,5);
    if (random(1000) == 0) {
      pd.adrLED2()->bullet2Color("orange", "yellow", 50, 0, -1);
      for (int i=0; i<500; i=i+1){
        checkPinStates();
      }
      pd.adrLED1()->bullet2Color("purple", "blue", 50, 0, -1);
      for (int i=0; i<500; i=i+1){
       checkPinStates();
      }
    }
  } 

