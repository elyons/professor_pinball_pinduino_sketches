/*
  pinduino.h - Library for pinduino shield for Arduinos.
  Created by Eric Lyons and Wes Sparks, 2015.
  Released into the public domain.
  Play more pinball!
*/
#ifndef pinduino_h
#define pinduino_h

#include "Arduino.h"
#include <RGBStrip.h>
class pinduino
{
  protected:

  public:
    //Constructor
    pinduino();

    //functions for controlling 12V RGB strips
    RGBStrip* RGBStrip1();
    RGBStrip* RGBStrip2();
    RGBStrip* RGBStrip3();
    RGBStrip* RGBStrip4();
    void X1(); // pin A15
    void X2(); // pin A14
    void X3(); // pin A13

    void testRGBStrip(RGBStrip* strip);
    void testRGBStrip1();
    void testRGBStrip2();
    void testRGBStrip3();
    void testRGBStrip4();
     
  private:
    int _pin;
};



#endif
