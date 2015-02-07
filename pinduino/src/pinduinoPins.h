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
		void reset();
		void print();
		void update();
		int get(int pin);
		int numPins();
		int J6(int pin);
		int J7(int pin);

  private:
		//internal array for input pins getting signal from pinball machine
		const static int _numPins = 16;
		int _pins[_numPins] = {22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52};
		int _pinStates[_numPins];
};



#endif
