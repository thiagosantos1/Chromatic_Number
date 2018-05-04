#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* 1 point */

/**
 * Create a program that takes a pattern string as the first command line
 * argument and an optional file-name as the second command line argument.
 * If not file-name is given, read lines from stdin.
 * Using the strstr() function, print any lines from the input that contain the
 * pattern string.
 * Example input/output:
 * ./h1 B testfile
 * Bob
 * Butters
 * Bubbles
 */

#define MAX  200
int main(int argc, char * argv[]){
  
  char *patternString;
  char stringLine[MAX];
  FILE * fp;
  
  if(argc <2){
    printf("You must enter a pattern string to the program %s\n", argv[0]);
    exit(1);
  }else{
    patternString = argv[1];
    fp = stdin; // if no file is gaven, pointer is gonna point to stdin(user input)
    if(argc > 2){
      fp = fopen(argv[2], "r");
      if(fp == NULL){
	printf("Usage: %s <%s>\n", argv[0],argv[2]);
	exit(1);
      } 
    }
  }
 
  while(fgets(stringLine, MAX, fp)){   
   if(strstr(stringLine, patternString)){
     printf("%s", stringLine);
   }
  }
  return 0;
 
}