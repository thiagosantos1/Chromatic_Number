
/**
 * Modify h5 and make a square (actually one column wider than it is high) that
 * is composed of two triangles, one made of stars (*) and the other made of
 * dashes (-):
 *  Usage: h6 <height>
 * Example input/output:
 * ./h6 5
 * *-----
 * **----
 * ***---
 * ****--
 * *****-
 */

/* Author: Thiago
 * Date: 09/08/17
 */

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

void square(int height);

int main(int argc, char *argv[])
{
  if (argc < 2) {
    printf("usage: h4 <number>\n");
    return 1;
  }
  square(atoi(argv[1]) );

  return 0;
}


void square(int height)
{
 
  int piran = height;
  
  for(int i=1; i<=height; i++){
    
    for(int stars =0; stars<i; stars++)
      printf("*");
    
    
    for(int lines=0; lines < piran; lines++)
      printf("-");
    
    printf("\n");
    piran--;
    
  }
  
}