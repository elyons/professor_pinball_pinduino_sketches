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

pinduino::pinduino()
{
	init(1,1,1, "Mega");
}


pinduino::pinduino(int aledNum1, String arduinoType)
{
	init(aledNum1, 1, 1, arduinoType);
}

pinduino::pinduino(int aledNum1, int aledNum2, String arduinoType)
{
	init(aledNum1, aledNum2, 1, arduinoType);
}

pinduino::pinduino(int aledNum1, int aledNum2, int aledNum3)
{
	init(aledNum1, aledNum2, aledNum3, "Mega");
}

pinduino::pinduino(int aledNum1, int aledNum2, int aledNum3, String arduinoType)
{
	init(aledNum1, aledNum2, aledNum3, arduinoType);
}

void pinduino::init(int aledNum1, int aledNum2, int aledNum3, String arduinoType)
{
	_pinState = new pinduinoPins(arduinoType);

  if (arduinoType=="Mega") 
	{
 		ALED1 = new AddressableStrip(aledNum1, 69, _pinState); // A15 (analog port):  Changed to a number for compiling compatibility when board is set to Nano
 		ALED2 = new AddressableStrip(aledNum2, 68, _pinState); // A14
 		ALED3 = new AddressableStrip(aledNum3, 67, _pinState); // A13
		RGB1 = new RGBStrip(11,12,13); // pins 11,12,13 
 		RGB2 = new RGBStrip(8,9,10); // pins 8,9,10 
 		RGB3 = new RGBStrip(5,6,7); // pins 5,6,7 
 		RGB4 = new RGBStrip(2,3,4); // pins 2,3,4 
	}
	else if (arduinoType == "Nano") 
	{
 		ALED1 = new AddressableStrip(aledNum1, 10, _pinState);
 		ALED2 = new AddressableStrip(aledNum2, 11, _pinState);
 		ALED3 = new AddressableStrip(aledNum3, 0, _pinState);
	}
	else
	{
		Serial.print("Unsupported Arduino board: ");
		Serial.println(arduinoType);
	}
	//I think these are never used.
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

//fade out all addressable strips
void pinduino::fadeOutAllAdr(float steps)
{
  if (steps < 1){steps=1;}
  uint8_t origBrightness1 = ALED1->strip()->getBrightness();
  uint8_t origBrightness2 = ALED2->strip()->getBrightness();
  uint8_t origBrightness3 = ALED3->strip()->getBrightness();

  float brightStep1 = origBrightness1/steps; 
  float brightStep2 = origBrightness2/steps; 
  float brightStep3 = origBrightness3/steps; 
  
  for (int i=0; i<steps; i++) {
        _pinState->update();
        int brightness1 = origBrightness1-(brightStep1+brightStep1*i);
        if (brightness1 < 1) {brightness1=1;}
        ALED1->strip()->setBrightness(brightness1);
        ALED1->strip()->show();

        int brightness2 = origBrightness2-(brightStep2+brightStep2*i);
        if (brightness2 < 1) {brightness2=1;}
        ALED2->strip()->setBrightness(brightness2);
        ALED2->strip()->show();

        int brightness3 = origBrightness1-(brightStep3+brightStep3*i);
        if (brightness3 < 1) {brightness3=1;}
        ALED3->strip()->setBrightness(brightness3);
        ALED3->strip()->show();
  }
  ALED1->clear();
  ALED2->clear();
  ALED3->clear();
}

//fade in all addressable strips
//note that strip colors must be previously set.  
//E.g.,:  ALED1->color("red", 1);  //brightness of 1
void pinduino::fadeInAllAdr(float steps)
{
  if (steps <= 0) {steps = 0.1;}
  float brightStep = 256/steps;
  for (int i = 1; i < steps; i++) {
    float brightness = brightStep*i;
    if (brightness<1) {brightness = 1;}
    _pinState->update();
    ALED1->strip()->setBrightness(brightness);
    ALED1->strip()->show();
    ALED2->strip()->setBrightness(brightness);
    ALED2->strip()->show();
    ALED3->strip()->setBrightness(brightness);
    ALED3->strip()->show();
  }
  ALED1->strip()->setBrightness(255);
  ALED1->strip()->show();
  ALED2->strip()->setBrightness(255);
  ALED2->strip()->show();
  ALED3->strip()->setBrightness(255);
  ALED3->strip()->show();

}

void pinduino::fadeAllAdrRGB2RGB(float r1, float g1, float b1, float r2, float g2, float b2, float time) {
	time = time/256;
	ALED1->colorRGB(r1, g1, b1, 250);
	ALED2->colorRGB(r1, g1, b1, 250);
	ALED3->colorRGB(r1, g1, b1, 250);
	ALED1->strip()->show();
	ALED2->strip()->show();
	ALED3->strip()->show();
	if (time < 1) {time = 0;}
	float rcs = abs(r1-r2)/256;
	if (r2 > r1){rcs=rcs*-1;}
	float gcs = abs(g1-g2)/256;
	if (g2 > g1){gcs=gcs*-1;}
	float bcs = abs(b1-b2)/256;
	if (b2 > b1){bcs=bcs*-1;}
	for (int i = 1; i < 256; i++) {
		_pinState->update();
		if (time) {delay(time);}
		float r = r1-(rcs*i);
		float g = g1-(gcs*i);
		float b = b1-(bcs*i);
		ALED1->colorRGB(r, g, b, 250);
		ALED2->colorRGB(r, g, b, 250);
		ALED3->colorRGB(r, g, b, 250);
 		ALED1->strip()->show();
		ALED2->strip()->show();
		ALED3->strip()->show();
	}
}

void pinduino::fadeAllAdrColor2Color(String color1, String color2, float time) {
 	int r1,g1,b1;
 	int r2,g2,b2;
 	ALED1->color2RGB(color1, r1, g1, b1);
	ALED1->color2RGB(color2, r2, g2, b2);
	fadeAllAdrRGB2RGB(r1, g1, b1, r2, g2, b2, time);
}

void pinduino::chaseAllAdr2RGB (float r1, float g1, float b1, float r2, float g2, float b2, float span, int time, int dir) {
	int pos;
	int numP = ALED1->strip()->numPixels();
	if (ALED2->strip()->numPixels() > numP) {numP = ALED2->strip()->numPixels();}
	if (ALED3->strip()->numPixels() > numP) {numP = ALED3->strip()->numPixels();}
	if (dir >0) {pos = numP+span;}
	else { pos = 0-span;}
	float rcs = abs(r1-r2)/(numP);
	if (r2 > r1){rcs=rcs*-1;}
	float gcs = abs(g1-g2)/(numP);
	if (g2 > g1){gcs=gcs*-1;}
	float bcs = abs(b1-b2)/(numP);
	if (b2 > b1){bcs=bcs*-1;}
	
	for (int i = 0; i < span; i++) {
	  	_pinState->update();
	  	if (pos < ALED1->strip()->numPixels()+span+1) {ALED1->RGBBand(pos, r1, g1, b1, span);}
	  	if (pos < ALED2->strip()->numPixels()+span+1) {ALED2->RGBBand(pos, r1, g1, b1, span);}
	  	if (pos < ALED3->strip()->numPixels()+span+1) {ALED3->RGBBand(pos, r1, g1, b1, span);}
	  	if (time){delay(time);}
	  	for(int j=-span; j<= span; j++) {
	  		if (pos < ALED1->strip()->numPixels()+span) {ALED1->strip()->setPixelColor(pos+j, 0,0,0);}
	  		if (pos < ALED2->strip()->numPixels()+span) {ALED2->strip()->setPixelColor(pos+j, 0,0,0);}
	  		if (pos < ALED3->strip()->numPixels()+span) {ALED3->strip()->setPixelColor(pos+j, 0,0,0);}
	  	}  
	    if (dir > 0) {pos--;}
	    else {pos++;}
	}
	for (int i = 0; i < numP; i++) {
		_pinState->update();
		float r = r1;
		float g = g1;
		float b = b1;
		if (i > span) {
			r = r1-(rcs*(i-span));
			g = g1-(gcs*(i-span));
			b = b1-(bcs*(i-span));
		}
		if (pos < ALED1->strip()->numPixels()+span+1) {ALED1->RGBBand(pos, r, g, b, span);}
		if (pos < ALED2->strip()->numPixels()+span+1) {ALED2->RGBBand(pos, r, g, b, span);}
		if (pos < ALED3->strip()->numPixels()+span+1) {ALED3->RGBBand(pos, r, g, b, span);}
		if (time){delay(time);}
		for(int j=-span; j<= span; j++) {
			if (pos < ALED1->strip()->numPixels()+span) {ALED1->strip()->setPixelColor(pos+j, 0,0,0);}
			if (pos < ALED2->strip()->numPixels()+span) {ALED2->strip()->setPixelColor(pos+j, 0,0,0);}
			if (pos < ALED3->strip()->numPixels()+span) {ALED3->strip()->setPixelColor(pos+j, 0,0,0);}
		}
		if (dir > 0) {pos--;}
		else{pos++;}
	}
	for (int i = 0; i < span; i++) {
		_pinState->update();
		if (pos < ALED1->strip()->numPixels()+span+1) {ALED1->RGBBand(pos, r2, g2, b2, span);}
		if (pos < ALED2->strip()->numPixels()+span+1) {ALED2->RGBBand(pos, r2, g2, b2, span);}
		if (pos < ALED3->strip()->numPixels()+span+1) {ALED3->RGBBand(pos, r2, g2, b2, span);}
		if (time){delay(time);}
		for(int j=-span; j<= span; j++) {
			if (pos < ALED1->strip()->numPixels()+span) {ALED1->strip()->setPixelColor(pos+j, 0,0,0);}
			if (pos < ALED2->strip()->numPixels()+span) {ALED2->strip()->setPixelColor(pos+j, 0,0,0);}
			if (pos < ALED3->strip()->numPixels()+span) {ALED3->strip()->setPixelColor(pos+j, 0,0,0);}
		}  
		if (dir > 0) {pos--;}
		else {pos++;}
	}
}

void pinduino::chaseAllAdr2Color (String color1, String color2, float span, int time, int dir){
	int r1,g1,b1;
	int r2,g2,b2;
	ALED1->color2RGB(color1, r1, g1, b1);
	ALED2->color2RGB(color2, r2, g2, b2);
  chaseAllAdr2RGB(r1, g1, b1, r2, g2, b2, span, time, dir);
}

void pinduino::chaseAllAdr2RGBFromPoint(int pos, float r1, float g1, float b1, float r2, float g2, float b2, int span, int time) {
	int numP = ALED1->strip()->numPixels();
	if (ALED2->strip()->numPixels() > numP) {numP = ALED2->strip()->numPixels();}
	if (ALED3->strip()->numPixels() > numP) {numP = ALED3->strip()->numPixels();}
	int max_pos = pos;  //max distance to edge of strip from position pos
	if (max_pos < numP-pos) {max_pos = numP-pos;}
	  //color step size
	  float rcs = abs(r1-r2)/(max_pos);
	  if (r2 > r1){rcs=rcs*-1;}
	  float gcs = abs(g1-g2)/(max_pos);
	  if (g2 > g1){gcs=gcs*-1;}
	  float bcs = abs(b1-b2)/(max_pos);
	  if (b2 > b1){bcs=bcs*-1;}
	  
	  for (int i = 0; i < max_pos; i++) {
		_pinState->update();
		float r = r1;
		float g = g1;
		float b = b1;
		r = r1-(rcs*(i));
		g = g1-(gcs*(i));
		b = b1-(bcs*(i)); 
		if (pos+i < ALED1->strip()->numPixels()+span+1) {ALED1->RGBBand(pos-i, r, g, b, span); ALED1->RGBBand(pos+i, r, g, b, span);}
		if (pos+i < ALED2->strip()->numPixels()+span+1) {ALED2->RGBBand(pos-i, r, g, b, span); ALED2->RGBBand(pos+i, r, g, b, span);}
		if (pos+i < ALED3->strip()->numPixels()+span+1) {ALED3->RGBBand(pos-i, r, g, b, span); ALED2->RGBBand(pos+i, r, g, b, span);}
		if (time){delay(time);}
		// Rather than being sneaky and erasing just the tail pixel,
		// it's easier to erase it all and draw a new one next time.
		for(int j=-span; j<= span; j++) 
		{
			if (pos < ALED1->strip()->numPixels()+span) {ALED1->strip()->setPixelColor(pos-i+j, 0,0,0); ALED1->strip()->setPixelColor(pos+i+j, 0,0,0);}
			if (pos < ALED2->strip()->numPixels()+span) {ALED2->strip()->setPixelColor(pos-i+j, 0,0,0); ALED2->strip()->setPixelColor(pos+i+j, 0,0,0);}
			if (pos < ALED3->strip()->numPixels()+span) {ALED3->strip()->setPixelColor(pos-i+j, 0,0,0); ALED3->strip()->setPixelColor(pos+i+j, 0,0,0);}
		}
	  }
	  for (int i = 0; i < span; i++) {
		_pinState->update();
		 {ALED1->RGBBand(pos-max_pos-i, r2, g2, b2, span); ALED1->RGBBand(pos+max_pos+i, r2, g2, b2, span);}
		 {ALED2->RGBBand(pos-max_pos-i, r2, g2, b2, span); ALED2->RGBBand(pos+max_pos+i, r2, g2, b2, span);}
		 {ALED3->RGBBand(pos-max_pos-i, r2, g2, b2, span); ALED2->RGBBand(pos+max_pos+i, r2, g2, b2, span);}
		for(int j=-span; j<= span; j++) {
			{ALED1->strip()->setPixelColor(pos-max_pos-i+j, 0,0,0); ALED1->strip()->setPixelColor(pos+max_pos+i+j, 0,0,0);}
			 {ALED2->strip()->setPixelColor(pos-max_pos-i+j, 0,0,0); ALED2->strip()->setPixelColor(pos+max_pos+i+j, 0,0,0);}
			 {ALED3->strip()->setPixelColor(pos-max_pos-i+j, 0,0,0); ALED3->strip()->setPixelColor(pos+max_pos+i+j, 0,0,0);}
		}   
	  }	
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

