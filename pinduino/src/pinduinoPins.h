/*
  pinduino.h - Library for pinduino shield for Arduinos.
  Created by Eric Lyons and Wes Sparks, 2015.
  Released into the public domain.
  Play more pinball!
*/
#ifndef pinduinoPins_h
#define pinduinoPins_h

#include <Arduino.h>
class pinduinoPins
{
  protected:

  public:
    //Constructor
    pinduinoPins();
		
		//Arduino pin functions
		void reset(); // resets values of all pin states to 0
		void resetPin(int pin); // resets the value of a pin State to 0
		void print(); // print values of pin states
		void update(); // update pin states by scanning input pins
		int get(int pin); // gets the pin state for a given Arduino pin
		int numPins(); // returns the number of pins being monitors (default: 16)
		int J6(int pin); // interface to retrieve pin state by J6 pin
		int J7(int pin); // interface to retrieve pin state by J7 pin 
		int any(); // returns true if any pinStates have non-zero values

  private:
		//internal array for input pins getting signal from pinball machine
		const static int _numPins = 16;
		int _pins[_numPins] = { 22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52 };
		int _pinStates[_numPins];
};



#endif
