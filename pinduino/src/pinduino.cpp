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
	
	ALED1->setNext(ALED2);
	ALED1->setPrevious(ALED3);
	ALED2->setNext(ALED3);
	ALED2->setPrevious(ALED1);
	ALED3->setNext(ALED1);
	ALED3->setPrevious(ALED2);
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


void pinduino::testSpeakerAdrLED (AddressableStrip* strip)
{
  //chase2RGBCont(float r1, float g1, float b1, float r2, float g2, float b2, float span, int time, int dir, int startLED, int endLED)
  
  // Slow Red/Blue
  strip->chase2RGBCont(255,0,0,  0,0,255, 6, 100, -1, 0, 23);
  strip->chase2RGBCont(0,0,255,  255,0,0, 6, 100, -1, 0, 23);

  strip->chase2RGBCont(255,0,0,  0,0,255, 6, 100, 1, 0, 23);
  strip->chase2RGBCont(0,0,255,  255,0,0, 6, 100, 1, 0, 23);

  // Fast Red/Blue
  strip->chase2RGBCont(255,0,0,  0,0,255, 6, 10, -1, 0, 23);
  strip->chase2RGBCont(0,0,255,  255,0,0, 6, 10, -1, 0, 23);

  strip->chase2RGBCont(255,0,0,  0,0,255, 6, 10, 1, 0, 23);
  strip->chase2RGBCont(0,0,255,  255,0,0, 6, 10, 1, 0, 23);
  
  // Fast cylon Red
  strip->chase2RGBCont(255,0,0,  255,0,0, 1, 20, -1, 0, 23);
  strip->chase2RGBCont(255,0,0,  255,0,0, 1, 20,  1, 0, 23);
  strip->chase2RGBCont(255,0,0,  255,0,0, 1, 20, -1, 0, 23);
  strip->chase2RGBCont(255,0,0,  255,0,0, 1, 20,  1, 0, 23);
  strip->chase2RGBCont(255,0,0,  255,0,0, 1, 20, -1, 0, 23);
  strip->chase2RGBCont(255,0,0,  255,0,0, 1, 20,  1, 0, 23);
  strip->chase2RGBCont(255,0,0,  255,0,0, 1, 20, -1, 0, 23);
  strip->chase2RGBCont(255,0,0,  255,0,0, 1, 20,  1, 0, 23);
  strip->chase2RGBCont(255,0,0,  255,0,0, 1, 20, -1, 0, 23);
  strip->chase2RGBCont(255,0,0,  255,0,0, 1, 20,  1, 0, 23);
  strip->chase2RGBCont(255,0,0,  255,0,0, 1, 20, -1, 0, 23);
  strip->chase2RGBCont(255,0,0,  255,0,0, 1, 20,  1, 0, 23);
  strip->chase2RGBCont(255,0,0,  255,0,0, 1, 20, -1, 0, 23);
  strip->chase2RGBCont(255,0,0,  255,0,0, 1, 20,  1, 0, 23);
  
  //Speed Up!
  strip->chase2RGBCont(255,0,0, 255,0,0, 1, 100, 1, 0, 23);
  strip->chase2RGBCont(255,0,0, 255,0,0, 1, 80, 1, 0, 23);
  strip->chase2RGBCont(255,0,0, 255,0,0, 1, 60, 1, 0, 23);
  strip->chase2RGBCont(255,0,0, 255,0,0, 1, 40, 1, 0, 23);
  strip->chase2RGBCont(255,0,0, 255,0,0, 1, 20, 1, 0, 23);
  strip->chase2RGBCont(255,0,0, 255,0,0, 1, 20, 1, 0, 23);
  strip->chase2RGBCont(255,0,0, 255,0,0, 1, 10, 1, 0, 23);
  strip->chase2RGBCont(255,0,0, 255,0,0, 1, 10, 1, 0, 23);
  strip->chase2RGBCont(255,0,0, 255,0,0, 1, 10, 1, 0, 23);
  strip->chase2RGBCont(255,0,0, 255,0,0, 1, 10, 1, 0, 23);
  strip->chase2RGBCont(255,0,0, 255,0,0, 1, 10, 1, 0, 23);
  strip->chase2RGBCont(255,0,0, 255,0,0, 1, 10, 1, 0, 23);
  strip->chase2RGBCont(255,0,0, 255,0,0, 1, 10, 1, 0, 23);
  strip->chase2RGBCont(255,0,0, 255,0,0, 1, 10, 1, 0, 23);
  strip->chase2RGBCont(255,0,0, 255,0,0, 1, 10, -1, 0, 23);
  strip->chase2RGBCont(255,0,0, 255,0,0, 1, 10, -1, 0, 23);
  strip->chase2RGBCont(255,0,0, 255,0,0, 1, 10, -1, 0, 23);
  strip->chase2RGBCont(255,0,0, 255,0,0, 1, 10, -1, 0, 23);
  strip->chase2RGBCont(255,0,0, 255,0,0, 1, 10, -1, 0, 23);
  strip->chase2RGBCont(255,0,0, 255,0,0, 1, 10, -1, 0, 23);
  strip->chase2RGBCont(255,0,0, 255,0,0, 1, 10, -1, 0, 23);
  strip->chase2RGBCont(255,0,0, 255,0,0, 1, 10, -1, 0, 23);
  strip->chase2RGBCont(255,0,0, 255,0,0, 1, 20, -1, 0, 23);
  strip->chase2RGBCont(255,0,0, 255,0,0, 1, 20, -1, 0, 23);
  strip->chase2RGBCont(255,0,0, 255,0,0, 1, 40, -1, 0, 23);
  strip->chase2RGBCont(255,0,0, 255,0,0, 1, 60, -1, 0, 23);
  strip->chase2RGBCont(255,0,0, 255,0,0, 1, 80, -1, 0, 23);
  strip->chase2RGBCont(255,0,0, 255,0,0, 1, 100, -1, 0, 23);
  strip->chase2RGBCont(255,0,0, 255,0,0, 1, 100, -1, 0, 23);
  strip->chase2RGBCont(255,0,0, 255,255,255, 1, 10, -1, 0, 23);
  strip->chase2RGBCont(255,255,255, 10,10,10, 1, 10, -1, 0, 23);

  
  
}

