/*
  pinduino.h - Library for pinduino shield for Arduinos.
  Created by Eric Lyons and Wes Sparks, 2015.
  Released into the public domain.
  Play more pinball!
*/
#ifndef pinduino_h
#define pinduino_h

#include <Arduino.h>
#include <RGBStrip.h>
#include <AddressableStrip.h>
#include <pinduinoPins.h>
class pinduino
{
  protected:

  public:
  	//Constructor with no parameters
  	pinduino();
  	
    //Overloaded Constructor for addressable strips
    pinduino(int num1, int num2, int num3);
		
    //functions for controlling 12V RGB strips
		pinduinoPins* pinState();

    //functions for controlling 12V RGB strips
    RGBStrip* rgbLED1();
    RGBStrip* rgbLED2();
    RGBStrip* rgbLED3();
    RGBStrip* rgbLED4();

    //functions for controlling 5V Addressable LED strips
    AddressableStrip* adrLED1();    
    AddressableStrip* adrLED2();    
    AddressableStrip* adrLED3();    

    void testRGBStrip(RGBStrip* strip);
    void testRGBStrip1();
    void testRGBStrip2();
    void testRGBStrip3();
    void testRGBStrip4();

  	void testSpeakerAdrLED(AddressableStrip* strip);
	void testSpeakerAdrLED1();

	void testAdrLED(AddressableStrip* strip);
    void testAdrLED1();
    void testAdrLED2();
    void testAdrLED3();
    void testAdrLED4();
	
	void testAdrLEDAlpha(AddressableStrip* strip);
    void testAdrLED1Alpha();
    void testAdrLED2Alpha();
    void testAdrLED3Alpha();
	
     
  private:
		//internal object for monitoring pinball machine states
		pinduinoPins* _pinState;

		//internal objects for RGB strip control`
    RGBStrip* RGB1;
    RGBStrip* RGB2;
    RGBStrip* RGB3;
    RGBStrip* RGB4;

		//internal objects for AssressableStrip control
    AddressableStrip* ALED1;
    AddressableStrip* ALED2;
    AddressableStrip* ALED3;
    
    void init(int aledNum1, int aledNum2, int aledNum3);
};



#endif
