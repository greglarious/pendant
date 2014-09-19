#include <TinyWireM.h>
#include "ledMatrixUtils.h"

// display object using default address
LEDMatrix matrix = LEDMatrix();

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
 { 250,       250, 0};

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
 { 250,       250, 0 };

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
 { 250,       250, 0 };


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
 { 120,       120,       120,       120, 0 };

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
  int longerSleep = 30000;
  int numAnimations = 4;  
  for (int repeat=0; repeat < 30; repeat++) {
    //
    // do animation patterns with short sleep between each alien

    matrix.drawAnimation(alien1Timing, alien1Data, numAnimations);
    matrix.clear();
    delay(shortSleep);

    matrix.drawAnimation(alien2Timing, alien2Data, numAnimations);
    matrix.clear();
    delay(shortSleep);
    
    matrix.drawAnimation(alien3Timing, alien3Data, numAnimations);
    matrix.clear();
    delay(shortSleep);
    
    matrix.drawAnimation(alien4Timing, alien4Data, numAnimations);
    matrix.clear();
    
    // longer sleep until repeat
    delay(longerSleep);
  }
   
  // go to permanent sleep mode and dont return until button pushed
  matrix.goToSleep();
}
