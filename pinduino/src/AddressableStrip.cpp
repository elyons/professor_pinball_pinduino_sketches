#include <Arduino.h>
#include <AddressableStrip.h>
#include <Adafruit_NeoPixel.h>
#include <pinduinoPins.h>

AddressableStrip::AddressableStrip(int num, int pin, pinduinoPins* pinState)
{
  //Data channel
  pinMode(pin, OUTPUT);
  _pinState=pinState;
  _pin = pin;
  _numLEDs = num;
  _strip = new Adafruit_NeoPixel(_numLEDs, _pin, NEO_GRB + NEO_KHZ800);
//  clear();// this is causing the Arduino to crash.  Perhaps where I have it placed in terms of order in the library?
}

//not being used this way.  Strip LEDS are declared when object is substaniated
void AddressableStrip::setNumLEDs(int num)
{
  _numLEDs = num;
}

int AddressableStrip::getNumLEDs()
{
  return _numLEDs;
}

AddressableStrip* AddressableStrip::next()
{
	return _next;
}

void AddressableStrip::setNext(AddressableStrip* strip)
{
	_next = strip;
}

AddressableStrip* AddressableStrip::previous()
{
	return _previous;
}

void AddressableStrip::setPrevious(AddressableStrip* strip)
{
	_previous = strip;
}

//initilize
Adafruit_NeoPixel* AddressableStrip::strip()
{
   // Adafruit_NeoPixel (# of LEDs, Signal Pin, Refresh Rate)
   //Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, LEDPIN, NEO_GRB + NEO_KHZ800);   
   if (_strip->numPixels()==0)
   {
     _strip = new Adafruit_NeoPixel(_numLEDs, _pin, NEO_GRB + NEO_KHZ800);
   }
   return _strip; 
}

//convert named colors (e.g., "red") to RGB (e.g., 255,0,0)
void AddressableStrip::color2RGB(String color, int &r, int &g, int &b)
{
  r=0;
  g=0;
  b=0;
  if (color.equalsIgnoreCase("red"))
  {
    r=255;
  }
  else if (color.equalsIgnoreCase("green"))
  {
    g=255;
  }
  else if (color.equalsIgnoreCase("blue"))
  {
    b=255;
  }
  else if (color.equalsIgnoreCase("yellow"))
  {
    r=255;
    g=255;
  }
  else if (color.equalsIgnoreCase("purple"))
  {
    r=255;
    b=255;
  }
  else if (color.equalsIgnoreCase("cyan"))
  {
    b=255;
    g=255;
  }
  else if (color.equalsIgnoreCase("white"))
  {
    r=255;
    g=255;
    b=255;
  }
  else if (color.equalsIgnoreCase("orange"))
  {
    r=255;
    g=128;
    b=0;
  }
  else if (color.equalsIgnoreCase("lime"))
  {
    r=128;
    g=255;
    b=0;
  }
  else if (color.equalsIgnoreCase("sky"))
  {
    r=0;
    g=128;
    b=255;
  }
  else if (color.equalsIgnoreCase("mint"))
  {
    r=0;
    g=255;
    b=128;
  }
  else if (color.equalsIgnoreCase("magenta"))
  {
    r=255;
    g=0;
    b=128;
  }
  else if (color.equalsIgnoreCase("lavender"))
  {
    r=128;
    g=0;
    b=255;
  }
}

//set entire strip one color based on RGB values
void AddressableStrip::colorRGB(int r, int g, int b, int brightness) {
  if (brightness < 1) {brightness = 1;}
  if (brightness > 255) {brightness = 255;}
  if (r<0) {r=0;}
  if (r>255) {r=255;}
  if (g<0) {g=0;}
  if (g>255) {g=255;}
  if (b<0) {b=0;}
  if (b>255) {b=255;}
  for(int i=0; i<_numLEDs; i++) {
      _strip->setPixelColor(i, r, g, b);
  }
  _strip->setBrightness(brightness);
  _strip->show();
}

