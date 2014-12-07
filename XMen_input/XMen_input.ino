//Eric Lyons 2014
//Note to self:  Play more pinball!

#include <Adafruit_NeoPixel.h>

// Number of LEDs in the NeoPixel Light Strip
#define L_START    0
#define L_END      81
#define R_START    82
#define R_END      150

#define N_LEDS     151

// The LED Signal Pin for the NeoPixel Light Strip
#define LEDPIN     4

//Pins for standard LED strips
#define RED  8
#define GRN  9
#define BLU  10

//Number of pins reading data
#define numPins 16

// Adafruit_NeoPixel (# of LEDs, Signal Pin, Refresh Rate)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, LEDPIN, NEO_GRB + NEO_KHZ800);

// Arduino INPUT pins Digital 2-13 used (mapped to pinStates 0..11)
int pins[] = { 23,25,27,29,31,33,35,37,39,41,43,45,47,49,51,53 };
// pin 0:  Flash: Pop Bumper Fl. (BLK-BRN)
// pin 1:  Orbit Diverter (BLK-RED)
// pin 2:  Iceman Motor (BLK-ORG)
// pin 3:  Flash: Backpanel Left (x3) (BLK-YEL)
// pin 4:  Flash: Backpanel Left (x3) (BLK-GRN)
// pin 5:  Flash: Magneto Spot Light (BLK-BLU)
// pin 6:  Flash: Bottom Arch x2 (BLK-VIO)
// pin 7:  Flash: Magneto Figure (BLK-GRY)
// pin 8:  Flash: Disc Blue x2 (VIO-WHT)
// pin 9:  Flash: Disc Red x2 (VIO-ORG)
// pin 10: Flash: Right side (VIO-RED)
// pin 11: Flash: Left side (x2) (VIO-BRN)
// pin 12: Coil Optional (VIO-GRY)
// pin 13: Disc Motor Power (VIO-BLK)
// pin 14: Flash: Magneto Left/right x2 (VIO-BLU)
// pin 15: Flash: Wolverine (VIO-GRN)
int pinStates[numPins];

int span = 6;
int pos = N_LEDS+span, dir = -1; // Position, direction of "eye"
//int pos = 0-span; // Position, direction of "eye"
int chaseSpeed = 10; //speed of chase lights
int cr = 255;
int cg = 0;
int cb = 0;
long count=0;
int bg_chase_on = 1;
unsigned long timeLastEvent = 0; // time last event was last triggered
int startChaseWaitTime = 15000; //Amount of time to wait before chase lights start up again 1000 == 1 second
//track the number of times various pins have been triggered.  This will be a number higher than one, depending on the
//length of time an event occurs (e.g., flasher).  Hope that these can be used to determine relative events.  
//E.g., light1 flashed once, light2 flashed twice: trigger event

void setup() {
  // initialize pins as an input:
  for (int i = 0; i < numPins; i = i + 1) {
    pinMode(pins[i], INPUT); 
  }
  pinMode(RED, OUTPUT);
  pinMode(GRN, OUTPUT);
  pinMode(BLU, OUTPUT);
  digitalWrite(RED, LOW);
  digitalWrite(GRN, LOW);
  digitalWrite(BLU, LOW);  resetPinStates();
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600); // debugging logging
}

void loop(){
  if (bg_chase_on){backgroundChase();}
  updatePinStates();
//   Print the pin states out to serial 
//  printPinStates();
  checkPinStates();
  if (millis()-timeLastEvent > startChaseWaitTime) {bg_chase_on=1;}
}

