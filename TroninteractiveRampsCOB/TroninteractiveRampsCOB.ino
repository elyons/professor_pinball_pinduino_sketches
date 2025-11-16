//Eric Lyons 2023
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3
//Uses pinduino library


#include <pinduino.h>
//blue light cycle,  ramp entrance on left; exit on right
#int aLEDNum1 = 42; // 70mm segments
int aLEDNum1 = 59; // 50mm segments

// yellow light cycle, ramp entrance on right; exit on left
#int aLEDNum2 = 36; // 70mm segments
int aLEDNum2 = 50; // 50mm segments

int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");


int bg_chase_on = 1;
int disc_motor = 0; // flag for sensing disc motor
int disc_motor_wait = 5000;//time to wait with no disc motor activity to reset disc_motor_flag
int zuse = 0; // flag for sensing zuse
int zuse_wait = 500;//time to wait with no zuse activity to reset zuse flag
unsigned long timeLastEvent = 0; // time last event was last triggered
unsigned long discEvent = 0; // time since disc lights last went
int startChaseWaitTime = 10000;//Amount of time to wait before chase lights start up again 1000 == 1 second
int bgTime = 30000; // time till lights are set to background color
String led1Color = "red";
String led2Color = "blue";


void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
  pd.adrLED1()->strip()->updateType("RGB");
  pd.adrLED2()->strip()->updateType("RGB");
}

void loop(){
  for (int i=0; i<50; i=i+1) {     
    pd.pinState()->update();
  }
//   Print the pin states out to serial 
//  pd.pinState()->print();
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) {bg_chase_on=1;}
  if (millis()-timeLastEvent > bgTime) {
    led1Color="orange";
    led2Color="blue";
  }
  if (!pd.pinState()->J6(6) && millis()-timeLastEvent > disc_motor_wait) { disc_motor=0;}
  if ( millis()-timeLastEvent > zuse_wait) { zuse=0;}
  if ( millis()-timeLastEvent > 5000){pd.pinState()->reset();} // reset pin states if nothing has been triggered for 2 seconds
  if (bg_chase_on){backgroundChase();}

}

