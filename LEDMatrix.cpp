#include <TinyWireM.h>
#include "LEDMatrix.h"

#include <avr/power.h>
#include <avr/sleep.h>

LEDMatrix::LEDMatrix() {
  address = DEFAULT_I2C_ADDR;
}

LEDMatrix::LEDMatrix(byte I2CAddress) {
  address = I2CAddress;
}

void LEDMatrix::ledCmd(const uint8_t x) {
  TinyWireM.beginTransmission(address);
  TinyWireM.write(x);
  TinyWireM.endTransmission();
}

void LEDMatrix::lowPowerMode() {
  power_timer1_disable();    // Disable unused peripherals
  power_adc_disable();       // to save power
  PCMSK |= _BV(PCINT1);      // Set change mask for pin 1
}

uint8_t LEDMatrix::translateRow(const uint8_t rowData) {
  uint8_t rowCommand = 0;
  // read bits from rowData left to right
  // and translate into LED matrix command
  for (int column=0; column < 8; column++) {
    int sourceBitPos = 7 - column;
    int targetBitPos = column==0 ? 7 : column -1;
    bitWrite(rowCommand, targetBitPos, bitRead(rowData, sourceBitPos));       
  }

  return rowCommand;
}

void LEDMatrix::beginFrame() {
  TinyWireM.beginTransmission(address);
  TinyWireM.write(0);  // start frame at row 0
}

void LEDMatrix::endFrame() {
  TinyWireM.endTransmission();
}

void LEDMatrix::drawRow(const uint8_t rowData) {
    TinyWireM.write(translateRow(rowData));
    TinyWireM.write(0);
}

void LEDMatrix::clear() { 
  TinyWireM.beginTransmission(address);
  for(uint8_t i=0; i<17; i++) TinyWireM.write(0);
  TinyWireM.endTransmission();
}

void LEDMatrix::oscillatorOn() {
    ledCmd(0x21);
}

void LEDMatrix::oscillatorOff() {
    ledCmd(0x20);
}

void LEDMatrix::displayOn(const int blinkType) {
    ledCmd(0x81 + blinkType);
}

void LEDMatrix::displayOff() {
    ledCmd(0x80 );
}

void LEDMatrix::setBrightness(const unsigned int level) {
  if (level > 15) {
    ledCmd(0xE0 | 15);
  }
  else {
    ledCmd(0xE0 | level);
  }
}

void LEDMatrix::initializeDisplay(const byte brightness, const byte blinkType) {
  TinyWireM.begin();         // I2C init
  clear();                   // Blank display
  oscillatorOn();
  setBrightness(brightness);
  displayOn(blinkType);
}

void LEDMatrix::drawFrame(const uint8_t data[ROWS_PER_FRAME][MAX_FRAMES] PROGMEM, int frameIndex, Position* pos) {
      //
      // draw the current frame
      beginFrame();
      
      int startingRow = 0;
      int numRowsToDraw = ROWS_PER_FRAME; 
      
      // if sliding down, draw blank lines before image
      if (pos->vOffset > 0 ) {
        for (int rows=0; rows < pos->vOffset; rows++) {
          drawRow(0);
        }
        numRowsToDraw = ROWS_PER_FRAME - pos->vOffset;
      }
      
      if (pos->vOffset < 0) {
        startingRow = abs(pos->vOffset);
      }
      
      for (int rowIndex=startingRow; rowIndex < numRowsToDraw; rowIndex++) {
        uint8_t curLine = pgm_read_byte(&(data[rowIndex][frameIndex]));
        drawRow(pos->slideRow(curLine));
      }
      
      // if sliding up, draw blank lines after image
      if (pos->vOffset < 0 ) {
        for (int rows=0; rows < abs(pos->vOffset); rows++) {
          drawRow(0);
        }
      }
      
      endFrame();
}                            
                              
void LEDMatrix::goToSleep() {
    oscillatorOff();
    GIMSK = _BV(PCIE);     // Enable pin change interrupt
    power_all_disable();   // All peripherals off
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sei();                 // Keep interrupts disabled
    sleep_mode();          // Power down CPU (pin 1 will wake)
    
    // Execution resumes here on wake.
    GIMSK = 0;             // Disable pin change interrupt
    power_timer0_enable(); // Re-enable timer
    power_usi_enable();    // Re-enable USI
    
    TinyWireM.begin();     // Re-init I2C
    clear();               // Blank display
    oscillatorOn();
}

//
// Button tap
ISR(PCINT0_vect) {} 
