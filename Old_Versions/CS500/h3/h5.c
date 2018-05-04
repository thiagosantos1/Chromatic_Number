
/**
 * Makes a rectangle made of stars that is height x width in size:
 * Example input/output:
 * ./h5 5 10
 * **********
 * **********
 * **********
 * **********
 * **********
 */

/* Author: Thiago
 * Date: 09/08/17
 */

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

void rectangle(int height , int width);

int main(int argc, char *argv[])
{
  if (argc < 3) {
    printf("usage: h4 <number>\n");
    return 1;
  }
  rectangle(atoi(argv[1]), atoi(argv[2]) );

  return 0;
}


void rectangle(int height , int width)
{
 
  for(int i=0; i<height; i++){
    
    for(int stars =0; stars<width; stars++){
	  
      printf("*");
    }
    
    printf("\n");
    
  }
  
}