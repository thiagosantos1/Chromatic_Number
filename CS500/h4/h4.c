#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/**
 * This program takes a file-name from the command line and prints it out 5
 * lines at a time, numbering the lines of the output as it goes (line numbers
 * should be three characters wide, right-aligned). Every five lines print it
 * should stop and print a prompt "MORE? " and read a line from the standard
 * input.  If the first letter of the users input is a 'q' or a 'Q', then quit
 * the program, otherwise print the next five lines.
 *
 * Example input/output:
 * ./h4 test/h3-testa 
 *   1 Test A
 *   2 Test B
 *   3 Test C
 *   4 Test D
 *   5 Test E
 * MORE? q
 */

int printfile(const char * fileName)
{

  FILE * fp, *fpCount;
  int ch;
  int count;
  int line =0;
  int c;
  int countLinesFile =0;

  fp= fopen(fileName, "r");
  fpCount =  fopen(fileName, "r");

  if(fp == NULL)
    return -1;
  
  while( (count=fgetc(fpCount)) != EOF){
    if(count == '\n')
      countLinesFile++;
    
  }
  

  printf("%3d ", line++ +1);
  while( (((ch=fgetc(fp)) != EOF)) && ( (toupper(c)) !='Q') ){
    putchar(ch);
    if(ch == '\n'){
      if(line %5 ==0){
	printf("MORE? " );
	  c=getchar();
	  //getchar();
      }
      if( (toupper(c)) == 'Q')
	break;
		  
      if(line <= countLinesFile-1) // make sure to don't print an extra line
	printf("%3d ", line++ +1);
    }
		
  }
  fclose(fp);
  fclose(fpCount);

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