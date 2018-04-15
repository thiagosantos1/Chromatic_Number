
/**
 * Print all the hours and minutes in a day, in AM/PM format.  Hours should
 * be two characters wide, minutes should be zero padded.
 * Example output:
 * ./h1
 * 12:00 am
 * 12:01 am
 * 12:02 am
 * 12:03 am
 * ...
 */

/* Author: Thiago
 * Date: 09/09/17
 */


#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  
   for(int hour=0; hour< 12; hour++){
      
      for(int minutes = 0; minutes<60; minutes++){
	
		if(hour ==0)
		  printf("%2d:%02d %s\n", hour + 12, minutes, "AM");
		else
		  printf("%2d:%02d %s\n", hour, minutes, "AM");
      }
   }
    
   for(int hour=0; hour < 12; hour++){
      
      for(int minutes = 0; minutes<60; minutes++){
	
		if(hour ==0)
		  printf("%2d:%02d %s\n", hour + 12, minutes, "PM");
		else
		  printf("%2d:%02d %s\n", hour, minutes, "PM");
		  
	  }
      
   }
  
  return 0;
  
  
}
