#include <TinyWireM.h>
#include "LEDMatrix.h"

#include <avr/power.h>
#include <avr/sleep.h>


LEDMatrix::LEDMatrix() {
  address = DEFAULT_I2C_ADDR;
}

LEDMatrix::LEDMatrix(int I2CAddress) {
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

uint8_t LEDMatrix::slideRow(const uint8_t rowData, const int offset) {
  if (offset >= 0) {
    return rowData >> offset;
  } else if (offset < 0) {
    return rowData << abs(offset);
  }
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

void LEDMatrix::initializeDisplay(const int brightness, const int blinkType) {
  TinyWireM.begin();         // I2C init
  clear();                   // Blank display
  oscillatorOn();
  setBrightness(brightness);
  displayOn(blinkType);
}


void LEDMatrix::drawFrame(const uint8_t data[ROWS_PER_FRAME][MAX_FRAMES] PROGMEM, int frameIndex, int hOffset, int vOffset) {
      //
      // draw the current frame
      beginFrame();
      for (int rowIndex=0; rowIndex < ROWS_PER_FRAME; rowIndex++) {
        uint8_t curLine = pgm_read_byte(&(data[rowIndex][frameIndex]));
        curLine = slideRow(curLine, hOffset);
        drawRow(curLine);
      }
      endFrame();
}                            
                              
void LEDMatrix::drawAnimation(const uint16_t timing[] PROGMEM, 
                              const uint8_t data[ROWS_PER_FRAME][MAX_FRAMES] PROGMEM, 
                              const int hMomentum,
                              const int vMomentum,
                              const int framesPerMove,
                              const int repititions) {
  int hOffset = 0;
  int vOffset = 0;
  
  // if moving right, start all the way left
  if (hMomentum > 0) hOffset = -7;
  
  // if moving left, start all the way right
  if (hMomentum < 0) hOffset = 7;
    
  int framesShown = 0;
  
  for (int repeatIndex=0; repeatIndex < repititions; repeatIndex++) {
    //
    // loop until we find end of frame timing data
    int frameIndex = 0;
    while (pgm_read_word(&timing[frameIndex]) != END_FRAMES) {
      //
      // draw the current frame
      drawFrame(data, frameIndex, hOffset, vOffset);
      
      framesShown++;
      if (framesShown >= framesPerMove) {
        framesShown = 0;
        
        //
        // do move
        hOffset+= hMomentum;
        if (hOffset > 8) {
          hOffset = -7;
        }
        if (hOffset < -8) {
          hOffset = 7;
        }
      }
      
      //
      // pause between frames
      delay(pgm_read_word(&timing[frameIndex]));
      frameIndex++;
    }
  }
}

void LEDMatrix::fadeInOut(const uint16_t timing[] PROGMEM, 
                          const uint8_t data[ROWS_PER_FRAME][MAX_FRAMES] PROGMEM,
                          const int numAnimations, 
                          const int fadeStep,
                          const long sleepWhenDone) {
    // fade dim to bright
    for (int b=0; b <= 15; b+= fadeStep) {
      setBrightness(b);
      drawAnimation(timing, data, 0, 0, 0, numAnimations);
    }
    // fade bright to dim
    for (int b=15; b >= 0 ; b-= fadeStep) {
      setBrightness(b);
      drawAnimation(timing, data, 0, 0, 0, numAnimations);
    }
    clear();
    delay(sleepWhenDone);
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
