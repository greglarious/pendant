#include <TinyWireM.h>
#include "ledMatrixUtils.h"

// display object using default address
LEDMatrix matrix = LEDMatrix();
#define FRM_DELAY 100
#define SFRM_DLAY 80
//
//--------------alien 1 ------------------------------------
//
const  uint8_t alien1Data[ROWS_PER_FRAME][MAX_FRAMES] = { 
 { B00011000, B00011000 },
 { B00111100, B00111100 },
 { B01111110, B01111110 },
 { B11011011, B11011011 },
 { B11111111, B11111111 },
 { B00100100, B00100100 },
 { B01011010, B01011010 },
 { B10100101, B01000010 } };
const long alien1Timing[] = 
 { FRM_DELAY, FRM_DELAY, 0};

//
//--------------alien 2 ------------------------------------
//
const  uint8_t alien2Data[ROWS_PER_FRAME][MAX_FRAMES] = { 
 { B00000000, B00111100 },
 { B00111100, B01111110 },
 { B01111110, B11011011 },
 { B11011011, B11011011 },
 { B11011011, B01111110 },
 { B01111110, B00100100 },
 { B00100100, B00100100 },
 { B11000011, B00100100 } };
const long alien2Timing[] = 
 { FRM_DELAY, FRM_DELAY, 0 };

//
//--------------alien 3 ------------------------------------
//
const  uint8_t alien3Data[ROWS_PER_FRAME][MAX_FRAMES] = { 
 { B00100100, B00100100 },
 { B00100100, B10100101 },
 { B01111110, B11111111 },
 { B11011011, B11011011 },
 { B11111111, B11111111 },
 { B11111111, B01111110 },
 { B10100101, B00100100 },
 { B00100100, B01000010 } };
const long alien3Timing[] = 
 { FRM_DELAY, FRM_DELAY, 0 };


//
//--------------alien 4 ------------------------------------
//
const  uint8_t alien4Data[ROWS_PER_FRAME][MAX_FRAMES] = { 
 { B00111100, B00111100, B00111100, B00111100 },
 { B01111110, B01111110, B01111110, B01111110 },
 { B00110011, B10011001, B11001100, B01100110 },
 { B01111110, B01111110, B01111110, B01111110 },
 { B00111100, B00111100, B00111100, B00111100 },
 { B00000000, B00000000, B00000000, B00000000 },
 { B00001000, B00001000, B00000000, B00000000 },
 { B00000000, B00001000, B00001000, B00000000 } };
const long alien4Timing[] =
 { SFRM_DLAY, SFRM_DLAY, SFRM_DLAY, SFRM_DLAY, 0 };


//
//--------------pacman ------------------------------------
//
const  uint8_t pacmanData[ROWS_PER_FRAME][MAX_FRAMES] = { 
 { B00111100, B00111100, B00111100, B00111100},
 { B01111110, B01111110, B01111110, B01111110},
 { B11011111, B11011111, B11011111, B11011111},
 { B11111000, B11111100, B11111111, B11111111},
 { B11100000, B11100000, B11110000, B11111111},
 { B11111000, B11111100, B11111111, B11111111},
 { B01111110, B01111110, B01111110, B01111110},
 { B00111100, B00111100, B00111100, B00111100} };
const long pacmanTiming[] =
 { 120,       120,       120,       120, 0 };

//
//--------------ghost ------------------------------------
//
const  uint8_t ghostData[ROWS_PER_FRAME][MAX_FRAMES] = { 
 { B00011000, B00011000},
 { B01100110, B01100110},
 { B10000001, B10000001},
 { B10100101, B10010011},
 { B10000001, B10000001},
 { B10000001, B10000001},
 { B10101011, B10101011},
 { B01010101, B01010101} };
 
const long ghostTiming[] =
 { 200,       200, 0 };



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
  int shortSleep = 5000;
  int longerSleep = 15000;
  int numAnimations = 1;  
  
  for (int repeat=0; repeat < 30; repeat++) {
    matrix.fadeInOut(alien1Timing, alien1Data, numAnimations, 3);
    delay(shortSleep);

    matrix.fadeInOut(alien2Timing, alien2Data, numAnimations, 3);
    delay(shortSleep);
    
    matrix.fadeInOut(alien3Timing, alien3Data, numAnimations, 3);
    delay(shortSleep);
    
    matrix.fadeInOut(alien4Timing, alien4Data, numAnimations, 3);
    delay(shortSleep);
    
    matrix.fadeInOut(pacmanTiming, pacmanData, numAnimations, 3);
    delay(shortSleep);
    
    matrix.fadeInOut(ghostTiming, ghostData, numAnimations, 3);
    delay(shortSleep);
    
    // longer sleep until repeat
    delay(longerSleep);
  }
   
  // go to permanent sleep mode and dont return until button pushed
  matrix.goToSleep();
}
