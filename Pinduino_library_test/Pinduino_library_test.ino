#include <pinduino.h>


int aLEDNum1 = 300;
int aLEDNum2 = 240;
int aLEDNum3 = 240;

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
  pd.pinState()->update();
  pd.pinState()->print();
  
  pd.rgbLED1()->set("red");
  pd.rgbLED2()->set("red");
  pd.rgbLED3()->set("red");
  pd.rgbLED4()->set("red");
  delay(2000);
  pd.rgbLED1()->set("green");
  pd.rgbLED2()->set("green");
  pd.rgbLED3()->set("green");
  pd.rgbLED4()->set("green");
  delay(2000);
  pd.rgbLED1()->set("blue");
  pd.rgbLED2()->set("blue");
  pd.rgbLED3()->set("blue");
  pd.rgbLED4()->set("blue");
  delay(2000);
  pd.rgbLED1()->set("white");
  pd.rgbLED2()->set("white");
  pd.rgbLED3()->set("white");
  pd.rgbLED4()->set("white");
  delay(2000);
  pd.adrLED1()->color("red",255);
  pd.adrLED2()->color("red",255);
  pd.adrLED3()->color("red",255);
  delay(2000);
  pd.adrLED1()->color("green",255);
  pd.adrLED2()->color("green",255);
  pd.adrLED3()->color("green",255);
  delay(2000);
  pd.adrLED1()->color("blue",255);
  pd.adrLED2()->color("blue",255);
  pd.adrLED3()->color("blue",255);
  delay(2000);
//    
//  pd.adrLED1()->color("white",255);
//  delay(2000);
//  pd.adrLED1()->color("white",250);
//  delay(2000);
//  pd.adrLED1()->color("white",200);
//  delay(2000);
//  pd.adrLED1()->color("white",150);
//  delay(2000);
//  pd.adrLED1()->color("white",100);
//  delay(2000);
//  pd.adrLED1()->color("white",50);
//  delay(2000);

}
