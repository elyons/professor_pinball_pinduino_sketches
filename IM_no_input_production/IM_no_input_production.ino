#include <Adafruit_NeoPixel.h>
#include <math.h>

#define N_LEDS 81
#define PIN     0

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // initialize the pushbutton pin as an input:
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
//  Serial.begin(9600);
}

int span = 6;
int pos = strip.numPixels()+span, dir = -1; // Position, direction of "eye"
int speed_var = 10, speed_dir = 1;
int r = 1;
int g = 0;
int b = 0;
long count=0;

void loop() {
  chase();
//  rainbowCycle(speed_var);
}

void chase() {
  colorBand (r,g,b,span, pos);
  delay(speed_var);
  // Rather than being sneaky and erasing just the tail pixel,
  // it's easier to erase it all and draw a new one next time.
  for(int j=-span; j<= span; j++) strip.setPixelColor(pos+j, 0,0,0);
  // Bounce off ends of strip
  pos += dir;
  if(pos < 0-span ) {
    pos = strip.numPixels()+span;
    if (r==1 && g == 0) {
     r=1;
     g=1;
     b=0;
//     speed_var = speed_var+speed_dir;
//     if (speed_var < 2) {speed_dir = -speed_dir;}
//     if (speed_var > 100) {speed_dir = -speed_dir;}
    }
    else {
      r=1;
      g=0;
      b=0;
    }
  }
}

void colorBand(uint8_t r, uint8_t g, uint8_t b, uint8_t x, int pos) {
  double s = 100/x;
  
  for(double i=0; i<x; i++) {
    double V = (s*i/100);
    V = sqrt(V);
    V = 255-V*255;
    int r1 = r*V;
    int g1 = g*V;
    int b1 = b*V;
    if (r1 <=0 ) {r1=0;}
    if (g1 <=0 ) {g1=0;}
    if (b1 <=0 ) {b1=0;}
    if (pos+i > -1) {strip.setPixelColor(pos+i, r1, g1, b1);}
    if (pos-i > -1) {strip.setPixelColor(pos-i, r1, g1, b1);}
  }
  strip.show();
}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
 