//clear strip  turn off all colors
void AddressableStrip::clear()
{
  colorRGB(0,0,0,1);
}

//set entire strip one color based on names color
void AddressableStrip::color(String color, int brightness)
{
  int r = 0;
  int g = 0;
  int b = 0;
  color2RGB(color, r, g, b);
  colorRGB(r, g, b, brightness); 
}

//fade in strip to a named color
void AddressableStrip::fadeIn(String color, float time)
{
  int r = 0;
  int g = 0;
  int b = 0;
  color2RGB(color, r, g, b);
  fadeInRGB(r,g,b,time);
}

//fade in strip to an RGB color
void AddressableStrip::fadeInRGB(int r, int g, int b, float time)
{
  time = time/256;
  colorRGB(r,g,b,1);
  if (time < 1) {time = 0;}
  for (int i = 1; i < 256; i++) {
		_pinState->update();
    if (time) {delay(time);}
    _strip->setBrightness(i);
    _strip->show();
  }
  _strip->setBrightness(250);
  _strip->show();
}

//fade strip from RGB color to another RGB color
void AddressableStrip::fadeRGB2RGB(float r1, float g1, float b1, float r2, float g2, float b2, float time)
{
  time = time/256;
  colorRGB(r1,g1,b1,250);
  if (time < 1) {time = 0;}
  //calcuate color changes
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
    colorRGB(r,g,b,250);
		_strip->show();
  }
}

//fade strip from color to another color
void AddressableStrip::fadeColor2Color(String color1, String color2, float time)
{
 int r1,g1,b1;
 int r2,g2,b2;
 color2RGB(color1, r1, g1, b1);
 color2RGB(color2, r2, g2, b2);
 fadeRGB2RGB(r1, g1, b1, r2, g2, b2, time);
}

//fade out strip
void AddressableStrip::fadeOut(float steps)
{
  if (steps < 1){steps=1;}
  uint8_t origBrightness = _strip->getBrightness();
  float brightStep = origBrightness/steps; 
  
  for (int i=0; i<steps; i++) {
	_pinState->update();
    int brightness = origBrightness-(brightStep+brightStep*i);
    if (brightness < 1) {brightness=1;}
    _strip->setBrightness(brightness);
    _strip->show();
  }
  clear();
}

//draw a band of width 2xspan on the LED strip at position pos of a given span with an RGB color.  Center of band is brightest and fades to either end
void AddressableStrip::RGBBand(int pos, int r, int g, int b, int span) {
    if (r <0 ) {r=0;}
    if (g <0 ) {g=0;}
    if (b <0 ) {b=0;}
    if (r >255 ) {r=255;}
    if (g >255 ) {g=255;}
    if (b >255 ) {b=255;}
  double s = 100/span;
  for(int i=0; i<span; i++) {
    double V = (i*s/100);
    V = sqrt(V);
    int r1 = r-V*r;
    int g1 = g-V*g;
    int b1 = b-V*b;
    if (r1 <=0 ) {r1=0;}
    if (g1 <=0 ) {g1=0;}
    if (b1 <=0 ) {b1=0;}
    if (r1 >255 ) {r1=255;}
    if (g1 >255 ) {g1=255;}
    if (b1 >255 ) {b1=255;}
	  
    if (pos+i > -1 && pos+i < _strip->numPixels()) {_strip->setPixelColor(pos+i, r1, g1, b1);}
    if (pos-i > -1 && pos+i < _strip->numPixels()) {_strip->setPixelColor(pos-i, r1, g1, b1);}
  }
  _strip->setBrightness(255);
  _strip->show();
}