void checkPinStates(){
  int trigger =0;
  
  if (pinStates[0]>1){
//    for (int i = 0; i < 7; i = i + 1) {
//      explosion (255,random(100)+50,0, random(5)+5, random(strip.numPixels()), 100);
//    }
//    trigger =1;
  }
  if (pinStates[1]>1){ 
  }
 if (pinStates[2]>1){ 
//      spreadInFromPoint(N_LEDS,255, 0, 0, 200, 100);
//      spreadOutToPoint(0,255, 0, 0, 300);
    completeChase2(0,0,255, 255,255,255,strip.numPixels()/6, 0, -11);
    trigger =1;
  }
  if (pinStates[3]>1){ 
    spreadInFromPoint(R_START,150, 150, 255, 0, 0);
    fadeOut(100);
    trigger =1;
  }
  if (pinStates[4]>1){
    spreadInFromPoint(R_START,255, 100, 0, 0, 0);
    fadeOut(100);
    trigger =1;
  }
  if (pinStates[5]>1 and bg_chase_on==0 ){
    colorWipe(255,0,0,255);
    spreadOutFromPoint (R_START, 0);
    trigger =1;
  }
  if (pinStates[6]>1){
    colorWipe(255, 255, 0, 255);
    delay(20);
    clearStrip();
//      stripFade(255, 0, 0, 200, 10);
//      completeChase2(255,0,0, 255,255,0,strip.numPixels()/4, 3, -1);
      trigger =1;
  }
  if (pinStates[7]>1){ 
//      colorWipe(255, 0, 0, 100, 255);
//      stripFade(255, 0, 0, 300, 10);
//      completeChase2(255,0,0, 255,255,0,strip.numPixels()/4, 3, -1);
    colorWipe(255, 0, 0, 255);
    delay(20);
    trigger =1;
  }
  if (pinStates[8]>1){ 
      trigger =1;
  }
  if (pinStates[9]>1){
//      stripFade(255, 255, 0, 200, 10);
      completeChase2(255,255,0, 0,0,255,strip.numPixels()/4, 0, 1);
      trigger =1;
  }
  if (pinStates[10]>1){ 
//      spreadInFromPoint(N_LEDS,255, 0, 0, 200, 100);
 //     spreadOutToPoint(0,255, 0, 0, 300);
      completeChase2(255,0,0, 0,0,255,strip.numPixels()/8, 0, 1);
      trigger =1;
  }
  if (pinStates[11]>1){
      completeChase2(0,0,255, 255,255,0,N_LEDS/8, 0, -1);
      trigger=1;
    }
  if (pinStates[12]>1){
  }
  if (pinStates[13]>1){
  }
  if (pinStates[14]>1){
    spreadInFromPoint2 (R_START, 255,0,0,0,0,255, 0);
    fadeOut(100);
    trigger=1;
  }
  if (pinStates[15]>1){
  }

//trigger is to take care of any cleanup after a sequence has been triggered.
 if (trigger) {
   clearStrip();
   resetPinStates();
   trigger =0;
   pos = N_LEDS+span;
   bg_chase_on = 0;
   timeLastEvent = millis();
 }

}

//helps with debugging
void printPinStates() {
  int i;
  for (i = 0; i < numPins; i = i + 1) {
    Serial.print(pinStates[i]);    
    Serial.print(" ");
  }
  Serial.println();
}

//set it all back to 0
void resetPinStates(){
  int i;
  for (i = 0; i < numPins; i = i + 1) {
    pinStates[i] = 0;    
  }
  strip.setBrightness(255);
}

//scan the inputs for flashers being triggered
void updatePinStates(){
  int i;
  for (i = 0; i < numPins; i = i + 1) {
    int state = digitalRead(pins[i]);
    if (state == 1) { //circuit being checked has been activated
      pinStates[i] = pinStates[i] + 1;
    }
  }
}

//Control static LED light strip
void staticLED (int r, int g, int b, int time) {
  if (r){digitalWrite(RED, HIGH);}
  if (g){digitalWrite(GRN, HIGH);}
  if (b){digitalWrite(BLU, HIGH);}
  delay(time);
  digitalWrite(RED, LOW);
  digitalWrite(GRN, LOW);
  digitalWrite(BLU, LOW);
}

//return true if any pinStates are true
int anyPinStates() {
  return 0;
  int pinState=0;
  for (int i = 0; i < numPins; i = i + 1) {
    if (pinStates[i]>0) {pinState = 1;}    
  }
  return pinState;
}

void completeChase(int r, int g, int b, int span, int chaseSpeed, int dir) {
  int pos;
  if (dir > 0) { pos=strip.numPixels()+span;} 
  else  { pos=0-span;} 
  for (int i = 0; i < strip.numPixels()+span; i++) {
    colorBand (r,g,b, span, pos);
    delay(chaseSpeed);
    // Rather than being sneaky and erasing just the tail pixel,
    // it's easier to erase it all and draw a new one next time.
    for(int j=-span; j<= span; j++) strip.setPixelColor(pos+j, 0,0,0);
    if (dir > 0) {pos--;}
    else {pos++;}
  }
}

