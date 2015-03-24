#include <pinduino.h>

pinduino pd;

#define UC_RED 0
#define UC_YELLOW 1
#define UC_BLUE 2
#define UC_GREEN 3

#define FLASHER_POLLING_PERIOD 50
#define UNDERCAB_FLASH_PERIOD 150
#define UNDERCAB_FLASH_PULSE_COUNT 1

unsigned long undercab_flasherpoll_waituntilmillis[4];

byte undercab_flashes[4];
byte current_undercab_color;
unsigned long undercab_waituntilmillis;

unsigned long currentMillis;

void setup() {
  pd.pinState()->reset();
  undercab_waituntilmillis = 0;
  undercab_flasherpoll_waituntilmillis[UC_RED] = 0;
  undercab_flasherpoll_waituntilmillis[UC_YELLOW] = 0;
  undercab_flasherpoll_waituntilmillis[UC_BLUE] = 0;
  undercab_flasherpoll_waituntilmillis[UC_GREEN] = 0;
  current_undercab_color = UC_RED;
  undercab_flashes[UC_RED] = 0;
  undercab_flashes[UC_YELLOW] = 0;
  undercab_flashes[UC_BLUE] = 0;
  undercab_flashes[UC_GREEN] = 0;
}

void loop() {
  currentMillis = millis();

  if ((currentMillis > undercab_flasherpoll_waituntilmillis[UC_RED]) || (currentMillis > undercab_flasherpoll_waituntilmillis[UC_YELLOW]) || (currentMillis > undercab_flasherpoll_waituntilmillis[UC_BLUE]) || (currentMillis > undercab_flasherpoll_waituntilmillis[UC_GREEN])) {
    pd.pinState()->reset();
    pd.pinState()->update();
  }

  if (currentMillis > undercab_flasherpoll_waituntilmillis[UC_RED]) {  
    //RED FLASHER
    if ( pd.pinState()->J6(1) ){
      undercab_flashes[UC_RED] += UNDERCAB_FLASH_PULSE_COUNT;
      undercab_flasherpoll_waituntilmillis[UC_RED] = currentMillis + FLASHER_POLLING_PERIOD;
    }
  }
  
  if (currentMillis > undercab_flasherpoll_waituntilmillis[UC_YELLOW]) {
    //YELLOW FLASHER
    if ( pd.pinState()->J6(2) ){ 
      undercab_flashes[UC_YELLOW] += UNDERCAB_FLASH_PULSE_COUNT;
      undercab_flasherpoll_waituntilmillis[UC_YELLOW] = currentMillis + FLASHER_POLLING_PERIOD;
    }
  }
  
  if (currentMillis > undercab_flasherpoll_waituntilmillis[UC_GREEN]) {
    //GREEN FLASHER
    if ( pd.pinState()->J6(3) ){ 
      undercab_flashes[UC_GREEN] += UNDERCAB_FLASH_PULSE_COUNT;
      undercab_flasherpoll_waituntilmillis[UC_GREEN] = currentMillis + FLASHER_POLLING_PERIOD;
    }
  }
  
  if (currentMillis > undercab_flasherpoll_waituntilmillis[UC_BLUE]) {
    //BLUE FLASHER
    if ( pd.pinState()->J6(4) ){ 
      undercab_flashes[UC_BLUE] += UNDERCAB_FLASH_PULSE_COUNT;
      undercab_flasherpoll_waituntilmillis[UC_BLUE] = currentMillis + FLASHER_POLLING_PERIOD;
    }
  }  

  if (currentMillis > undercab_waituntilmillis) {
    pd.rgbLED1()->clear();
    
    //does anything have flashes left?
    if ((undercab_flashes[UC_RED] > 0) || (undercab_flashes[UC_YELLOW] > 0) || (undercab_flashes[UC_GREEN] > 0) || (undercab_flashes[UC_BLUE] > 0)) {
      for (int iLoop = 0; iLoop < 4; iLoop++) { 
        //Gonna check all 4 colors of undercab flasher, but the counter is just to ensure a loop 4 times if necessary
        if (undercab_flashes[current_undercab_color] > 0) {
          switch(current_undercab_color) {
            case UC_RED:
              pd.rgbLED1()->set("red");
              break;
            case UC_YELLOW:
              pd.rgbLED1()->set("yellow");
              break;
            case UC_GREEN:
              pd.rgbLED1()->set("green");
              break;
            case UC_BLUE:
              pd.rgbLED1()->set("blue");
              break;
          } //end switch
          undercab_flashes[current_undercab_color] -= 1;
          advanceUndercabColor();
          undercab_waituntilmillis = currentMillis + UNDERCAB_FLASH_PERIOD;
          break;
        } else {
          advanceUndercabColor();
        } //end if
      } //end for
    }
  } //end if
  
}

void advanceUndercabColor() {
  if (current_undercab_color >= 3) {
    current_undercab_color = 0;
  } else {
    current_undercab_color += 1;
  }
}

void checkPinStates(){
  
  //MULTIBALL FLASHER
  if ( pd.pinState()->J6(5) ){
  }

  //LEFT RAMP FLASHER
  if ( pd.pinState()->J6(6) ){
  }

  //RIGHT RAMP FLASHER
  if ( pd.pinState()->J6(7) ){
  }

  //POP FLASHER
  if ( pd.pinState()->J6(8) ){
  }

}


