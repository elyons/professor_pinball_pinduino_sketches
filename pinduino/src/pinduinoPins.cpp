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

void pinduinoPins::reset()
{
	int i;
	for (i = 0; i < _numPins; i = i + 1) 
	{
		_pinStates[i] = 0;    
	}
}

void pinduinoPins::resetPin(int pin)
{
	_pinStates[pin] = 0;
}

int pinduinoPins::get(int pin)
{
	return _pinStates[pin];
}

int pinduinoPins::any()
{
	for (int i = 0; i < _numPins; i = i + 1)
	{
		if (_pinStates[i] and !i==15){return 1;}//skipping J7-10 due to noise in some systems
	}
	return 0;
}

int pinduinoPins::J7 (int pin)
{
	if (pin == 2) { return get(8);}
	else if (pin == 3) { return get(9);}
	else if (pin == 4) { return get(10);}
	else if (pin == 6) { return get(11);}
	else if (pin == 7) { return get(12);}
	else if (pin == 8) { return get(13);}
	else if (pin == 9) { return get(14);}
	else if (pin == 10) { return get(15);}
	//default
	return 0;
}

void pinduinoPins::resetJ7 (int pin)
{
	if (pin == 2) { resetPin(8);}
	else if (pin == 3) { resetPin(9);}
	else if (pin == 4) { resetPin(10);}
	else if (pin == 6) { resetPin(11);}
	else if (pin == 7) { resetPin(12);}
	else if (pin == 8) { resetPin(13);}
	else if (pin == 9) { resetPin(14);}
	else if (pin == 10) { resetPin(15);}
}

int pinduinoPins::J6 (int pin)
{
	if (pin == 1) { return get(0);}
	else if (pin == 2) { return get(1);}
	else if (pin == 3) { return get(2);}
	else if (pin == 4) { return get(3);}
	else if (pin == 5) { return get(4);}
	else if (pin == 6) { return get(5);}
	else if (pin == 7) { return get(6);}
	else if (pin == 8) { return get(7);}
	//default
	return 0;
}

void pinduinoPins::resetJ6 (int pin)
{
	if (pin == 1) { resetPin(0);}
	else if (pin == 2) { resetPin(1);}
	else if (pin == 3) { resetPin(2);}
	else if (pin == 4) { resetPin(3);}
	else if (pin == 5) { resetPin(4);}
	else if (pin == 6) { resetPin(5);}
	else if (pin == 7) { resetPin(6);}
	else if (pin == 8) { resetPin(7);}
}

int pinduinoPins::numPins()
{
	return _numPins;
}

//helps with debugging
void pinduinoPins::print() 
{
	int i;
	for (i = 0; i < _numPins; i = i + 1) 
	{
		Serial.print(_pinStates[i]);    
		Serial.print(" ");
	}
	Serial.println();
}

void pinduinoPins::update()
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
