/*
  pinduino.h - Library for pinduino shield for Arduinos.
  Created by Eric Lyons and Wes Sparks, 2015.
  Released into the public domain.
  Play more pinball!
*/
#ifndef pinduino_h
#define pinduino_h

#include <Arduino.h>
#include <RGBStrip.h>
#include <AddressableStrip.h>
class pinduino
{
  protected:

  public:
    //Constructor
    pinduino(int num1, int num2, int num3);

    //functions for controlling 12V RGB strips
    RGBStrip* rgbLED1();
    RGBStrip* rgbLED2();
    RGBStrip* rgbLED3();
    RGBStrip* rgbLED4();

    //functions for controlling 5V Addressable LED strips
    AddressableStrip* adrLED1();    
    AddressableStrip* adrLED2();    
    AddressableStrip* adrLED3();    

    void testRGBStrip(RGBStrip* strip);
    void testRGBStrip1();
    void testRGBStrip2();
    void testRGBStrip3();
    void testRGBStrip4();

    void testAdrLED(AddressableStrip* strip);
    void testAdrLED1();
    void testAdrLED2();
    void testAdrLED3();
    void testAdrLED4();
     
  private:
    int _pin;
    RGBStrip* RGB1;
    RGBStrip* RGB2;
    RGBStrip* RGB3;
    RGBStrip* RGB4;

    AddressableStrip* ALED1;
    AddressableStrip* ALED2;
    AddressableStrip* ALED3;
};



#endif
