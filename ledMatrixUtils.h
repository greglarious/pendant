#define ROWS_PER_FRAME 8
#define MAX_FRAMES 8

void lowPowerMode() {
  power_timer1_disable();    // Disable unused peripherals
  power_adc_disable();       // to save power
}

void ledCmd(uint8_t x) { // Issue command to LED backback driver
  TinyWireM.beginTransmission(I2C_ADDR);
  TinyWireM.write(x);
  TinyWireM.endTransmission();
}

void clear(void) { // Clear display buffer
  TinyWireM.beginTransmission(I2C_ADDR);
  for(uint8_t i=0; i<17; i++) TinyWireM.write(0);
  TinyWireM.endTransmission();
}

void initializeDisplay(boolean turnOn, int brightness, boolean doBlink) {
  TinyWireM.begin();         // I2C init
  clear();                   // Blank display
  if (turnOn) ledCmd(0x21);              // Turn on oscillator
  ledCmd(0xE0 | brightness); // Set brightness
  if (!doBlink) ledCmd(0x81);              // Display on, no blink
}

uint8_t translateRow(uint8_t rowData) {
  uint8_t rowCommand = 0;
  // read bits from rowData left to right
  // and translate into buffer command
  for (int col=0; col < 8; col++) {
    int colBit = bitRead(rowData, 7 - col);
    int targetBit = (col==0? 7 : col -1);
    bitWrite(rowCommand, targetBit, colBit);       
  }
  return rowCommand;
}

//
// begin writing to screan
//
void beginFrame() {
  TinyWireM.beginTransmission(I2C_ADDR);
  TinyWireM.write(0);  // start frame at row 0
}

//
// end writing to screen
//
void endFrame() {
  TinyWireM.endTransmission();
}

//
// draw one row of 8 pixels below the previously drawn row
//
void drawRow(uint8_t rowData) {
    TinyWireM.write(translateRow(rowData));
    TinyWireM.write(0);
}

//
// draw a sequence of screens with sleep between each frame
//
void drawAnimation(const uint8_t frames[ROWS_PER_FRAME][MAX_FRAMES], const uint8_t frame_timing[], int repititions ) {
  int numFrames = sizeof(frame_timing);
  
  for (int repeatIndex=0; repeatIndex < repititions; repeatIndex++) {
    for (int frameIdx=0; frameIdx < numFrames; frameIdx++) {
      beginFrame();
      for (int rowIdx=0; rowIdx < ROWS_PER_FRAME; rowIdx++) {
        drawRow(frames[rowIdx][frameIdx]);
      }
      endFrame();
      delay(frame_timing[frameIdx]);
    }
  }
}

void goToSleep() {
    ledCmd(0x20);          // LED matrix in standby mode
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
    ledCmd(0x21);          // Re-enable matrix
}

ISR(PCINT0_vect) {} // Button tap