void completeChase2(float r1, float g1, float b1, float r2, float g2, float b2, float span, int chaseSpeed, int dir) {
  int pos;
  if (dir > 0) { pos=strip.numPixels()+span;} 
  else  { pos=0-span;} 
  //color step size
  float rcs = abs(r1-r2)/(strip.numPixels());
  if (r2 > r1){rcs=rcs*-1;}
  float gcs = abs(g1-g2)/(strip.numPixels());
  if (g2 > g1){gcs=gcs*-1;}
  float bcs = abs(b1-b2)/(strip.numPixels());
  if (b2 > b1){bcs=bcs*-1;}
  
  for (int i = 0; i < strip.numPixels()+span*2; i++) {
    float r = r1;
    float g = g1;
    float b = b1;
    if (i > span) {
      r = r1-(rcs*(i-span));
      g = g1-(gcs*(i-span));
      b = b1-(bcs*(i-span)); 
    }
    colorBand (r,g,b,span, pos);
    if (chaseSpeed){delay(chaseSpeed);}
    // Rather than being sneaky and erasing just the tail pixel,
    // it's easier to erase it all and draw a new one next time.
    for(int j=-span; j<= span; j++) 
    {
      strip.setPixelColor(pos+j, 0,0,0);
    }
    if (dir > 0) {pos--;}
    else {pos++;}
  }
}

//fade out the strip
void fadeOut (float steps) {
  if (steps < 1){steps=1;}
  uint8_t origBrightness = strip.getBrightness();
  float brightStep = origBrightness/steps; 
  
  for (int i=0; i<steps; i++) {
    int brightness = origBrightness-(brightStep+brightStep*i);
    strip.setBrightness(brightness);
    updatePinStates();
    strip.show();
  }
  colorWipe(0,0,0,1);
}

void backgroundChase() {
  spreadInFromPoint(R_START,150, 150, 255, 1, 1);
  updatePinStates();
  fadeOut(100);
  updatePinStates();
  delay(10);
  updatePinStates();
  colorWipe(150, 150, 255,150);
  updatePinStates();
  fadeOut(50);
  updatePinStates();
  delay(100);
  updatePinStates();
  colorWipe(150, 150, 255,100);
  updatePinStates();
  fadeOut(50);
  updatePinStates();
  delay(200);
  updatePinStates();
  colorWipe(255,0,0,50);
  updatePinStates();
  fadeOut(200);
  updatePinStates();
  for (int i=0; i<100; i=i+1){
      updatePinStates();
      delay(10);
  }  
}

void backgroundChase_old() {
  colorBand (cr,cg,cb,100, pos);
  delay(chaseSpeed);
  // Rather than being sneaky and erasing just the tail pixel,
  // it's easier to erase it all and draw a new one next time.
  for(int j=-span; j<= span; j++) strip.setPixelColor(pos+j, 0,0,0);


  pos += dir;
  if(pos < 0) { 
    pos = strip.numPixels()+span;
    if (cr==255 && cg == 0) {
     cr=255;
     cg=255;
     cb=255;
    }
    else {
      cr=150;
      cg=150;
      cb=255;
     }  
    }
}


void colorBand(int r, int g, int b, uint8_t x, int pos) {
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
    if (pos+i > -1) {strip.setPixelColor(pos+i, r1, g1, b1);}
    if (pos-i > -1) {strip.setPixelColor(pos-i, r1, g1, b1);}
  }
  strip.show();
}


void explosion(int r, int g, int b, int span, int pos, int time) {
  double s = 100/span;
  clearStrip();
    if (r <0 ) {r=0;}
    if (g <0 ) {g=0;}
    if (b <0 ) {b=0;}
    if (r >255 ) {r=255;}
    if (g >255 ) {g=255;}
    if (b >255 ) {b=255;}
  strip.setBrightness(255);
    strip.show();

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
    if (pos+i > -1) {strip.setPixelColor(pos+i, r1, g1, b1);}
    if (pos-i > -1) {strip.setPixelColor(pos-i, r1, g1, b1);}
  }
    fadeOut(50);
}

// clear strip 
void clearStrip() {
  colorWipe(0,0,0,0);
}

// Fill the dots one after the other with a color
void colorWipe(int r, int g, int b, int brightness) {
  if (brightness < 1) {brightness = 1;}
  if (brightness > 255) {brightness = 255;}
  if (r<0) {r=0;}
  if (r>255) {r=255;}
  if (g<0) {g=0;}
  if (g>255) {g=255;}
  if (b<0) {b=0;}
  if (b>255) {b=255;}
  for(int i=0; i<N_LEDS; i++) {
      strip.setPixelColor(i, r, g, b);
  }
  strip.setBrightness(brightness);
  strip.show();
}

// start lights at middle of strip and expand light to ends of strip
// spreading of light takes time (time)
// holding of full lights for time (hold)

