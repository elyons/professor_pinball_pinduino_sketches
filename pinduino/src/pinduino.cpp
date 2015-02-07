/*
  pinduino.cpp - Library for pinduino shield for Arduinos.
  Created by Eric Lyons and Wes Sparks, 2015.
  Released into the public domain.
  Play more pinball!
*/

#include <Arduino.h>
#include <pinduino.h>
#include <RGBStrip.h>
#include <AddressableStrip.h>
#include <pinduinoPins.h>

pinduino::pinduino(int aledNum1, int aledNum2, int aledNum3)
{
	_pinState = new pinduinoPins();

	RGB1 = new RGBStrip(11,12,13); // pins 11,12,13 
 	RGB2 = new RGBStrip(8,9,10); // pins 8,9,10 
 	RGB3 = new RGBStrip(5,6,7); // pins 5,6,7 
 	RGB4 = new RGBStrip(2,3,4); // pins 2,3,4 

 	ALED1 = new AddressableStrip(aledNum1, A15, _pinState);
 	ALED2 = new AddressableStrip(aledNum2, A14, _pinState);
 	ALED3 = new AddressableStrip(aledNum3, A13, _pinState);
}

pinduinoPins* pinduino::pinState()
{
  return _pinState;
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
  strip->chase("green", 10, 10, 1);
  strip->chase("blue", 10, 10, -1);
  strip->chase("red", 10, 10, 1);
  strip->chase("white", 10, 10, -1);
  strip->chase2Color("red", "green", 10, 10, 1);
  strip->chase2Color("green", "blue", 10, 10, -1);
  strip->chase2Color("blue", "blue", 10, 10, 1);
  strip->chase2Color("blue", "white", 10, 10, -1);
  strip->chase2Color("white", "red", 10, 10, 1);
  strip->chase2Color("red", "white", 10, 10, -1);
  strip->chase2Color("white", "green", 10, 10, 1);
  strip->chase2Color("green", "white", 10, 10, -1);
  strip->chase2Color("white", "blue", 10, 10, 1);
  strip->chase2Color("blue", "white", 10, 10, -1);
  strip->spreadInFromPoint (strip->strip()->numPixels()/2, "red", 1000);
  strip->fadeOut(500);
  strip->spreadInFromPoint (strip->strip()->numPixels()/2, "green", 1000);
  strip->fadeOut(500);
  strip->spreadInFromPoint (strip->strip()->numPixels()/2, "blue", 1000);
  strip->fadeOut(500);
  strip->spreadInFromPoint (strip->strip()->numPixels()/2, "white", 1000);
  strip->fadeOut(500);
  strip->spreadInFromPoint2Color (strip->strip()->numPixels()/2, "red", "green", 1000);
  strip->fadeOut(500);
  strip->spreadInFromPoint2Color (strip->strip()->numPixels()/2, "green", "blue", 1000);
  strip->fadeOut(500);
  strip->spreadInFromPoint2Color (strip->strip()->numPixels()/2, "blue", "red", 1000);
  strip->fadeOut(500);
  strip->spreadInFromPoint2Color (strip->strip()->numPixels()/2, "white", "blue", 1000);
  strip->fadeOut(500);
  strip->spreadInFromPoint2Color (strip->strip()->numPixels()/2, "blue", "white", 1000);
  strip->fadeOut(500);
  strip->spreadInFromPoint2Color (strip->strip()->numPixels()/2, "white", "red", 1000);
  strip->fadeOut(500);
  strip->spreadInFromPoint2Color (strip->strip()->numPixels()/2, "red", "white", 1000);
  strip->fadeOut(500);
  strip->spreadInFromPoint2Color (strip->strip()->numPixels()/2, "white", "green", 1000);
  strip->fadeOut(500);
  strip->spreadInFromPoint2Color (strip->strip()->numPixels()/2, "green", "white", 1000);
  strip->fadeOut(500);
  strip->spreadInFromPoint (strip->strip()->numPixels()/2, "red", 1000);  
  strip->spreadOutFromPoint (strip->strip()->numPixels()/2, 1000);  
  strip->spreadInFromPoint (strip->strip()->numPixels()/2, "green", 1000);  
  strip->spreadOutToPoint (strip->strip()->numPixels()/2, 1000);  
  strip->spreadInFromPoint (strip->strip()->numPixels()/2, "blue", 1000);  
  strip->spreadOutToPoint (strip->strip()->numPixels()/2, 1000);  
  strip->spreadInFromPoint (strip->strip()->numPixels()/2, "white", 1000);  
  strip->spreadOutToPoint (strip->strip()->numPixels()/2, 1000);  
  for (int i = 0; i < 7; i = i + 1) {
    strip->explosion (random(100), "red", random(10)+5);
  }
  strip->rainbow(10);
  strip->fadeOut(1000);
  delay(500);
  strip->rainbowCycle(10);
  strip->fadeOut(1000);
  delay(500);

  strip->color("red", 255);
  delay(2000);
  strip->color("green", 255);
  delay(2000);
  strip->color("blue", 255);
  delay(2000);
  strip->color("yellow", 255);
  delay(2000);
  strip->color("cyan", 255);
  delay(2000);
  strip->color("purple", 255);
  delay(2000);
  strip->color("white", 255);
  delay(2000);
  strip->color("orange", 255);
  delay(2000);
  strip->color("lime", 255);
  delay(2000);
  strip->color("sky", 255);
  delay(2000);
  strip->color("mint", 255);
  delay(2000);
  strip->color("magenta", 255);
  delay(2000);
  strip->color("lavender", 255);
  delay(2000);
  strip->fadeOut(100);
  delay(500);
  strip->fadeIn("Red", 2000);
  strip->fadeOut(2000);
  delay(500);
  strip->fadeIn("blue", 2000);
  delay(500);
  strip->fadeOut(2000);
  delay(500);
  strip->fadeIn("green",2000);
  delay(500);
  strip->fadeOut(2000);
  delay(500);
  strip->fadeIn("white",2000);
  delay(500);
  strip->fadeOut(2000);
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
