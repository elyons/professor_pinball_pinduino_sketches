//Eric Lyons2019
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3
//Uses pinduino library

#include <pinduino.h>

int aLEDNum1 = 68;  // GI lights
int aLEDNum2 = 48;  // side rails

String color1 = "green";
String color2 = "blue";
String color3 = "red";

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

void loop(){
//   Print the pin states out to serial 
//  pd.pinState()->print();
 pd.adrLED1()->fadeColor2Color("yellow", "red", 1000);
 delay(500);
 pd.adrLED1()->fadeColor2Color("red", "purple", 1000);
 delay(500);
 pd.adrLED1()->fadeColor2Color("purple", "blue", 1000);
 delay(500);
 pd.adrLED1()->fadeColor2Color("blue", "green", 1000);
 delay(500);
 pd.adrLED1()->bullet("green", "yellow", 8,  4,  -1);
 pd.adrLED1()->bullet("green", "blue", 8,  4,  1);
 pd.adrLED1()->bullet("green", "red", 8,  4,  -1);
 pd.adrLED1()->bullet("green", "yellow", 8,  4,  1);

 pd.adrLED1()->fadeColor2Color("green", "yellow", 1000);
 delay(500);

}
