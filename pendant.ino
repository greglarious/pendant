#define BRIGHTNESS   12   // 0=min, 15=max
#define I2C_ADDR     0x70 // Edit if backpack A0/A1 jumpers set

#include <TinyWireM.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include "ledUtils.h"

//
//--------------alien 1 ------------------------------------
//
const  uint8_t alien1_data[ROWS_PER_FRAME][MAX_FRAMES] = { 
 { B00011000, B00011000 },
 { B00111100, B00111100 },
 { B01111110, B01111110 },
 { B11011011, B11011011 },
 { B11111111, B11111111 },
 { B00100100, B00100100 },
 { B01011010, B01011010 },
 { B10100101, B01000010 } };
const uint8_t alien1_timing[] = 
 { 250,       250};

//
//--------------alien 2 ------------------------------------
//
const  uint8_t alien2_data[ROWS_PER_FRAME][MAX_FRAMES] = { 
 { B00000000, B00111100 },
 { B00111100, B01111110 },
 { B01111110, B11011011 },
 { B11011011, B11011011 },
 { B11011011, B01111110 },
 { B01111110, B00100100 },
 { B00100100, B00100100 },
 { B11000011, B00100100 } };
const uint8_t alien2_timing[] = 
 { 250,       250 };

//
//--------------alien 3 ------------------------------------
//
const  uint8_t alien3_data[ROWS_PER_FRAME][MAX_FRAMES] = { 
 { B00100100, B00100100 },
 { B00100100, B10100101 },
 { B01111110, B11111111 },
 { B11011011, B11011011 },
 { B11111111, B11111111 },
 { B11111111, B01111110 },
 { B10100101, B00100100 },
 { B00100100, B01000010 } };
const uint8_t alien3_timing[] = 
 { 250,       250 };


//
//--------------alien 4 ------------------------------------
//
const  uint8_t alien4_data[ROWS_PER_FRAME][MAX_FRAMES] = { 
 { B00111100, B00111100, B00111100, B00111100 },
 { B01111110, B01111110, B01111110, B01111110 },
 { B00110011, B10011001, B11001100, B01100110 },
 { B01111110, B01111110, B01111110, B01111110 },
 { B00111100, B00111100, B00111100, B00111100 },
 { B00000000, B00000000, B00000000, B00000000 },
 { B00001000, B00001000, B00000000, B00000000 },
 { B00000000, B00001000, B00001000, B00000000 } };
const uint8_t alien4_timing[] =
 { 120,       120,       120,       120 };

//
// initial setup
//
void setup() {
  lowPowerMode();
  PCMSK |= _BV(PCINT1);      // Set change mask for pin 1
  initializeDisplay(true, BRIGHTNESS, false);
}

//
// main loop
//
void loop() {
  drawAnimation(alien1_data, alien1_timing, 3);
  drawAnimation(alien2_data, alien2_timing, 3);
  drawAnimation(alien3_data, alien3_timing, 3);
  drawAnimation(alien4_data, alien4_timing, 3);
   
  goToSleep();
  // returns here after wakeup from sleep
}