void pinduino::testSpeakerAdrLED1()
{
  testSpeakerAdrLED(ALED1);
  
}


void pinduino::testAdrLED (AddressableStrip* strip)
{
  strip->chase("green", 10, 10, 1);
  strip->chase("blue", 10, 10, -1);
  strip->chase("red", 10, 10, 1);
  strip->chase("white", 10, 10, -1);
  strip->chase2Color("red", "green", 10, 10, 1);
  strip->chase2Color("green", "blue", 10, 10, -1);
  strip->chase2Color("blue", "red", 10, 10, 1);
  strip->chase2Color("red", "white", 10, 10, -1);
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
  strip->spreadInFromPoint2Color (strip->strip()->numPixels()/2, "blue", "white", 1000);
  strip->fadeOut(500);
  strip->spreadInFromPoint2Color (strip->strip()->numPixels()/2, "white", "red", 1000);
  strip->fadeOut(500);
  strip->spreadInFromPoint2Color (strip->strip()->numPixels()/2, "white", "green", 1000);
  strip->fadeOut(500);
  strip->spreadInFromPoint (strip->strip()->numPixels()/2, "red", 1000);  
  strip->spreadOutFromPoint (strip->strip()->numPixels()/2, 1000);  
  strip->spreadInFromPoint (strip->strip()->numPixels()/2, "green", 1000);  
  strip->spreadOutToPoint (strip->strip()->numPixels()/2, 1000);  
  strip->spreadInFromPoint (strip->strip()->numPixels()/2, "blue", 1000);  
  strip->spreadOutToPoint (strip->strip()->numPixels()/2, 1000);  
  strip->spreadInFromPoint (strip->strip()->numPixels()/2, "white", 1000);  
  strip->spreadOutToPoint (strip->strip()->numPixels()/2, 1000);  
	strip->bullet2Color("red", "green", 20, 5, 1);
	strip->bullet2Color("green", "blue", 20, 5, -1);
	strip->bullet2Color("blue", "red", 20, 5, 1);
  for (int i = 0; i < 20; i = i + 1) {
    strip->explosion (random(strip->getNumLEDs()), "red", random(20)+5);
  }
  strip->rainbow(10);
  strip->rainbow(10);
  strip->rainbow(10);
  strip->rainbow(10);
  strip->fadeOut(1000);
  delay(500);

  strip->color("red", 255);
  delay(200);
  strip->color("green", 255);
  delay(200);
  strip->color("blue", 255);
  delay(200);
  strip->color("yellow", 255);
  delay(200);
  strip->color("cyan", 255);
  delay(200);
  strip->color("purple", 255);
  delay(200);
  strip->color("white", 255);
  delay(200);
  strip->color("orange", 255);
  delay(200);
  strip->color("lime", 255);
  delay(200);
  strip->color("sky", 255);
  delay(200);
  strip->color("mint", 255);
  delay(200);
  strip->color("magenta", 255);
  delay(200);
  strip->color("lavender", 255);
  delay(200);
  strip->fadeOut(100);
  delay(200);
  strip->fadeIn("Red", 200);
  strip->fadeOut(200);
  strip->fadeIn("blue", 200);
  strip->fadeOut(200);
  strip->fadeIn("green",200);
  strip->fadeOut(200);
  delay(200);
}

void pinduino::testAdrLEDAlpha (AddressableStrip* strip)
{
  strip->bullet("red", 10, 1, 1);
  strip->bullet("red", 10, 1, -1);
  strip->bullet("blue", 10, 1, 1);
  strip->bullet("blue", 10, 1, -1);
  strip->bullet2Color("red", "blue", 10, 1, 1);
  strip->bullet2Color("blue", "red", 10, 1, -1);
  strip->bullet2Color("blue", "white", 10, 1, 1);
  strip->bullet2Color("white", "blue", 10, 1, -1);
  strip->bullet2Color("red", "white", 10, 1, 1);
  strip->bullet2Color("white", "red", 10, 1, -1);
  strip->bullet2Color("orange", "red", 10, 1, 1);
  strip->bullet2Color("red", "orange", 10, 1, -1);
  strip->bullet2Color("white", "blue", 10, 1, 1);
  strip->bullet2Color("blue", "white", 10, 1, -1);
  
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
void pinduino::testAdrLED1Alpha()
{
  testAdrLEDAlpha(ALED1);
}

void pinduino::testAdrLED2Alpha()
{
  testAdrLEDAlpha(ALED2);
}

void pinduino::testAdrLED3Alpha()
{
  testAdrLEDAlpha(ALED3);
}

