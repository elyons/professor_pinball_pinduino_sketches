//Eric Lyons 2020
//Note to self:  Play more pinball!
//Interfaced for pinduino shield v0.3
//Uses pinduino library

#include <pinduino.h>

int N_LEDS = 196;
int aLEDNum1 = N_LEDS;
int aLEDNum2 = N_LEDS;

pinduino pd (aLEDNum1, "Nano");


void setup() {
  Serial.begin(115200);
  pd.adrLED1()->clear();
}

void loop(){
//  pd.adrLED1()->sparkle("red", 20);
//  pd.adrLED2()->sparkle("green", 20);
  pd.adrLED1()->meteorRain(0, 0, 255, 20, 100, true, 0);
//  Serial.println(1);
}
