#include <stdio.h>
#include <math.h>

/**
 * Write a C program that prints 'h' many lines, with the i'th line being
 * length[i] many '-' characters. (3 points)
 */

int main(int argc, char *argv[])
{
  const int h=30;
  int lengths[h];
  for(int i=0; i < h; i++) lengths[i] = sin(3.14*i/h)*h*2;

  for(int i=0; i < h; i++){
    for(int j=0; j<lengths[i]; j++)
      printf("-");
    printf("\n");
  }
  
  
  return 0;
}

