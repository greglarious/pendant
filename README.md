Pendant
=======
This is an example Arduino IDE project for the AdaFruit pendant project 
-----------------------------------------------------------------------

[The original project page from Adafruit with full instructions](https://learn.adafruit.com/trinket-slash-gemma-space-invader-pendant/)

[This project is available on github](https://github.com/greglarious/pendant)

Overview
--------
This is the controller for an animated pendant using the following parts:

* Adafruit Gemma 8mhz
* 8x8 LED matrix with serial backpack
* Small lipo battery

Background for new programmers
------------------------------
This is a list of topics with brief explanations to help a new programmer understand how this project works:

* # Binary numbers  
   There are 8 bits in a byte visualized as follows:  
   ![a byte](https://github.com/greglarious/pendant/raw/master/markdown/byte.png "Explanation of a byte")  

   A single byte can represent a number from 0 to 255  
   A constant binary value is represented by the letter B followed by 8 0s and 1s  
   Example binary constant: B00101011  
 
* ### Binary numbers used as a bitmap:  

   When a binary number is used as a bitmap, each individual bit is used for a distinct purpose. The overall binary number is not meaningful, just the individual bits.  
   In this specific project, each bit represents an LED on the display.  
   If the bit is a one then the LED will be turned on.  if the bit is a zero then the LED will be off.  
  
* ### Variables:  
   in arduino programming, variables are named locations in memory that have specific type.  
   some examples:  
     int x     - an integer named x
     char y    y a character name y

* ### Arrays:  
   An array is a single variable that represents a sequence of values  
   some examples:
     int a[]      - an array of integers named a with unknown length  
     int b[3]     - an array of integers named b that can hold 3 numbers  
     int coord[2] - an array of 2 integers.  handy for storing X Y coordinates  

* ### Multidimensional arrays:  
   A multidimensional array is a single variable that represents an array of arrays.
   some examples:
     int coord[2][3]  - 3 sets of arrays of 2

* ### Functions:

  * A function is a named section of code with an optional set of parameters passed in and an optional return value

* ### Object Oriented Concepts:

  * A class represents a concept in a way that combines data and functions
  * This project includes a class called LEDMatrix that helps to work with the Adafruit LED backpack controller