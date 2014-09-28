Pendant
=======
This is an example program for the AdaFruit pendant project.  The project and this readme were written to teach kids in 6th grade.

For buying and building the actual pendant, see the: [Adafruit project](https://learn.adafruit.com/trinket-slash-gemma-space-invader-pendant/)  
This learning project is available here: [pendant on github](https://github.com/greglarious/pendant)

Overview
--------
This is the controller for an animated pendant using the following parts:

* Adafruit Gemma 8mhz
* 8x8 LED matrix with serial backpack
* Small lipo battery

Background for new programmers
------------------------------
This is a list of topics with brief explanations to help a new programmer understand how this project works:

* ### Binary numbers  
   There are 8 bits in a byte visualized as follows:  
   ![a byte](https://github.com/greglarious/pendant/raw/master/markdown/byte.png "Explanation of a byte")  
   A single byte can represent a number from 0 to 255
   A constant binary value is represented by the letter B followed by 8 0s and 1s
   Example binary constant: B00101011
 
* ### Binary numbers used as a bitmap:
   When a binary number is used as a bitmap, it becomes 8 separate on/off switches.
   The overall binary number is not meaningful, just the individual bits.  
   In this specific project, each bit represents an LED on the display.
   If the bit is a one then the LED will be turned on.  if the bit is a zero then the LED will be off.
  
* ### Variables:  
   in arduino programming, variables are named locations in memory that have specific type. [Variables](http://arduino.cc/en/Tutorial/Variables)
   some examples:
     int x     - an integer named x
     char y    y a character name y

* ### Arrays:
   An array is a single variable that represents a sequence of values.  [Arduino array](http://arduino.cc/en/Reference/array)
   some examples:
     int a[]      - an array of integers named a with unknown length
     int b[3]     - an array of integers named b that can hold 3 numbers
     int coord[2] - an array of 2 integers.  handy for storing X Y coordinates

* ### Multidimensional arrays:
   A multidimensional array is a single variable that represents an array of arrays.
   some examples:
     int coord[2][3]  - 3 sets of arrays of 2

* ### Arduino programming:
   This Arduino site contains helpful information about programming: [Arduino Tutorial](http://arduino.cc/en/Tutorial/HomePage)

* ### Functions:
   A function is a named section of code [Arduino function](http://arduino.cc/en/Reference/FunctionDeclaration)
   It has an optional set of parameters which are variables passed into the function
   It has an optional return value which is information returned from the function

* ### Object Oriented Concepts:
   A class represents a concept in a way that combines data and functions
   A function inside of a class is called a method
   A variable inside of a class is called a member 
   When you create an instance of a class that is called an object
   This project includes a class called LEDMatrix that helps to work with the Adafruit LED backpack controller

Using the LEDMatrix Class
-------------------------
This section describes how to use the example program to work with the display:  
* ### Defining an LEDMatrix object to use:
   ```cpp
LEDMatrix matrix = LEDMatrix();   
```
   This makes a variable named "matrix" that is an object of class LEDMatrix.

* ### Defining a new animation to show on the display
   #### Define a two dimensional array to hold the image data like this:
   ```cpp
const  uint8_t ghostData[8][8] PROGMEM = { 
 { B00011000, B00011000},
 { B01100110, B01100110},
 { B10000001, B10000001},
 { B10100101, B10010011},
 { B10000001, B10000001},
 { B10000001, B10000001},
 { B10101011, B10101011},
 { B01010101, B01010101} };
   ```
   The first dimension of the array is 8 because there are 8 lines on the display.
   The second dimension of the array is 8 because there are can be up to 8 frames of animation.
   The word PROGMEM helps us save memory on the Gemma by storing this data in Flash rather than SRAM
   Each group of numbers shows an image with the ones being lighted LEDs and the zeros being off LEDs.

   #### Next, define a new array to hold the timing data (how long to show each image)   
   ```cpp
const uint16_t ghostTiming[] PROGMEM =
 { 120, 120, 0 };   
   ```
   The numbers in this array represent how many milliseconds to show each image before moving to the next.
   The zero at the end is very important, this is what tells the LEDMatrix object how many animation frames to show before going back to the start

* ### Sending an animation to the display
   #### drawAnimation method
   ```cpp
void drawAnimation(const uint16_t frameTiming[] PROGMEM, 
                   const uint8_t frames[ROWS_PER_FRAME][MAX_FRAMES] PROGMEM, 
                   const int repititions ); 
```
   This method will draw an animation on the display and repeat it a number of times.  You can use it like this to draw the ghost animation and repeat it 3 times:
   ```cpp   
matrix.drawAnimation(ghostTiming,  ghostData,  3);
```

   #### fadeInOut method
   ```cpp
  void fadeInOut(    const uint16_t timing[] PROGMEM, 
                     const uint8_t data[ROWS_PER_FRAME][MAX_FRAMES] PROGMEM, 
                     const int repititions, 
                     const int fadeStep,
                     const long sleepWhenDone);
```
   This method will call drawAnimation multiple times to present the animation fading from dim to bright and back to dim.  Then, it will sleep for a period of time.  The first 3 parameters are the same as drawAnimation.  
   fadeStep - is how quickly to adjust the brightness.  Suggested values are between 1 and 3
   sleepWhenDown - is how many milliseconds to sleeep