void checkPinStates(){
  int trigger =0;
  if (pd.pinState()->J7(2)) // zen
    {
//       bg_chase_on = 0;
//       timeLastEvent = millis();
    }
  if ( pd.pinState()->J6(2) )
    { // flashes if quora his hit and nothing else
      // let monitor for a bit longer to see if something else goes 
      // used to sense disc
      for (int i=0; i<1000; i=i+1) {     
        pd.pinState()->update();
      }
    }
  if (pd.pinState()->J7(3) ) { // Video Game Scoop
//    pd.adrLED1()->bullet2Color("black", "blue", 16, 0, 1);
//    pd.adrLED1()->fadeOut(10); pd.adrLED2()->fadeOut(10);
//    pd.adrLED2()->bullet2Color("orange", "red", 10, 10, 1);
//    pd.fadeInAllAdrRGB(100,0,100, 50);
    pd.adrLED1()->colorRGB(50,0,100);
    pd.adrLED2()->colorRGB(50,0,100);
    delay(300);
    pd.fadeOutAllAdr(50);
    trigger = 1;
  }

  if ( pd.pinState()->J6(1) & pd.pinState()->J7(8) ) { // light cycle
    pd.adrLED1()->fadeOut(10); pd.adrLED2()->fadeOut(10);
//    pd.adrLED2()->bullet2Color("yellow", "yellow", 8,20, 1);
//    pd.adrLED1()->bullet2Color("blue", "blue", 8, 20, 1);
    pd.chaseAllAdr2RGB(200,200,0, 100,100, 0, 10, 30, 1);
    led1Color="yellow";
    led2Color="blue";
    trigger =1;    
  }

  if (  pd.pinState()->J7(4) && pd.pinState()->J7(9) ) { // light cycle
    pd.adrLED1()->fadeOut(10); pd.adrLED2()->fadeOut(10);
//    pd.adrLED2()->bullet2Color("yellow", "yellow", 8, 10, 1);
//    pd.adrLED1()->bullet2Color("blue", "blue", 8, 10, 1);
    pd.chaseAllAdr2RGB(0,0,200, 0,0,100, 10, 30, 1);
    led1Color="blue";
    led2Color="yellow";

    trigger =1;    
  }

  if ( !zuse && pd.pinState()->J6(4) && ! pd.pinState()->J7(4)){// zuse
    pd.adrLED1()->fadeOut(10); pd.adrLED2()->fadeOut(10);
    pd.chaseAllAdr2RGBFromPoint (20, 200,200,255, 0,0,255, 10, 10);
    led1Color="blue";
    led2Color="sky";
    trigger =1;
    zuse = 1;
   }
   

//   if (pd.pinState()->J6(2) && pd.pinState()->J6(3) && pd.pinState()->J6(7) && pd.pinState()->J6(8) 
   if (pd.pinState()->J6(2) && pd.pinState()->J6(3) 
     //&& ! pd.pinState()->J7(4) && ! pd.pinState()->J7(8) && ! pd.pinState()->J7(9) 
     ) {// disc open and hit
      pd.adrLED1()->fadeOut(10); pd.adrLED2()->fadeOut(10);
      pd.adrLED1()->spreadInFromPoint(aLEDNum1, "orange", 30);
      pd.adrLED2()->spreadInFromPoint(aLEDNum2, "blue", 30);
      delay (400);
      pd.fadeOutAllAdr(100);
      led1Color="red";
      led2Color="orange";
      trigger = 1;
    } 
  
  if ( pd.pinState()->J6(5) ){ // recognizer
    pd.adrLED1()->fadeOut(10); pd.adrLED2()->fadeOut(10);
    pd.chaseAllAdr2RGBFromPoint (20, 255,200,0, 255,0,0, 10, 10);
//    pd.chaseAllAdr2Color("red", "red", 5, 30, 1);
    led1Color="red";
    led2Color="red";
    delay(300);
  }
  
  if ( pd.pinState()->J6(6) && !disc_motor){ // Disc motor
    //want this to run when the disc starts up
    pd.adrLED1()->fadeOut(10); pd.adrLED2()->fadeOut(10);
    pd.adrLED1()->spreadInFromPoint(aLEDNum1/2, "orange", 30);
    pd.adrLED2()->spreadInFromPoint(aLEDNum2/2, "red", 30);
    delay (300);
    pd.fadeOutAllAdr(50);
    disc_motor=1;
    led1Color="orange";
    led2Color="red";
   trigger = 1; 
  }

  if ( pd.pinState()->J6(2) && !pd.pinState()->J6(3) && ! pd.pinState()->J6(5)){//quora
    pd.adrLED1()->fadeOut(10); pd.adrLED2()->fadeOut(10);
//    pd.chaseAllAdr2RGB(0,255,0, 0,25,0, 10, 30, 1);
    pd.chaseAllAdr2RGBFromPoint (20, 0,255,0, 0,100,0, 10, 10);
    trigger = 1; 
    led1Color="green";
    led2Color="blue";

  }
  if ( pd.pinState()->J6(7) ){ //RED disc left (flashers under disc)
    led1Color="orange";
    led2Color="orange";
    discEvent = millis();   
  }
  if ( pd.pinState()->J6(8) ){ //RED disc right (flashers under disc)
    led1Color="red";
    led2Color="red";

    discEvent = millis();   
  }
  
//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   pd.pinState()->reset();
   pd.adrLED1()->fadeOut(10); pd.adrLED2()->fadeOut(10);
   trigger =0;
   bg_chase_on = 0;
   timeLastEvent = millis();
  }
}



void backgroundChase() {
    //Uncomment for data stream effect in attact mode
    pd.adrLED1()->dataStream(led1Color,50, 15, 1); 
    pd.adrLED2()->dataStream(led2Color,50, 15, 1);
    
    //Uncomment for sparkle effect in attract mode
    //pd.adrLED1()->sparkle("blue", 100,5);
    //pd.adrLED2()->sparkle("blue", 100,5);

    if (random(1000) == 0) {
      pd.adrLED1()->fadeOut(10); pd.adrLED2()->fadeOut(10);
      pd.adrLED2()->bullet2Color("yellow", "orange", 30, 20, 1);
      pd.adrLED1()->bullet2Color("sky", "blue", 30, 20, 1);
    }
  } 
