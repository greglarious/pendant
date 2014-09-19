#include <TinyWireM.h>
#include "ledMatrixUtils.h"

#include <avr/power.h>
#include <avr/sleep.h>


LEDMatrix::LEDMatrix() {
  address = DEFAULT_I2C_ADDR;
}

LEDMatrix::LEDMatrix(int I2CAddress) {
  address = I2CAddress;
}

void LEDMatrix::ledCmd(uint8_t x) {
  TinyWireM.beginTransmission(address);
  TinyWireM.write(x);
  TinyWireM.endTransmission();
}

void LEDMatrix::lowPowerMode() {
  power_timer1_disable();    // Disable unused peripherals
  power_adc_disable();       // to save power
  PCMSK |= _BV(PCINT1);      // Set change mask for pin 1
}

uint8_t LEDMatrix::translateRow(uint8_t rowData) {
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

void LEDMatrix::drawRow(uint8_t rowData) {
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

void LEDMatrix::displayOn(int blinkType) {
    ledCmd(0x81 + blinkType);
}

void LEDMatrix::displayOff() {
    ledCmd(0x80 );
}

void LEDMatrix::setBrightness(unsigned int level) {
  if (level > 15) {
    level = 15;
  }
  
  ledCmd(0xE0 | level);
}

void LEDMatrix::initializeDisplay(int brightness, int blinkType) {
  TinyWireM.begin();         // I2C init
  clear();                   // Blank display
  oscillatorOn();
  
  setBrightness(brightness);
  
  displayOn(blinkType);
}

void LEDMatrix::drawAnimation(const long frameTiming[], 
                   const uint8_t frames[ROWS_PER_FRAME][MAX_FRAMES], 
                   int repititions ) {
  for (int repeatIndex=0; repeatIndex < repititions; repeatIndex++) {
    
    //
    // loop until we find a frameTiming of zero
    int frameIndex = 0;
    while (frameTiming[frameIndex] > 0) {
      //
      // draw the current frame
      beginFrame();
      for (int rowIndex=0; rowIndex < ROWS_PER_FRAME; rowIndex++) {
        drawRow(frames[rowIndex][frameIndex]);
      }
      endFrame();
      
      //
      // pause between frames
      delay(frameTiming[frameIndex]);
      frameIndex++;
    }
  }
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
