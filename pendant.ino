#include <TinyWireM.h>
#include "ledMatrixUtils.h"

// display object using default address
LEDMatrix matrix = LEDMatrix();

//
//--------------alien 1 ------------------------------------
//
const  uint8_t alien1Data[ROWS_PER_FRAME][MAX_FRAMES] PROGMEM = { 
 { B00011000, B00011000 },
 { B00111100, B00111100 },
 { B01111110, B01111110 },
 { B11011011, B11011011 },
 { B11111111, B11111111 },
 { B00100100, B00100100 },
 { B01011010, B01011010 },
 { B10100101, B01000010 } };
const uint16_t alien1Timing[] PROGMEM = 
 { LFRM_DLAY, LFRM_DLAY, END_FRAMES};

//
//--------------alien 2 ------------------------------------
//
const  uint8_t alien2Data[ROWS_PER_FRAME][MAX_FRAMES] PROGMEM = { 
 { B00000000, B00111100 },
 { B00111100, B01111110 },
 { B01111110, B11011011 },
 { B11011011, B11011011 },
 { B11011011, B01111110 },
 { B01111110, B00100100 },
 { B00100100, B00100100 },
 { B11000011, B00100100 } };
const uint16_t alien2Timing[] PROGMEM = 
 { LFRM_DLAY, LFRM_DLAY, END_FRAMES};

//
//--------------alien 3 ------------------------------------
//
const  uint8_t alien3Data[ROWS_PER_FRAME][MAX_FRAMES] PROGMEM = { 
 { B00100100, B00100100 },
 { B00100100, B10100101 },
 { B01111110, B11111111 },
 { B11011011, B11011011 },
 { B11111111, B11111111 },
 { B11111111, B01111110 },
 { B10100101, B00100100 },
 { B00100100, B01000010 } };
const uint16_t alien3Timing[] PROGMEM = 
 { LFRM_DLAY, LFRM_DLAY, END_FRAMES };


//
//--------------alien 4 ------------------------------------
//
const  uint8_t alien4Data[ROWS_PER_FRAME][MAX_FRAMES] PROGMEM = { 
 { B00111100, B00111100, B00111100, B00111100 },
 { B01111110, B01111110, B01111110, B01111110 },
 { B00110011, B10011001, B11001100, B01100110 },
 { B01111110, B01111110, B01111110, B01111110 },
 { B00111100, B00111100, B00111100, B00111100 },
 { B00000000, B00000000, B00000000, B00000000 },
 { B00001000, B00001000, B00000000, B00000000 },
 { B00000000, B00001000, B00001000, B00000000 } };
const uint16_t alien4Timing[] PROGMEM =
 { MFRM_DLAY, MFRM_DLAY, MFRM_DLAY, MFRM_DLAY, END_FRAMES };


//
//--------------pacman ------------------------------------
//
const  uint8_t pacmanData[ROWS_PER_FRAME][MAX_FRAMES] PROGMEM = { 
 { B00111100, B00111100, B00111100, B00111100, B00111100, B00111100 },
 { B01111110, B01111110, B01111110, B01111110, B01111110, B01111110 },
 { B11011110, B11011111, B11011111, B11011111, B11011111, B11011111 },
 { B11111000, B11111100, B11111111, B11111111, B11111111, B11111100 },
 { B11100000, B11100000, B11110000, B11111111, B11110000, B11100000 },
 { B11111000, B11111100, B11111111, B11111111, B11111111, B11111100 },
 { B01111110, B01111110, B01111110, B01111110, B01111110, B01111110 },
 { B00111100, B00111100, B00111100, B00111100, B00111100, B00111100 } };
const uint16_t pacmanTiming[] PROGMEM =
 { SFRM_DLAY, SFRM_DLAY, SFRM_DLAY, SFRM_DLAY, SFRM_DLAY, SFRM_DLAY, END_FRAMES };
 
 
//
//--------------ghost ------------------------------------
//
const  uint8_t ghostData[ROWS_PER_FRAME][MAX_FRAMES] PROGMEM = { 
 { B00011000, B00011000},
 { B01100110, B01100110},
 { B10000001, B10000001},
 { B10100101, B10010011},
 { B10000001, B10000001},
 { B10000001, B10000001},
 { B10101011, B10101011},
 { B01010101, B01010101} };
 
const uint16_t ghostTiming[] PROGMEM =
 { LFRM_DLAY, LFRM_DLAY, END_FRAMES };

//
// initial setup
//
void setup() {
  matrix.lowPowerMode();
  matrix.initializeDisplay(12, LEDMatrix::BLINK_NONE);
}


//
// main loop
//
void loop() {
  const int shortSleep = 3000;
  const int longerSleep = 10000;
  const int numAnimations = 2;
  const int fadeStep = 2;
  const int repeatCount = 2;
  
  for (int repeat=0; repeat < repeatCount ; repeat++) {
    matrix.fadeInOut(alien1Timing, alien1Data, numAnimations, fadeStep, shortSleep);
    matrix.fadeInOut(alien2Timing, alien2Data, numAnimations, fadeStep, shortSleep);
    matrix.fadeInOut(alien3Timing, alien3Data, numAnimations, fadeStep, shortSleep);
    matrix.fadeInOut(alien4Timing, alien4Data, numAnimations, fadeStep, shortSleep);
    matrix.fadeInOut(pacmanTiming, pacmanData, numAnimations, fadeStep, shortSleep);
    matrix.fadeInOut(ghostTiming,  ghostData,  numAnimations, fadeStep, longerSleep);
  }
   
  // go to permanent sleep mode and dont return until button pushed
  matrix.goToSleep();
}
