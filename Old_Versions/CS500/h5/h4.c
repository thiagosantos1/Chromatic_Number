#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 1000000
#define MAXWORD 100

int totalWords; // global variable to save total of words
char *fileStorage[MAX];

/* 2 points */

/**
 * Re-use the load_dictionary() function from h3.c
 */

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

int isWordInDictionary(const char * word)
{  
  for(int i=0; i<totalWords; i++){
   
    if( (strcasecmp(word, fileStorage[i])) ==0){ // same words
      return 1;
    }
  }
  return 0;
}




/**
 * Create a main function that takes a file-name on the command line and 
 * reads words out of the file (use fscanf() to do this) and checks each word
 * to see if it's in the loaded dictionary.  Again use strcasecmp() to do a
 * case-insensitive search.
 * Example input/output:
 * ./h4 testfile 
 * 'Bob'   OK
 * 'Tiffany'       NOT FOUND
 * 'Steve' NOT FOUND
 * 'Jim'   NOT FOUND
 * ...
 */

int main(int argc, char * argv[])
{
  char word[MAXWORD];
  FILE * fp;
  if(argc<2){
    printf("Usage: %s <File>\n", argv[0]);
    exit(1);
  }
  
  if( (load_dictionary("/usr/share/dict/words")) <=0){
    printf("File could not be open\n");
    exit(1);
  }
  
  fp = fopen(argv[1], "r");
  if(fp == NULL){
    return 0;
  }
  

  while (fscanf(fp, "%s", word) != EOF) { // read word by word to check in the dictionary
   word[strcspn(word, "\n")] = 0; 

   if(isWordInDictionary(word))
      printf("'%s'\tOK\n", word); 
    else
      printf("'%s'\tNOT FOUND\n", word); 

  } 
  
 
  return 0;
  
}