//TWS: Continuous Band with start and stop positions
//draw a band of width 2xspan on the LED strip at position pos of a given span with an RGB color.  Center of band is brightest and fades to either end
void AddressableStrip::RGBBandCont(int pos, int r, int g, int b, int span, int startLED, int endLED) {
	int numP = _strip->numPixels();
	if (r <0 ) {r=0;}
    if (g <0 ) {g=0;}
    if (b <0 ) {b=0;}
    if (r >255 ) {r=255;}
    if (g >255 ) {g=255;}
    if (b >255 ) {b=255;}
  double s = 100/span;
  for(int i=0; i<span; i++) {
    double V = (i*s/100);
    V = sqrt(V);
    int r1 = r-V*r;
    int g1 = g-V*g;
    int b1 = b-V*b;
    if (r1 <=0 ) {r1=0;}
    if (g1 <=0 ) {g1=0;}
    if (b1 <=0 ) {b1=0;}
    if (r1 >255 ) {r1=255;}
    if (g1 >255 ) {g1=255;}
    if (b1 >255 ) {b1=255;}
	

	if (pos+i >= startLED+numP)
		{
		_strip->setPixelColor((pos+i-numP), r1, g1, b1);
		}
	else
		{
		_strip->setPixelColor(pos+i, r1, g1, b1);
		}
	if (pos-i < startLED) 
		{
		_strip->setPixelColor(numP+pos-i,r1,g1,b1);
		}
	else
		{
		_strip->setPixelColor(pos-i, r1, g1, b1);
		}
  }
  _strip->setBrightness(255);
  _strip->show();
}

//generate a band of light that move from one end of the strip to the other that starts at one RGB color and ends at another RGB color
void AddressableStrip::chase2RGB(float r1, float g1, float b1, float r2, float g2, float b2, float span, int time, int dir) {
  int pos;
  int numP = _strip->numPixels();
  if (dir > 0) { pos=numP+span;} 
  else  { pos=0-span;} 
  //color step size
  float rcs = abs(r1-r2)/(numP);
  if (r2 > r1){rcs=rcs*-1;}
  float gcs = abs(g1-g2)/(numP);
  if (g2 > g1){gcs=gcs*-1;}
  float bcs = abs(b1-b2)/(numP);
  if (b2 > b1){bcs=bcs*-1;}

  for (int i = 0; i < span; i++) {
  	_pinState->update();
  	RGBBand (pos, r1,g1,b1,span);
  	if (time) {delay(time);}
  	for(int j=-span; j<= span; j++) {
  	  _strip->setPixelColor(pos+j, 0,0,0);
  	}  
    if (dir > 0) {pos--;}
    else {pos++;}
  }
  for (int i = 0; i < numP; i++) {
	_pinState->update();
    float r = r1;
    float g = g1;
    float b = b1;
    r = r1-(rcs*(i));
    g = g1-(gcs*(i));
    b = b1-(bcs*(i)); 
    RGBBand (pos, r,g,b,span);
    if (time){delay(time);}
    // Rather than being sneaky and erasing just the tail pixel,
    // it's easier to erase it all and draw a new one next time.
    for(int j=-span; j<= span; j++) 
    {
      _strip->setPixelColor(pos+j, 0,0,0);
    }
    if (dir > 0) {pos--;}
    else {pos++;}
  }
  for (int i = 0; i < span; i++) {
  	_pinState->update();
  	RGBBand (pos, r2,g2,b2,span);
  	if (time){delay(time);}
  	for(int j=-span; j<= span; j++) {
  	  _strip->setPixelColor(pos+j, 0,0,0);
  	}  
    if (dir > 0) {pos--;}
    else {pos++;}
  }
}

//starting from a point, create two bands of light that spread to the ends of the strip
void AddressableStrip::chase2RGBFromPoint(int pos, float r1, float g1, float b1, float r2, float g2, float b2, int span, int time) {
  int numP = _strip->numPixels();
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
	RGBBand (pos-i, r,g,b,span);
	RGBBand (pos+i, r,g,b,span);
	if (time){delay(time);}
	// Rather than being sneaky and erasing just the tail pixel,
	// it's easier to erase it all and draw a new one next time.
	for(int j=-span; j<= span; j++) 
	{
	  _strip->setPixelColor(pos-i+j, 0,0,0);
	  _strip->setPixelColor(pos+i+j, 0,0,0);
	}
  }
  for (int i = 0; i < span; i++) {
	_pinState->update();
	RGBBand (pos-max_pos-i, r2,g2,b2,span);
	RGBBand (pos+max_pos+i, r2,g2,b2,span);
	for(int j=-span; j<= span; j++) {
	  _strip->setPixelColor(pos-max_pos-i+j, 0,0,0);
	  _strip->setPixelColor(pos+max_pos+i+j, 0,0,0);
	}   
  }	
}

