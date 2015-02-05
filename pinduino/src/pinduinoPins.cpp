/*
  pinduino.cpp - Library for pinduino shield for Arduinos.
  Created by Eric Lyons and Wes Sparks, 2015.
  Released into the public domain.
  Play more pinball!
*/

#include <Arduino.h>
#include <pinduinoPins.h>


//Note: are these being released as global vars into the parent program?
//RGBStrip* RGB1;
//RGBStrip* RGB2;
//RGBStrip* RGB3;
//RGBStrip* RGB4;

//AddressableStrip* ALED1;
//AddressableStrip* ALED2;
//AddressableStrip* ALED3;


pinduinoPins::pinduinoPins()
{
}

//helps with debugging
void pinduinoPins::resetPinStates()
{
	int i;
	for (i = 0; i < _numPins; i = i + 1) 
	{
		_pinStates[i] = 0;    
	}
}

void pinduinoPins::printPinStates() 
{
	int i;
	for (i = 0; i < _numPins; i = i + 1) 
	{
		Serial.print(_pinStates[i]);    
		Serial.print(" ");
	}
	Serial.println();
}

void pinduinoPins::updatePinStates()
{
	int i;
	for (i = 0; i < _numPins; i = i + 1) 
	{
		int state = digitalRead(_pins[i]);
		if (state == 1) 
		{ //circuit being checked has been activated
			_pinStates[i] = _pinStates[i] + 1;
		}
	}
}
