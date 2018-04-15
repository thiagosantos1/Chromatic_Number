#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 1000000

/* 1 point */

/**
 * Make a function that checks if a word provided on the command line is 
 * present in the dictionary which you load.  Use strcasecmp() to compare
 * the word against the dictionary words.
 * Example input/output:
 * ./h3 test
 * test OK
 * ./h3 xxyx
 * xxyx NOT FOUND
 */

/**
 * Create a load_dictionary function to open and read the words in the file:
 *   /usr/share/dict/words
 * Store the words and a count of the words in global variables.
 * It should return an error code if the dictionary could not be loaded for
 * any reason.  This code should be checked in main and the program aborted
 * if there is an error.
 */

int totalWords; // global variable to save total of words
char *fileStorage[MAX];

int load_dictionary( const char * fileName) // return num of words //  gonna save on fileStorage
{ 
  
  int wordsCount =0;
  FILE * fp = fopen(fileName, "r");
  if(fp == NULL){
    return 0;
  }
  
  fileStorage[wordsCount] = (char *)malloc(MAX); // maloc size for the first position
  while (fscanf(fp, "%s", fileStorage[wordsCount++]) != EOF) { // read and save word for position wordsCount
    
    fileStorage[wordsCount] = (char *)malloc(MAX); // alocate memoray to save next word
  }  
  
  totalWords = wordsCount;
  
  return wordsCount;
}


int isWordInDictionary(char * word)
{  
  for(int i=0; i<totalWords; i++){
   
    if( (strcasecmp(word, fileStorage[i])) ==0){ // same words
      return 1;
    }
  }
  return 0;
}

int main(int argc, char * argv[])
{
  if(argc<2){
    printf("Usage: %s <Word>\n", argv[0]);
    exit(1);
  }
  
  if( (load_dictionary("/usr/share/dict/words")) <=0){
    printf("File could not be open\n");
    exit(1);
  }
  
  if(isWordInDictionary(argv[1]))
    printf("%s OK\n", argv[1]); 
  else
    printf("%s NOT FOUND\n", argv[1]); 
  
  return 0;
  
  
}