void AddressableStrip::chase2ColorFromPoint(int pos, String color1, String color2, int span, int time){
  int r1,g1,b1;
  int r2,g2,b2;
  color2RGB(color1, r1, g1, b1);
  color2RGB(color2, r2, g2, b2);
  chase2RGBFromPoint(pos, r1, g1, b1, r2, g2, b2, span, time);
}

//generate a band of light that move from one end of the strip to the other that starts at one RGB color and ends at another RGB color
void AddressableStrip::chase2RGBCont(float r1, float g1, float b1, float r2, float g2, float b2, float span, int time, int dir, int startLED, int endLED) {
  // TWS: Initialized POS to 0 for cont circle testing.
  int pos = 0;
  int numP = _strip->numPixels();
  
  // TWS: Removed this for continuous circle testing.
  if (dir > 0) 
  { 
	  pos=startLED+numP;
  } 
  else  
  { 
	  pos=startLED;
  } 
  
  //color step size
  float rcs = abs(r1-r2)/(numP);
  if (r2 > r1){rcs=rcs*-1;}
  float gcs = abs(g1-g2)/(numP);
  if (g2 > g1){gcs=gcs*-1;}
  float bcs = abs(b1-b2)/(numP);
  if (b2 > b1){bcs=bcs*-1;}
  
  for (int i = startLED; i < startLED+numP; i++) {
		_pinState->update();
    float r = r1;
    float g = g1;
    float b = b1;
    if (i > span) {
      r = r1-(rcs*(i-span));
      g = g1-(gcs*(i-span));
      b = b1-(bcs*(i-span)); 
    }
    RGBBandCont (pos, r,g,b,span,startLED, startLED+numP);
    if (time){delay(time);}
    // Rather than being sneaky and erasing just the tail pixel,
    // it's easier to erase it all and draw a new one next time.
    for(int j=startLED; j < (startLED+numP); j++) 
    {
	    _strip->setPixelColor(j, 0,0,0);
    }
    if (dir > 0) 
	  {
		  if (pos > startLED)
		  {
			  pos--;
		  }
		  else
		  {
			  pos = startLED + numP;
		  }
	  }
    else 
	  {
		  if (pos < (startLED + numP)) 
		  {
			  pos++;
		  }
		  else
		  {
			  pos = startLED;
		  }
	  }
  }
}

void AddressableStrip::chase2ColorCont(String color1, String color2, float span, int time, int dir, int startLED, int endLED) {
  int r1,g1,b1;
	int r2,g2,b2;
	color2RGB(color1, r1, g1, b1);
	color2RGB(color2, r2, g2, b2);
  chase2RGBCont(r1, g1, b1, r2, g2, b2, span, time, dir, startLED, endLED);
}
//generate a band of light that move from one end of the strip to the other that starts at one named color and ends at another named color
void AddressableStrip::chase2Color(String color1, String color2, float span, int time, int dir)
{
  int r1,g1,b1;
  int r2,g2,b2;
  color2RGB(color1, r1, g1, b1);
  color2RGB(color2, r2, g2, b2);
  chase2RGB(r1, g1, b1, r2, g2, b2, span, time, dir);
}

//generate a band of light that moves from one end of the strip to the other using RGB color
void AddressableStrip::chaseRGB(int r, int g, int b, int span, int time, int dir)
{
  chase2RGB(r,g,b,r,g,b,span, time, dir);
}

//generate a band of light that moves from one end of the strip to the other using RGB color
void AddressableStrip::chase(String color, float span, int time, int dir)
{
  int r,g,b;
  color2RGB(color,r,g,b);
  chaseRGB(r,g,b,span,time,dir);
}