void spreadInFromPoint (int start_led, int r, int g, int b, int time, int hold) {
  //Figure out the distance from the furthest end
  int middle_led = N_LEDS/2;
  int num_positions = 0;  // number of positions between the start_led and the furthest end of strip
  if (start_led < middle_led) {num_positions = N_LEDS-start_led+1;}
  else {num_positions = start_led+1;}

  //time between turning LEDs on 
  int expand_time = time/num_positions;
  
  strip.setBrightness(255);
  for(int i=0; i<num_positions; i++) {
     // Serial.println(i);
      updatePinStates();
      strip.setPixelColor(start_led + i, r, g, b);
      strip.setPixelColor(start_led - i, r, g, b);
      strip.show();
      delay(expand_time);
  }
  delay(hold);
}
 
//like spreadInFromPoint, but takes a starting olor and fades to an ending color
void spreadInFromPoint2 (int start_led, float r1, float g1, float b1, float r2, float g2, float b2, int time) {
  //Figure out the distance from the furthest end
  int middle_led = N_LEDS/2;
  int num_positions = 0;  // number of positions between the start_led and the furthest end of strip
  if (start_led < middle_led) {num_positions = N_LEDS-start_led+1;}
  else {num_positions = start_led+1;}

  //calcuate color changes
  float rcs = abs(r1-r2)/num_positions;
  if (r2 > r1){rcs=rcs*-1;}
  float gcs = abs(g1-g2)/num_positions;
  if (g2 > g1){gcs=gcs*-1;}
  float bcs = abs(b1-b2)/num_positions;
  if (b2 > b1){bcs=bcs*-1;}

  //time between turning LEDs on 
  int expand_time = time/num_positions;
  
  strip.setBrightness(255);
  for(int i=0; i<num_positions; i++) {
    float r = r1;
    float g = g1;
    float b = b1;
    r = r1-(rcs*i);
    g = g1-(gcs*i);
    b = b1-(bcs*i); 
    updatePinStates();
    strip.setPixelColor(start_led + i, r, g, b);
    strip.setPixelColor(start_led - i, r, g, b);
    strip.show();
    delay(expand_time);
  }
} 


 //with full lights, fade from point till you reach ends of light strip

void spreadOutFromPoint (int start_led, int time) {
  //Figure out the distance from the furthest end
  int middle_led = N_LEDS/2;
  int num_positions = 0;  // number of positions between the start_led and the furthest end of strip
  if (start_led < middle_led) {num_positions = N_LEDS-start_led+1;}
  else {num_positions = start_led+1;}

  //time between turning LEDs on 
  int expand_time = time/num_positions;
  
  for(int i=0; i<num_positions; i++) {
     // Serial.println(i);
      strip.setPixelColor(start_led + i, 0, 0, 0);
      strip.setPixelColor(start_led - i, 0, 0, 0);
      strip.show();
      delay(expand_time);
  }
}

//with full lights, fade ends till you reach a point in light strip
void spreadOutToPoint (int start_led, int r, int g, int b, int time) {
  strip.setBrightness(255);
  //set strip to a color
  for (int i = 0; i<N_LEDS; i++) {
      strip.setPixelColor(i, r, g, b);
  }
  strip.show();
  //Figure out the distance from the furthest end
  int middle_led = N_LEDS/2;
  int num_positions = 0;  // number of positions between the start_led and the furthest end of strip
  if (start_led < middle_led) {num_positions = N_LEDS-start_led+1;}
  else {num_positions = start_led+1;}

  //time between turning LEDs on 
  int expand_time = time/num_positions;
  
  for(int i=num_positions; i>0; i--) {
     // Serial.println(i);
      strip.setPixelColor(start_led + i, 0, 0, 0);
      strip.setPixelColor(start_led - i, 0, 0, 0);
      strip.show();
      delay(expand_time);
  }
}


//fade in/out strip over 'time'.  Hold bright for time == 'hold'
//brightness 0-255
void stripFade (int r, int g, int b, int time) {
  int steps = 50;
  int wait = time/steps;
  fadeIn(r, g, b, time);
  //fade out
  fadeOut(steps);
}

void fadeIn (int r, int g, int b, int time ) {
  int steps = 50;
  int wait = time/steps;
  if (wait < 1) {wait = 0;}
  int brightStep = 255/steps; 
  //fade in
  colorWipe(r, g, b, 1); 
  for (int i=0; i<steps; i++) {
    colorWipe(r, g, b, brightStep+brightStep*i); 
  }
  //hold at max brightness
  colorWipe(r, g, b, 255); 
}



//rainbow happy fun time!
void rainbow(uint8_t wait) {
  uint16_t i, j;
 
  for(j=0; j<256*5; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(strip.numPixels()-i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
 
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
 
  for(j=0; j<256*5; j++) { 
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(strip.numPixels()-i, Wheel(((i * 256 / strip.numPixels()) + j*2) & 255));
    }
    strip.show();
    delay(wait);
  }
}
 
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

