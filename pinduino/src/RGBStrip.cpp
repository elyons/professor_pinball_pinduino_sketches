#include "Arduino.h"
#include "RGBStrip.h"

int _r;
int _g;
int _b;


RGBStrip::RGBStrip(int pin1, int pin2, int pin3)
{
  //Blue channel
  pinMode(pin1, OUTPUT);
  _pin1 = pin1;

  //Red channel
  pinMode(pin2, OUTPUT);
  _pin2 = pin2;

  //Green channel
  pinMode(pin3, OUTPUT);
  _pin3 = pin3;

  clear();
}


void RGBStrip::clear()
{
  digitalWrite(_pin1, 0);
  digitalWrite(_pin2, 0);
  digitalWrite(_pin3, 0);
}

void set_color_vars(int r, int g, int b)
{
 _r = r;
 _g = g;
 _b = b;
}

void color2RGB(String color, int &r, int &g, int &b)
{
  r=0;
  g=0;
  b=0;
  if (color.equalsIgnoreCase("red"))
  {
    r=1;
  }
  else if (color.equalsIgnoreCase("green"))
  {
    g=1;
  }
  else if (color.equalsIgnoreCase("blue"))
  {
    b=1;
  }
  else if (color.equalsIgnoreCase("yellow"))
  {
    r=1;
    g=1;
  }
  else if (color.equalsIgnoreCase("purple"))
  {
    r=1;
    b=1;
  }
  else if (color.equalsIgnoreCase("cyan"))
  {
    b=1;
    g=1;
  }
  else if (color.equalsIgnoreCase("white"))
  {
    r=1;
    g=1;
    b=1;
  }
 set_color_vars(r, g, b);
}

void RGBStrip::set(String color)
{
  int r = 0;
  int g = 0;
  int b = 0;
  color2RGB(color, r, g, b);
  
  digitalWrite(_pin1, b);
  digitalWrite(_pin2, r);
  digitalWrite(_pin3, g);
}

void RGBStrip::fadeIn(String color, float time)
{
  int r = 0;
  int g = 0;
  int b = 0;
  time = time/256;
  color2RGB(color, r, g, b);

  for (int i = 0; i < 256; i++) { 
    analogWrite(_pin1, b*i);
    analogWrite(_pin2, r*i);
    analogWrite(_pin3, g*i);
    delay(time);
  } 
}

void RGBStrip::fadeOut(float time)
{
  int r = _r;
  int g = _g;
  int b = _b;
  time = time/256;
  for (int i = 255; i > -1; i--) { 
    analogWrite(_pin1, b*i);
    analogWrite(_pin2, r*i);
    analogWrite(_pin3, g*i);
    delay(time);
  } 

}