//start at a point x with one RGB color and then spread to both ends of strip fading to second RGB color
void AddressableStrip::spreadInFromPoint2RGB (int pos, float r1, float g1, float b1, float r2, float g2, float b2, int time) 
{
  int N_LEDS = _strip->numPixels();
  //Figure out the distance from the furthest end
  int middle_led = N_LEDS/2;
  int num_positions = 0;  // number of positions between the pos and the furthest end of strip
  if (pos < middle_led) {num_positions = N_LEDS-pos+1;}
  else {num_positions = pos+1;}

  //calcuate color changes
  float rcs = abs(r1-r2)/num_positions;
  if (r2 > r1){rcs=rcs*-1;}
  float gcs = abs(g1-g2)/num_positions;
  if (g2 > g1){gcs=gcs*-1;}
  float bcs = abs(b1-b2)/num_positions;
  if (b2 > b1){bcs=bcs*-1;}

  //time between turning LEDs on 
  int expand_time = time/num_positions;
  
  _strip->setBrightness(255);
  for(int i=0; i<num_positions; i++) {
		_pinState->update();
    float r = r1;
    float g = g1;
    float b = b1;
    r = r1-(rcs*i);
    g = g1-(gcs*i);
    b = b1-(bcs*i); 
    _strip->setPixelColor(pos + i, r, g, b);
    _strip->setPixelColor(pos - i, r, g, b);
    _strip->show();
    delay(expand_time);
  }
} 

//start at a point x with one named color and then spread to both ends of strip fading to second named color
void AddressableStrip::spreadInFromPoint2Color (int pos, String color1, String color2, int time) 
{
  int r1,g1,b1;
  int r2,g2,b2;
  color2RGB(color1, r1, g1, b1);
  color2RGB(color2, r2, g2, b2);
  spreadInFromPoint2RGB(pos, r1, g1, b1, r2, g2, b2, time);
}

void AddressableStrip::spreadInFromPointRGB (int pos, float r, float g, float b, int time)
{
  spreadInFromPoint2RGB(pos, r, g, b, r, g, b, time);
}

void AddressableStrip::spreadInFromPoint (int pos, String color, int time)
{
  int r,g,b;
  color2RGB(color, r, g, b);
  spreadInFromPointRGB(pos, r, g, b, time);
}


//with full lights, fade from point till you reach ends of light strip
void AddressableStrip::spreadOutFromPoint (int pos, float time) {
  //Figure out the distance from the furthest end
  int N_LEDS = _strip->numPixels();
  int middle_led = N_LEDS/2;
  int num_positions = 0;  // number of positions between the pos and the furthest end of strip
  if (pos < middle_led) {num_positions = N_LEDS-pos+1;}
  else {num_positions = pos+1;}

  //time between turning LEDs on 
  float expand_time = time/num_positions;
  
  for(int i=0; i<num_positions; i++) 
	{
		_pinState->update();
    // Serial.println(i);
    _strip->setPixelColor(pos + i, 0, 0, 0);
    _strip->setPixelColor(pos - i, 0, 0, 0);
    _strip->show();
    delay(expand_time);
  }
}

//with full lights, fade ends till you reach a point in light strip
void AddressableStrip::spreadOutToPoint (int pos, float time) {
  //Figure out the distance from the furthest end
  int N_LEDS = _strip->numPixels();
  int middle_led = N_LEDS/2;
  int num_positions = 0;  // number of positions between the pos and the furthest end of strip
  if (pos < middle_led) {num_positions = N_LEDS-pos+1;}
  else {num_positions = pos+1;}

  //time between turning LEDs on 
  int expand_time = time/num_positions;
  
  for(int i=num_positions; i>0; i--) 
	{
		_pinState->update();
    _strip->setPixelColor(pos + i, 0, 0, 0);
    _strip->setPixelColor(pos - i, 0, 0, 0);
    _strip->show();
    delay(expand_time);
  }
}

