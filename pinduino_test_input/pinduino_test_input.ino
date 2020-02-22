#include <pinduino.h>

//Eric Lyons 2015
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.2
//Uses pinduino library

#include <pinduino.h>
int N_LEDS = 150;
int aLEDNum1 = N_LEDS;
int aLEDNum2 = N_LEDS;
int aLEDNum3 = 0;

String color1 = "blue";
String color2 = "orange";
int start = 0;
int stop = aLEDNum1;
int dir =1;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3, "Nano");

void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
}

void loop(){
  pd.adrLED1()->sparkle("red", 20);
  pd.adrLED2()->sparkle("green", 20);
//  pd.adrLED1()->chase2Color("red", "blue",N_LEDS/8, 30, -1);
//  Serial.print(dir);
//  Serial.print(" ");
//  Serial.print(start);
//  Serial.print(" ");
//  Serial.println(stop);
//  pd.adrLED1()->bullet(color1, color2, 10,20,dir,start,stop);
//  int old_start = start;
//  int old_stop = stop;
//  if (dir==1) {
//    color1=pd.adrLED1()->randomColor();
//    start=random(aLEDNum1);
//    if (start < old_stop){dir=-1;}
//  }
//  else {
//    color2 = pd.adrLED1()->randomColor();
//    stop=random(aLEDNum1);
//    if (stop > old_start){dir=1;}
//  }
//  
  
  pd.pinState()->update();
  
//   Print the pin states out to serial 
//  pd.pinState()->print();
  checkPinStates();
}

void checkPinStates(){
  int trigger =0;
  
  if ( pd.pinState()->J6(1) ){
    pd.adrLED1()->color("red",255);
    pd.adrLED2()->color("red",255);
    delay(1000);
    trigger = 1; 
  }
  if ( pd.pinState()->J6(2) ){
    pd.adrLED1()->color("green",255);
    pd.adrLED2()->color("red",255);
    delay(1000);
    trigger = 1; 
  }
  if ( pd.pinState()->J6(3) ){ 
    pd.adrLED1()->color("blue",255);
    pd.adrLED2()->color("red",255);
    delay(1000);
    trigger = 1; 
  }
  if ( pd.pinState()->J6(4) ){ 
    pd.adrLED1()->color("yellow",255);
    pd.adrLED2()->color("red",255);
    delay(1000);
    trigger =1;
  }
  if ( pd.pinState()->J6(5) ){ 
    pd.adrLED1()->color("purple",255);
    pd.adrLED2()->color("red",255);
    delay(1000);
    trigger =1;
  }
  if ( pd.pinState()->J6(6) ){ 
    pd.adrLED1()->color("cyan",255);
    pd.adrLED2()->color("red",255);
    delay(1000);
    trigger =1;
  }
  if ( pd.pinState()->J6(7) ){ 
    pd.adrLED1()->color("sky",255);
    pd.adrLED2()->color("red",255);
    delay(1000);
    trigger =1;
  }
  if ( pd.pinState()->J6(8) ){ 
    pd.adrLED1()->color("red",255);
    pd.adrLED2()->color("red",255);
    delay(1000);
    trigger =1;
  }
  if ( pd.pinState()->J7(2) ){ 
    pd.adrLED1()->color("green",255);
    pd.adrLED2()->color("red",255);
    delay(1000);
    trigger =1;
  }
  if ( pd.pinState()->J7(3) ){ 
    pd.adrLED1()->color("blue",255);
    pd.adrLED2()->color("red",255);
    delay(1000);
    trigger =1;
  }
  if ( pd.pinState()->J7(4) ){ 
    pd.adrLED1()->color("yellow",255);
    pd.adrLED2()->color("red",255);
    delay(1000);
    trigger =1;
  }
  if ( pd.pinState()->J7(6) ){ 
    pd.adrLED1()->color("orange",255);
    pd.adrLED2()->color("red",255);
    delay(1000);
    trigger =1;
  }
  if ( pd.pinState()->J7(7) ){ 
    pd.adrLED1()->color("cyan",255);
    pd.adrLED2()->color("red",255);
    delay(1000);
    trigger =1;
  }
  if ( pd.pinState()->J7(8) ){
    pd.adrLED1()->color("purple",255);
    pd.adrLED2()->color("red",255);
    delay(1000);
    trigger=1;
  }
  if ( pd.pinState()->J7(9) ){
    pd.adrLED1()->color("red",255);
    pd.adrLED2()->color("red",255);
    delay(1000);
    trigger=1;
  }
  if ( pd.pinState()->J7(10) ){ 
    pd.adrLED1()->color("green",255);
    pd.adrLED2()->color("red",255);
    delay(1000);
    trigger =1;
  }


//trigger is to take care of any cleanup after a sequence has been triggered.
  if (trigger) {
   pd.adrLED1()->clear();
   pd.pinState()->reset();
   trigger =0;
  }

//end function checkPinStates
}
