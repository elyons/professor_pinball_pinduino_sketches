#include <Arduino.h>
#include <AddressableStrip.h>
#include <Adafruit_NeoPixel.h>

AddressableStrip::AddressableStrip(int num, int pin)
{
  //Data channel
  pinMode(pin, OUTPUT);
  _pin = pin;
  _numLEDs = num;
  _strip = new Adafruit_NeoPixel(_numLEDs, _pin, NEO_GRB + NEO_KHZ800);
//  clear();// this is causing the Arduino to crash.  Perhaps where I have it placed in terms of order in the library?
}

void AddressableStrip::setColorVars(int r, int g, int b)
{
  _r = r;
  _g = g;
  _b = b;
}

void AddressableStrip::setNumLEDs(int num)
{
  _numLEDs = num;
}

int AddressableStrip::getNumLEDs()
{
  return _numLEDs;
}

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
 setColorVars(r, g, b);
}

void AddressableStrip::setColor(String color)
{
  int r = 0;
  int g = 0;
  int b = 0;
  color2RGB(color, r, g, b);
  
}

void AddressableStrip::setRGB(int r, int g, int b)
{
  setColorVars(r, g, b);
}

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

void AddressableStrip::clear()
{
  colorRGB(0,0,0,1);
}

void AddressableStrip::color(String color, int brightness)
{
  int r = 0;
  int g = 0;
  int b = 0;
  color2RGB(color, r, g, b);
  colorRGB(r, g, b, brightness); 
}


void AddressableStrip::fadeIn(String color, float time)
{
  int r = 0;
  int g = 0;
  int b = 0;
  color2RGB(color, r, g, b);
  fadeInRGB(r,g,b,time);
}

void AddressableStrip::fadeInRGB(int r, int g, int b, float time)
{
  time = time/256;
  colorRGB(r,g,b,1);
  if (time < 1) {time = 0;}
  for (int i = 1; i < 256; i++) {
    if (time) {delay(time);}
    _strip->setBrightness(i);
    _strip->show();
  }
  _strip->setBrightness(250);
  _strip->show();
}

void AddressableStrip::fadeOut(float steps)
{
  if (steps < 1){steps=1;}
  uint8_t origBrightness = _strip->getBrightness();
  float brightStep = origBrightness/steps; 
  
  for (int i=0; i<steps; i++) {
    int brightness = origBrightness-(brightStep+brightStep*i);
    if (brightness < 1) {brightness=1;}
    _strip->setBrightness(brightness);
    _strip->show();
  }
  clear();
}

void AddressableStrip::RGBBand(int r, int g, int b, int x, int pos) {
    if (r <0 ) {r=0;}
    if (g <0 ) {g=0;}
    if (b <0 ) {b=0;}
    if (r >255 ) {r=255;}
    if (g >255 ) {g=255;}
    if (b >255 ) {b=255;}
  double s = 100/x;
  for(int i=0; i<x; i++) {
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
    if (pos+i > -1) {_strip->setPixelColor(pos+i, r1, g1, b1);}
    if (pos-i > -1) {_strip->setPixelColor(pos-i, r1, g1, b1);}
  }
  _strip->setBrightness(255);
  _strip->show();
}

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
  
  for (int i = 0; i < numP+span*2; i++) {
    float r = r1;
    float g = g1;
    float b = b1;
    if (i > span) {
      r = r1-(rcs*(i-span));
      g = g1-(gcs*(i-span));
      b = b1-(bcs*(i-span)); 
    }
    RGBBand (r,g,b,span, pos);
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

void AddressableStrip::chase2color(String color1, String color2, float span, int time, int dir)
{
  int r1,g1,b1;
  int r2,g2,b2;
  color2RGB(color1, r1, g1, b1);
  color2RGB(color2, r2, g2, b2);
  chase2RGB(r1, g1, b1, r2, g2, b2, span, time, dir);
}
