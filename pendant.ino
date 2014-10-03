#include <TinyWireM.h>
#include "LEDMatrix.h"

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
 { MFRM_DLAY, MFRM_DLAY, MFRM_DLAY, MFRM_DLAY, MFRM_DLAY, MFRM_DLAY, END_FRAMES };
 
 
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
 { B01010101, B10101010} };
 
const uint16_t ghostTiming[] PROGMEM =
 { LFRM_DLAY, LFRM_DLAY, END_FRAMES };
 
 //
//--------------smiley ------------------------------------
//
const  uint8_t smileyData[ROWS_PER_FRAME][MAX_FRAMES] PROGMEM = { 
 { B01000010, B01000010, B01000010, B01000010, B01000010, B01000010, B01000010, B01000010, B01000010, B01000010},
 { B10100101, B10100101, B10100101, B10100101, B10100101, B10100101, B10100101, B10100101, B11100111, B10100101},
 { B01000010, B01000010, B01000010, B01000010, B01000010, B01000010, B01000010, B01000010, B01000010, B01000010},
 { B00011000, B00011000, B00011000, B00011000, B00011000, B00011000, B00011000, B00011000, B00011000, B00011000},
 { B00000000, B00000000, B10000001, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000},
 { B00000000, B11000011, B01000010, B11000011, B01011010, B00011000, B00000000, B00000000, B00000000, B00000000},
 { B11111111, B00111100, B00111100, B00111100, B00111100, B00100100, B01100110, B11111111, B11111111, B11111111},
 { B00000000, B00000000, B00000000, B00000000, B00000000, B00011000, B00011000, B00000000, B00000000, B00000000} };
 
const uint16_t smileyTiming[] PROGMEM =
 { LFRM_DLAY, LFRM_DLAY, LFRM_DLAY, LFRM_DLAY, LFRM_DLAY, LFRM_DLAY, LFRM_DLAY, LFRM_DLAY, LFRM_DLAY, LFRM_DLAY, END_FRAMES };


 //
//--------------fireworks ------------------------------------
//
const  uint8_t fireworksData[ROWS_PER_FRAME][MAX_FRAMES] PROGMEM = { 
 { B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00010000, B00000000},
 { B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00010000, B10101010, B00000000},
 { B00000000, B00000000, B00000000, B00000000, B00000000, B00100000, B00000000, B00010000, B00101000, B01000100, B00000000},
 { B00000000, B00000000, B00000000, B00000000, B00100000, B00000000, B00010000, B00101000, B01010100, B10000010, B00000000},
 { B00000000, B00000000, B00000000, B00100000, B00000000, B00000000, B00000000, B00010000, B00101000, B01000100, B00000000},
 { B00000000, B00000000, B01000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00010000, B10101010, B00000000},
 { B00000000, B01000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00010000, B00000000},
 { B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00010000, B00000000} };
 
const uint16_t fireworksTiming[] PROGMEM =
 { SFRM_DLAY, MFRM_DLAY, LFRM_DLAY, LFRM_DLAY, VFRM_DLAY, VFRM_DLAY, VFRM_DLAY, MFRM_DLAY, MFRM_DLAY, MFRM_DLAY, MFRM_DLAY, END_FRAMES };

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
  for ( int numReps = 0; numReps < 3; numReps++) {
    matrix.setBrightness(10);
    
    // pacman runs right
    matrix.drawAnimation(pacmanTiming, pacmanData, 1, 0, false, 3, 8);
    

    // pacman backs left faster
    matrix.drawAnimation(pacmanTiming, pacmanData, -2, 0, true, 3, 4);
    // ghost chases left 
    matrix.drawAnimation(ghostTiming, ghostData, -1, 0, false, 2, 16);
  
    // bright fireworks
    matrix.setBrightness(12);
    matrix.drawAnimation(fireworksTiming, fireworksData, 1, false);
    matrix.drawAnimation(fireworksTiming, fireworksData, 1, true);
    matrix.drawAnimation(fireworksTiming, fireworksData, 1, false);
    matrix.drawAnimation(fireworksTiming, fireworksData, 1, true);
  
    // smiley
    matrix.setBrightness(8);
    matrix.drawAnimation(smileyTiming, smileyData, 3, false);
      
    // drop alien 1 from the top
    matrix.drawAnimation(alien1Timing, alien1Data, 0, 1, false, 2, 16);
  
    // alien 2 rises from the bottom
    matrix.drawAnimation(alien2Timing, alien2Data, 0, -1, false, 2, 16);
   
    // alien 3 upper left to center
    matrix.drawAnimation(alien3Timing, alien3Data, 1, 1, false, 2, 8);
    // alien 3 stay and dance a bit
    matrix.drawAnimation(alien3Timing, alien3Data, 4, false);
   
    // alien 4 fade in/out 
    matrix.fadeInOut(alien4Timing, alien4Data, 1, 2, 3000);

    delay(10000);
  }
     
  // go to permanent sleep mode and dont return until button pushed
  matrix.goToSleep();
}
