#include <pinduino.h>


int aLEDNum1 = 300;
int aLEDNum2 = 300;
int aLEDNum3 = 300;

pinduino pd(aLEDNum1, aLEDNum2, aLEDNum3);
void setup()
{
  Serial.begin(115200);
  pd.adrLED1()->clear();
  pd.adrLED2()->clear();
  pd.adrLED3()->clear();
  pd.pinState()->reset();
//  Serial.println("1");
//  delay(1000);
}


void loop()
{
//  pd.pinState()->update();
  pd.testAdrLED(pd.adrLED1());
}
