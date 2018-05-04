#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
/**
 * Create a program that opens and reads a list of long integers from a file
 * the name is provided on the command line as the first command line argument.
 * Read in the numbers into an array that needs to be at most 1000 long integers
 * in size.  Print the numbers read out in reverse.
 * Example input/output:
 * ./h5 test/h3-testb
 * 75
 * 16
 * 25
 * 90
 * 50
 * 10
 */

int printfile(const char * fileName)
{
  long int list[1000];
  long int num;
  int arraySize =0; 

  FILE * fp;

  fp= fopen(fileName, "r");

  if(fp == NULL)
    return -1;

  while( (fscanf(fp,"%ld", &num)) != EOF){		
    list[arraySize] = num;
    arraySize++;
  }

  for (int i = arraySize-1; i >= 0; i--){
    printf("%ld\n", list[i] );
  }
  
  fclose(fp);

	return 0;

}

int main(int argc, char const *argv[])
{
  if(argc <2){
    printf("Usade %s <File Name>\n", argv[0]);
    exit(1);
  }
  if(printfile(argv[1]) < 0)
    printf("Unable to open %s for reading.\n", argv[1]);
	
  return 0;
}
