/*
  RGBStrip.h - Library for pinduino shield for Arduinos.
  Created by Eric Lyons and Wes Sparks, 2015.
  Released into the public domain.
  Play more pinball!
*/
#ifndef RGBStrip_h
#define RGBStrip_h

#include <Arduino.h>
#include <RGBStrip.h>

class RGBStrip
{
  public:
    //Constructor
    // pins 1, 2, 3 control Blue, Red, Green channels, respectively
    RGBStrip(int pin1, int pin2, int pin3);

    //functions for controlling 12V RGB strips
    void set(String color);
    void clear();
    void fadeIn(String color, float time);
    void fadeOut(float time);

  private:
    int _pin1;
    int _pin2;
    int _pin3;
};

#endif

