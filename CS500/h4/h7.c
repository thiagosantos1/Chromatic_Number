#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>


/**
 * Like h1, create a program that opens and reads up to 1000 long integers from
 * a file, name provided on the command line, into an array.  Format the numbers
 * into evenly sized columns that fit inside of 50 columns.
 * Use the sprintf(3) function to determine how many characters each number is
 * and remember the width of the longest number and make each number column
 * that width + 2 spaces.
 * Remember to print a final newline for the last line if it requires it.
 * If the numbers read are:
 * AAA
 * BBBBB
 * CC
 * Then the program should output:
 *   AAA  BBBBB     CC  
 * Example input/output:
 * ./h7 test/h7-testdata
 *         1          10         100        1000  
 *     10000      100000     1000000    10000000  
 * 100000000          -1         -10        -100  
 *     -1000      -10000     -100000    -1000000  
 * -10000000  -100000000
 */

// did not really undestand how the sprintf works. Therefore, I dicieded to build my onw function
// to count how many characters each number is
int myOwnSprintf(long int value){
  int lengh =1;
  if(value <0){
    value *= -1;
    lengh++;
  }
  while(value >= 10){
    lengh++;
    value /=10;
  }
  return lengh; 
}
int printfile(const char * fileName)
{
  long int list[1000];
  long int num;
  int arraySize =0, length=0, temp=0, mod; 

  FILE * fp;

  fp= fopen(fileName, "r");

  if(fp == NULL)
    return -1;

  while( (fscanf(fp,"%ld", &num)) != EOF){		
    temp = myOwnSprintf(num);
    if( temp> length)
      length = temp;
      list[arraySize] = num;
      arraySize++;
  }
  mod = 50 / (length +2) ; // plus 2 because of the space

  for (int i = 0; i < arraySize; i++){
    if( (i%mod==0) && i > mod -1) 
      printf("\n");
    printf("%*ld  ", length, list[i] );
  }
  printf("\n");
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
