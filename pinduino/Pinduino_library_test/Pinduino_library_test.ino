#include <pinduino.h>
int N_LEDS = 220;
//int N_LEDS = 24;
int R_START = 110;

int aLEDNum1 = N_LEDS;
int aLEDNum2 = 0;
int aLEDNum3 = 0;

pinduino pd (aLEDNum1, aLEDNum2, aLEDNum3);

void setup()
{
}

void loop()
{
// pd.testSpeakerAdrLED1();
 pd.testAdrLED1Alpha();
}

