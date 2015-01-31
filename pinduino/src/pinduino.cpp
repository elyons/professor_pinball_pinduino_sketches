/*
  pinduino.cpp - Library for pinduino shield for Arduinos.
  Created by Eric Lyons and Wes Sparks, 2015.
  Released into the public domain.
  Play more pinball!
*/

#include <Arduino.h>
#include <pinduino.h>
#include <RGBStrip.h>;
#include <AddressableStrip.h>


//Note: are these being released as global vars into the parent program?
//RGBStrip* RGB1;
//RGBStrip* RGB2;
//RGBStrip* RGB3;
//RGBStrip* RGB4;

//AddressableStrip* ALED1;
//AddressableStrip* ALED2;
//AddressableStrip* ALED3;


pinduino::pinduino(int aledNum1, int aledNum2, int aledNum3)
{
 RGB1 = new RGBStrip(11,12,13); // pins 11,12,13 
 RGB2 = new RGBStrip(8,9,10); // pins 8,9,10 
 RGB3 = new RGBStrip(5,6,7); // pins 5,6,7 
 RGB4 = new RGBStrip(2,3,4); // pins 2,3,4 

 ALED1 = new AddressableStrip(aledNum1, A15);
 ALED2 = new AddressableStrip(aledNum2, A14);
 ALED3 = new AddressableStrip(aledNum3, A13);
}

RGBStrip* pinduino::rgbLED1 ()
{
 return RGB1;
}

RGBStrip* pinduino::rgbLED2 ()
{
 return RGB2;
}

RGBStrip* pinduino::rgbLED3 ()
{
 return RGB3;
}

RGBStrip* pinduino::rgbLED4 ()
{
 return RGB4;
}

AddressableStrip* pinduino::adrLED1 ()
{
 return ALED1;
}

AddressableStrip* pinduino::adrLED2 ()
{
 return ALED2;
}

AddressableStrip* pinduino::adrLED3 ()
{
 return ALED3;
}

void pinduino::testRGBStrip(RGBStrip* strip)
{
  strip->set("red");
  delay(300);
  strip->set("green");
  delay(300);
  strip->set("blue");
  delay(300);
  strip->set("yellow");
  delay(300);
  strip->set("purple");
  delay(300);
  strip->set("cyan");
  delay(300);
  strip->set("white");
  delay(300);
  strip->fadeIn("red",300);
  delay(100);
  strip->fadeOut(300);
  delay(500);
  strip->fadeIn("green",300);
  delay(100);
  strip->fadeOut(300);
  delay(500);
  strip->fadeIn("blue",300);
  delay(100);
  strip->fadeOut(300);
  delay(500);
  strip->fadeIn("yellow",300);
  delay(100);
  strip->fadeOut(300);
  delay(500);
  strip->fadeIn("purple",300);
  delay(100);
  strip->fadeOut(300);
  delay(500);
  strip->fadeIn("cyan",300);
  delay(100);
  strip->fadeOut(300);
  delay(500);
  strip->fadeIn("white",300);
  delay(100);
  strip->fadeOut(300);
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
void pinduino::testAdrLED (AddressableStrip* strip)
{
  strip->chase2color("orange", "purple", 10, 10, 1);
  strip->chase2color("purple", "green", 10, 10, -1);
  strip->color("red", 255);
  delay(500);
  strip->color("green", 255);
  delay(500);
  strip->color("blue", 255);
  delay(500);
  strip->color("yellow", 255);
  delay(500);
  strip->color("cyan", 255);
  delay(500);
  strip->color("purple", 255);
  delay(500);
  strip->color("white", 255);
  delay(500);
  strip->color("orange", 255);
  delay(500);
  strip->color("lime", 255);
  delay(500);
  strip->color("sky", 255);
  delay(500);
  strip->color("mint", 255);
  delay(500);
  strip->color("magenta", 255);
  delay(500);
  strip->color("lavender", 255);
  delay(500);
  strip->fadeOut(100);
  delay(500);
  strip->fadeIn("Red", 300);
  strip->fadeOut(300);
  delay(500);
  strip->fadeIn("blue", 300);
  delay(500);
  strip->fadeOut(300);
  delay(500);
  strip->fadeIn("green",300);
  delay(500);
  strip->fadeOut(300);
  delay(500);
}

void pinduino::testAdrLED1()
{
  testAdrLED(ALED1);
}

void pinduino::testAdrLED2()
{
  testAdrLED(ALED2);
}

void pinduino::testAdrLED3()
{
  testAdrLED(ALED3);
}
