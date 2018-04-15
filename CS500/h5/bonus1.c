#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX  200
/* 3 or 4 points */
/**
 * Modify h1.c to highlight the matched string portion using ANSI escape codes.
 * \033[#;#m changes the color. \033[0m resets the colors back to normal.
 * Codes are:
 * Attribute codes:
 * 00=none 01=bold 04=underscore 05=blink 07=reverse 08=concealed
 * Text color codes:
 * 30=black 31=red 32=green 33=yellow 34=blue 35=magenta 36=cyan 37=white
 * Background color codes:
 * 40=black 41=red 42=green 43=yellow 44=blue 45=magenta 46=cyan 47=white
 * 
 * ex: \033[04;32m green underlined text on regular background \033[0m
 * 
 * 4 points if it highlights all occurrences of the pattern on the same line. 
 */

char stringLine[MAX];

//void resetString(){

 // for(int i=0; i< sizeof(stringLine); i++)
   // stringLine[i] = 0;
//}

int main(int argc, char * argv[]){
  
  char *patternString;
  int flag = 0, index=0, startPrinting=0, lasPosOcurrency=0, sizeInput=0; //false
  char* posFound;
  char * temp;
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
  
  sizeInput = strlen(patternString);
  while(fgets(stringLine, MAX, fp)){  

    stringLine[strcspn(stringLine, "\n")] = 0; 
    posFound =  strstr(stringLine, patternString);

    while( posFound) {
      flag =1;
      lasPosOcurrency = (posFound - stringLine);
      // printf("Last: %d\n", strlen(patternString));
       //printf("String: %s \n", stringLine);
       //printf(" Hey %s was found at position %ld\n\n", patternString, posFound - stringLine);
      //print from where you left untill next //ocurrency ofpatternString 

      for(index=startPrinting; index<lasPosOcurrency +sizeInput ; index++){ 
	if(index < lasPosOcurrency) // not a word from pattern
	  printf("%c", stringLine[index]);
	else
	  printf("\033[22;31m%c\033[0m", stringLine[index]);// print occurency word in different color
			
      }
      startPrinting = lasPosOcurrency +sizeInput;
      temp = stringLine+ lasPosOcurrency + sizeInput; //sizeof(posFound);
      //printf("Temp: %s\n", temp);
      posFound = strstr( temp, patternString);
    
    }
    
   // printf("Original: %s\n", stringLine+4);
    // make sure with the flag if there still something in the line to print after the last occurency of patternString
    if(flag ==1){  
      for(index=lasPosOcurrency +sizeInput; index<strlen(stringLine) ; index++)
	printf("%c", stringLine[index]);

      startPrinting =0;
      flag =0;
      printf("\n");
    }

  }
  
  return 0;
 
}