void AddressableStrip::explosionRGB(int pos, int r, int g, int b, int span) 
{
  clear();
  if (r <0 ) {r=0;}
  if (g <0 ) {g=0;}
  if (b <0 ) {b=0;}
  if (r >255 ) {r=255;}
  if (g >255 ) {g=255;}
  if (b >255 ) {b=255;}

  double s = 100/span;
  for(int i=0; i<=span; i++) {
    double V = (i*s/100);
    V = sqrt(V); 
    //V = 255-V*255;
    int r1 = r-V*r;
    int g1 = g-V*g;
    int b1 = b-V*b;
    if (r1 <=0 ) {r1=0;}
    if (g1 <=0 ) {g1=0;}
    if (b1 <=0 ) {b1=0;}
    if (r1 >255 ) {r1=255;}
    if (g1 >255 ) {g1=255;}
    if (b1 >255 ) {b1=255;}
    if (pos+i > -1) {_strip->setPixelColor(pos+i, r1, g1, b1);}
    if (pos-i > -1) {_strip->setPixelColor(pos-i, r1, g1, b1);}
  }
  _strip->setBrightness(255);
  _strip->show();
  fadeOut(50);
}

void AddressableStrip::explosion (int pos, String color, int span)
{
  int r,g,b;
  color2RGB(color, r, g, b);
  explosionRGB(pos, r, g, b, span);
}

//rainbow happy fun time!
void AddressableStrip::rainbow(int wait) 
{
  int i, j; 
  _strip->setBrightness(255);
  for(j=0; j<256; j++) {
		_pinState->update();
    for(i=0; i<_strip->numPixels(); i++) {
		  _pinState->update();
      _strip->setPixelColor(_strip->numPixels()-i, Wheel((i+j) & 255));
    }
    _strip->show();
    delay(wait);
  }
}
 
