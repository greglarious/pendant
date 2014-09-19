#define ROWS_PER_FRAME 8
#define MAX_FRAMES 8
#define COLUMS_PER_ROW 8

class LEDMatrix {
public:
  static const int DEFAULT_I2C_ADDR = 0x70;
  static const int BLINK_NONE = 0;
  static const int BLINK_2HZ = 2;
  static const int BLINK_1HZ = 4;
  static const int BLINK_HALFHZ = 5;
  
  LEDMatrix();
  LEDMatrix(int I2CAddress);
  //
  // lower power consumption to extend battery life
  //
  void lowPowerMode();
  
  //
  // Clear display buffer
  //
  void clear();
  
  //
  // turn on display, blank it and set brigthness
  //
  void initializeDisplay(int brightness, int blinkType);
  
  //
  // draw a sequence of screens with sleep between each frame
  //
  // frame_timing - array of indicating how long to sleep between frames.
  //                an entry of zero indicates no more frames and decides how 
  //                many frames will be processed by this function
  //
  // frames       - two dimensional array of bitmapped data to draw
  //                the first index is the row 0 .. 8
  //                the second index is the frame number in the animation
  //
  // repititions  - how many times to repeat the entire animation from first frame to last
  //
  void drawAnimation(const long frameTiming[], 
                     const uint8_t frames[ROWS_PER_FRAME][MAX_FRAMES], 
                     int repititions );
  //
  // put display and gemma to sleep for extremely low power consumption
  // wakeup happens when the button is pushed and the interrupt is triggered
  // this function will not return until the button is pushed
  void goToSleep();

  void setBrightness(unsigned int level);
  void oscillatorOn();
  void oscillatorOff();
  
  void displayOn(int blinkType);
  void displayOff();

private:
  int address;
  
  //
  // send single byte command to LED matrix
  //
  void ledCmd(uint8_t x);

  //
  // translate a byte of bitmapped pixels into an LED matrix command as follows:
  // input bitmap bits = 7 6 5 4 3 2 1 0
  // target LED bits =   7 0 1 2 3 4 5 6
  //
  // rowData - bitmapped representation of pixels to draw
  //           bit 7 is the leftmost pixel and bit 0 is the rightmost pixel
  //
  // returns - byte formatted for LED matrix
  static uint8_t translateRow(uint8_t rowData);
  
  //
  // begin writing pixel data to screan
  //
  void beginFrame();
  
  //
  // end writing pixel data to screen
  //
  void endFrame();
  
  //
  // draw one row of 8 pixels below the previously drawn row
  // rowData - bitmapped representation of row
  //           bit 7 is the leftmost pixel and bit 0 is the right
  //
  void drawRow(uint8_t rowData);
};
