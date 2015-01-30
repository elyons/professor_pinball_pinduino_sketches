/*
  pinduino.cpp - Library for pinduino shield for Arduinos.
  Created by Eric Lyons and Wes Sparks, 2015.
  Released into the public domain.
  Play more pinball!
*/

#include <Arduino.h>
#include <pinduino.h>
#include <RGBStrip.h>;

RGBStrip* RGB1;
RGBStrip* RGB2;
RGBStrip* RGB3;
RGBStrip* RGB4;

pinduino::pinduino()
{
 RGB1 = new RGBStrip(11,12,13); // pins 11,12,13 
 RGB2 = new RGBStrip(8,9,10); // pins 8,9,10 
 RGB3 = new RGBStrip(5,6,7); // pins 5,6,7 
 RGB4 = new RGBStrip(2,3,4); // pins 2,3,4 
}

RGBStrip* pinduino::RGBStrip1 ()
{
 return RGB1;
}

RGBStrip* pinduino::RGBStrip2 ()
{
 return RGB2;
}

RGBStrip* pinduino::RGBStrip3 ()
{
 return RGB3;
}

RGBStrip* pinduino::RGBStrip4 ()
{
 return RGB4;
}

void pinduino::testRGBStrip(RGBStrip* strip)
{
  strip->set("red");
  delay(1000);
  strip->set("green");
  delay(1000);
  strip->set("blue");
  delay(1000);
  strip->set("yellow");
  delay(1000);
  strip->set("purple");
  delay(1000);
  strip->set("cyan");
  delay(1000);
  strip->set("white");
  delay(1000);
  strip->fadeIn("red",1000);
  delay(100);
  strip->fadeOut(1000);
  delay(500);
  strip->fadeIn("green",1000);
  delay(100);
  strip->fadeOut(1000);
  delay(500);
  strip->fadeIn("blue",1000);
  delay(100);
  strip->fadeOut(1000);
  delay(500);
  strip->fadeIn("yellow",1000);
  delay(100);
  strip->fadeOut(1000);
  delay(500);
  strip->fadeIn("purple",1000);
  delay(100);
  strip->fadeOut(1000);
  delay(500);
  strip->fadeIn("cyan",1000);
  delay(100);
  strip->fadeOut(1000);
  delay(500);
  strip->fadeIn("white",1000);
  delay(100);
  strip->fadeOut(1000);
  delay(500);
}

void pinduino::testRGBStrip1()
{
  testRGBStrip(RGB1);
}

void pinduino::testRGBStrip2()
{
  testRGBStrip(RGB2);
}

void pinduino::testRGBStrip3()
{
  testRGBStrip(RGB3);
}

void pinduino::testRGBStrip4()
{
  testRGBStrip(RGB4);
}

