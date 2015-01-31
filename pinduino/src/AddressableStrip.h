/*
  RGBStrip.h - Library for pinduino shield for Arduinos.
  Created by Eric Lyons and Wes Sparks, 2015.
  Released into the public domain.
  Play more pinball!
*/
#ifndef AddressableStrip_h
#define AddressableStrip_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class AddressableStrip
{
  public:
    //Constructor
    //initialize strip for appropriate data pin
    AddressableStrip(int num, int pin);

    void setNumLEDs(int num);
    int getNumLEDs();

    // Adafruit_NeoPixel (# of LEDs, Signal Pin, Refresh Rate)
    Adafruit_NeoPixel* strip();

    //functions for controlling 5V Addressable RGB strips
    //sets interal variables -- may remove if these are not used
    void setColor(String color);
    void setRGB(int r, int g, int b);

    //color the entire strip some color
    //valid colors are (case insensitive):  red, green, blue, yellow, cyan, purple, white, orange, lime, sky, mint, magenta, lavender
    void color(String color, int brightness);
    //If you want to specify by R, G, B values between 0-255
    void colorRGB(int r, int g, int b, int brightness);

    void clear();
    void fadeIn(String color, float time);
    void fadeInRGB(int r, int g, int b, float time);
    void fadeOut(float steps);
    void RGBBand(int r, int g, int b, int x, int pos);
    void chase2RGB(float r1, float g1, float b1, float r2, float g2, float b2, float span, int time, int dir);
    void chase2color(String color1, String color2, float span, int time, int dir);

  private:
    int _pin; //data pin 
    int _numLEDs = 0; // number of LEDs in strip;

    Adafruit_NeoPixel* _strip; 

    //Internal place to store previous color
    int _r;
    int _g;
    int _b;
    void setColorVars(int r, int g, int b);
    void color2RGB(String color, int &r, int &g, int &b);
};

#endif

