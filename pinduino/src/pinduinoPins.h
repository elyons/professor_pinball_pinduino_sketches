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
    pinduinoPins(String val);
		
		//Variables
		String arduinoType;

		//Arduino pin functions
		void reset(); // resets values of all pin states to 0
		void resetPin(int pin); // resets the value of a pin State to 0
		void print(); // print values of pin states
		void update(); // update pin states by scanning input pins
		int get(int pin); // gets the pin state for a given Arduino pin
		int numPins(); // returns the number of pins being monitors (default: 16)
		int J6(int pin); // interface to retrieve pin state by Stern J6 pin
		void resetJ6(int pin); // interface to retrieve pin state by Stern J6 pin
		int J7(int pin); // interface to retrieve pin state by Stern J7 pin 
		void resetJ7(int pin); // interface to retrieve pin state by Stern J7 pin 
		int J126(int pin); // interface to retrieve pin state by WPC J126 pin 
		void resetJ126(int pin); // interface to retrieve pin state by WPC J126 pin 
		int any(); // returns true if any pinStates have non-zero values

  private:
		//internal array for input pins getting signal from pinball machine
		const static int _numPins = 16;
		//array 0-7 are J6 pins 1-8 (pin 9 is key and pin 10 is power)
		//array 8-15 are J7 pins 2-10 (pin 1 is power and pin 5 is key)
		int _pinsMega[_numPins] = {22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52};
		//		int _pinsNano[_numPins] = {A2,A3,A4,A5,A1,A0,13,12,5,4,3,2,9,8,7,6};
		int _pinsNano[_numPins] = {A1,A0,13,12,A2,A3,A4,A5,5,4,3,2,9,8,7,6};
		int _pinStates[_numPins];
};



#endif
