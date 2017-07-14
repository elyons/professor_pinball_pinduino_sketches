#include <pinduino.h>


int aLEDNum1 = 100;
int aLEDNum2 = 10;
int aLEDNum3 = 10;

//pinduino pd(aLEDNum1, aLEDNum2, aLEDNum3);

pinduino pd(aLEDNum1, aLEDNum2, aLEDNum3, "Nano");

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting");
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.pinState()->reset();
//  delay(1000);
}


int i =0;
void loop()
{
  Serial.println(i);
  i=i+1;
//  pd.pinState()->update();
//  pd.testAdrLED(pd.adrLED1());
   pd.adrLED1()->color("green",255);
   pd.adrLED2()->color("green",255);
   delay(1000);
   pd.adrLED1()->clear();
   pd.adrLED2()->clear();
   delay(1000);
}