// Slightly different, this makes the rainbow equally distributed throughout
void AddressableStrip::rainbowCycle(int wait) 
{
  int i, j; 
  _strip->setBrightness(255);
  for(j=0; j<256; j++) { 
		_pinState->update();
    for(i=0; i < _strip->numPixels(); i++) {
		  _pinState->update();
      _strip->setPixelColor(_strip->numPixels()-i, Wheel(((i * 256 / _strip->numPixels()) + j*2) & 255));
    }
    _strip->show();
    delay(wait);
  }
}
 
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
int AddressableStrip::Wheel(int WheelPos) 
{
  if(WheelPos < 85) {
   return _strip->Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return _strip->Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return _strip->Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}


/* 
TWS: Feb 15 2015  Bullet Functions
*/

//RGBBullet -- draw a band of width 1xspan on the LED strip at position pos of a given span with an RGB color.  Front of band (at pos) is brightest and fades to end.
void AddressableStrip::RGBBullet(int pos, int r, int g, int b, int span, int dir) {
	int numP = _strip->numPixels();
    if (r <0 ) {r=0;}
    if (g <0 ) {g=0;}
    if (b <0 ) {b=0;}
    if (r >255 ) {r=255;}
    if (g >255 ) {g=255;}
    if (b >255 ) {b=255;}
  double s = 100/span;
  for(int i=0; i<=span; i++) {
    double V = (i*s/100);
    V = sqrt(V);
    int r1 = r-V*r;
    int g1 = g-V*g;
    int b1 = b-V*b;
    if (r1 <=0 ) {r1=0;}
    if (g1 <=0 ) {g1=0;}
    if (b1 <=0 ) {b1=0;}
    if (r1 >255 ) {r1=255;}
    if (g1 >255 ) {g1=255;}
    if (b1 >255 ) {b1=255;}
	if (dir >= 0) 
		{  
		if (pos+i > -121) 
			{
			if ((pos+i >= 0) && (pos+i < numP)){_strip->setPixelColor(pos+i, r1, g1, b1);}
			if ((pos+i+30 >= 0) && (pos+i+30 < numP)){_strip->setPixelColor(pos+i+30, r1, g1, b1);}
			if ((pos+i+60 >= 0) && (pos+i+60 < numP)){_strip->setPixelColor(pos+i+60, r1, g1, b1);}
			if ((pos+i+90 >= 0) && (pos+i+90 < numP)){_strip->setPixelColor(pos+i+90, r1, g1, b1);}
			if ((pos+i+120 >= 0) && (pos+i+120 < numP)){_strip->setPixelColor(pos+i+120, r1, g1, b1);}
			}
		if (pos+i >=span)
			{
			_strip->setPixelColor(pos+i+1, 0,0,0);
			_strip->setPixelColor(pos+i+31, 0,0,0);
			_strip->setPixelColor(pos+i+61, 0,0,0);		
			_strip->setPixelColor(pos+i+91, 0,0,0);
			_strip->setPixelColor(pos+i+121, 0,0,0);				
			}
		}
	else
		{
		if (pos-i > -1) 
			{
			if ((pos-i >= 0) && (pos-i < numP)){_strip->setPixelColor(pos-i, r1, g1, b1);}
			if ((pos-i-30 >= 0) && (pos-i-30 < numP)){_strip->setPixelColor(pos-i-30, r1, g1, b1);}
			if ((pos-i-60 >= 0) && (pos-i-60 < numP)){_strip->setPixelColor(pos-i-60, r1, g1, b1);}
			if ((pos-i-90 >= 0) && (pos-i-90 < numP)){_strip->setPixelColor(pos-i-90, r1, g1, b1);}
			if ((pos-i-120 >= 0) && (pos-i-120 < numP)){_strip->setPixelColor(pos-i-120, r1, g1, b1);}
			}
		if (pos+i >=span)
			{
			_strip->setPixelColor(pos-i-1, 0,0,0);
			_strip->setPixelColor(pos-i-31, 0,0,0);
			_strip->setPixelColor(pos-i-61, 0,0,0);		
			_strip->setPixelColor(pos+i-91, 0,0,0);
			_strip->setPixelColor(pos+i-121, 0,0,0);			
			}
		}
	
  }
  _strip->setBrightness(255);
  _strip->show();
}

//bullet2RGB -- generate a band of light that move from one end of the strip to the other that starts at one RGB color and ends at another RGB color
void AddressableStrip::bullet2RGB(float r1, float g1, float b1, float r2, float g2, float b2, float span, int time, int dir) {
  int pos;
  int numP = _strip->numPixels();
  if (dir > 0) { pos=numP+span;} 
  else  { pos=0-span;} 
  //color step size
  float rcs = abs(r1-r2)/(numP);
  if (r2 > r1){rcs=rcs*-1;}
  float gcs = abs(g1-g2)/(numP);
  if (g2 > g1){gcs=gcs*-1;}
  float bcs = abs(b1-b2)/(numP);
  if (b2 > b1){bcs=bcs*-1;}
  
  for (int i = 0; i < numP+span*2+120; i++) {
		_pinState->update();
    float r = r1;
    float g = g1;
    float b = b1;
    if (i > span) {
      r = r1-(rcs*(i-span));
      g = g1-(gcs*(i-span));
      b = b1-(bcs*(i-span)); 
    }
    RGBBullet (pos, r,g,b,span,dir);
    if (time){delay(time);}
    // Rather than being sneaky and erasing just the tail pixel,
    // it's easier to erase it all and draw a new one next time.
    for(int j=-span; j<= span; j++) 
    {
      _strip->setPixelColor(pos+j, 0,0,0);
    }
    if (dir > 0) {pos--;}
    else {pos++;}
  }
}

//bullet -- generate a band of light that moves from one end of the strip to the other using RGB color
void AddressableStrip::bullet(String color, float span, int time, int dir)
{
  int r,g,b;
  color2RGB(color,r,g,b);
  bulletRGB(r,g,b,span,time,dir);
}

//bulletRGB -- generate a band of light that moves from one end of the strip to the other using RGB color
void AddressableStrip::bulletRGB(int r, int g, int b, int span, int time, int dir)
{
  bullet2RGB(r,g,b,r,g,b,span, time, dir);
}

//bullet2Color -- generate a band of light that move from one end of the strip to the other that starts at one named color and ends at another named color
void AddressableStrip::bullet2Color(String color1, String color2, float span, int time, int dir)
{
  int r1,g1,b1;
  int r2,g2,b2;
  color2RGB(color1, r1, g1, b1);
  color2RGB(color2, r2, g2, b2);
  bullet2RGB(r1, g1, b1, r2, g2, b2, span, time, dir);
}

//Matrix2RGB -- generate randomly N bands of light that move from one end of the strip to the other that starts at one RGB color and ends at another RGB color
void AddressableStrip::Matrix2RGB(float r1, float g1, float b1, float r2, float g2, float b2, float span, int time, int dir) {
  int pos;
 
  
  int numP = _strip->numPixels();
  if (dir > 0) 
	{ 
	// This is where I have to put in the positions for the RNG
	pos=numP+span;
	} 
  else  
	{ 
	pos=0-span;
	} 
	
	
  //color step size
  float rcs = abs(r1-r2)/(numP);
  if (r2 > r1){rcs=rcs*-1;}
  float gcs = abs(g1-g2)/(numP);
  if (g2 > g1){gcs=gcs*-1;}
  float bcs = abs(b1-b2)/(numP);
  if (b2 > b1){bcs=bcs*-1;}
  
  for (int i = 0; i < numP+span*2+120; i++) {
  // this is what I have to change to make the matrix effect
 
		_pinState->update();
    float r = r1;
    float g = g1;
    float b = b1;
    if (i > span) {
      r = r1-(rcs*(i-span));
      g = g1-(gcs*(i-span));
      b = b1-(bcs*(i-span)); 
    }
    RGBMatrix (pos, r,g,b,span,dir);
    if (time){delay(time);}
    // Rather than being sneaky and erasing just the tail pixel,
    // it's easier to erase it all and draw a new one next time.
    for(int j=-span; j<= span; j++) 
    {
      _strip->setPixelColor(pos+j, 0,0,0);
    }
    if (dir > 0) {pos--;}
    else {pos++;}
  }
}

// Generate several RGB Matrices
void AddressableStrip::RGBMatrix(int rows, int r, int g, int b, int span, int dir) {
	int numP = _strip->numPixels();
	int numPixPerRow = numP/rows;
	int row1start = 0;
	int row2start = row1start + numPixPerRow;
	int row3start = row2start + numPixPerRow;
	int row4start = row3start + numPixPerRow;
	int row5start = row4start + numPixPerRow;
	
	// Row 1
	int rand1 = rand() % numPixPerRow;
	int rand2 = rand() % numPixPerRow;
	int rand3 = rand() % numPixPerRow;
	
    if (r <0 ) {r=0;}
    if (g <0 ) {g=0;}
    if (b <0 ) {b=0;}
    if (r >255 ) {r=255;}
    if (g >255 ) {g=255;}
    if (b >255 ) {b=255;}
  double s = 100/span;
  for(int i=0; i<=span; i++) {
    double V = (i*s/100);
    V = sqrt(V);
    int r1 = r-V*r;
    int g1 = g-V*g;
    int b1 = b-V*b;
    if (r1 <=0 ) {r1=0;}
    if (g1 <=0 ) {g1=0;}
    if (b1 <=0 ) {b1=0;}
    if (r1 >255 ) {r1=255;}
    if (g1 >255 ) {g1=255;}
    if (b1 >255 ) {b1=255;}
	if (dir >= 0) 
		{  
		if (rand1+i >= row1start) 
			{
			if ((rand1+i >= 0) && (rand1+i < row2start)){_strip->setPixelColor(rand1+i, r1, g1, b1);}
			}
		if (rand1+i >=span)
			{
			_strip->setPixelColor(rand1+i+1, 0,0,0);				
			}
		}

  }
  _strip->setBrightness(255);
  _strip->show();
}
/*
TWS: Feb 15 2015 End Bullet Functions
*/
