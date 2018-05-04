/* 4 points */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#define ROWS	30
#define COLS	120

/** (1pt)
 * Define a function called clear() that takes the screen array and zeros all
 * the values in it.  Note for all these functions your screen parameter should
 * be: uint8_t screen[ROWS][COLS/8]
 * Each column value represents 8 column pixels (each bit is a "pixel".)
 */



/**(1.5pts)
 * Create a function called plot that takes the screen array, and two integers
 * x and y which are the column and row pixel positions to turn on a pixel.
 * The function should check to make sure that x and y are valid pixel
 * locations, i.e. not negative or too big.
 */



/** (1.5pt)
 * Make a function called print() that is given the screen array and prints
 * out it's pixels as stars (*) if set or spaces if not.
 */



/**
 * Do not modify the code below:
 * Draws 9 circles at a downward angle on the "screen"
 * Your terminal window should be set to at least 121 columns wide and 31 rows
 * high for best results.
 */
int main(void)
{
  uint8_t screen[ROWS][COLS/8];

  clear(screen);
  int r=(ROWS/4);
  for(int xoff = r, yoff = r; xoff < COLS-ROWS; xoff += 10, yoff+=2) {
    for(int a = 1; a < 360; a += 5) {
      double rad = (a*M_PI)/180.0;
      plot(screen, (cos(rad)*r)+xoff, (sin(rad)*r)+yoff);
    }
  }
  print(screen);

  return 0;
}
