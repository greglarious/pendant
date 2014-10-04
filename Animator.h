#include "LEDMatrix.h"
#include "Translation.h"

void drawAnimation(LEDMatrix matrix,
                              const uint8_t timing[] PROGMEM, 
                              const uint8_t data[ROWS_PER_FRAME][MAX_FRAMES] PROGMEM, 
                              Translation trans,
                              const byte repititions) {
  Position* pos = trans.initialize();
  
  for (int repeatIndex=0; repeatIndex < repititions; repeatIndex++) {
    //
    // loop until we find end of frame timing data
    int frameIndex = 0;
    while (pgm_read_byte(&timing[frameIndex]) != END_FRAMES) {
      //
      // draw the current frame
      matrix.drawFrame(data, frameIndex, pos);
      
      // move the position according to the rules in the translation
      trans.apply(pos);
      
      //
      // pause between frames
      delay(pgm_read_byte(&timing[frameIndex]));
      frameIndex++;
    }
  }
}

void fadeInOut(LEDMatrix matrix,
               const uint8_t timing[] PROGMEM, 
                          const uint8_t data[ROWS_PER_FRAME][MAX_FRAMES] PROGMEM,
                          const int numAnimations, 
                          const int fadeStep,
                          const long sleepWhenDone) {
    // fade dim to bright
    for (int b=0; b <= 15; b+= fadeStep) {
      matrix.setBrightness(b);
      drawAnimation(matrix, timing, data, Translation(0, 0, false, 0), numAnimations);
    }
    // fade bright to dim
    for (int b=15; b >= 0 ; b-= fadeStep) {
      matrix.setBrightness(b);
      drawAnimation(matrix, timing, data, Translation(0, 0, false, 0), numAnimations);
    }
    matrix.clear();
    delay(sleepWhenDone);
}

