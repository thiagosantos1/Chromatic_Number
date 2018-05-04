#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 1000000
#define MAXWORD 100
/* 1 point */
/**
 * Modify h3.c to use a binary search:
 *   https://en.wikipedia.org/wiki/Binary_search_algorithm
 * to determine if a word is found in the dictionary or not.
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

void bubblesort(char *a[], int n)
{
  for (int j = 0; j < n -1; j++) {
    for (int i = 0; i < n -1; i++) {
      if ( strcasecmp(a[i], a[i +1]) > 0) {
        char* temp = a[i];
        a[i] = a[i +1];
        a[i +1] = temp;
      }
    }
  }

}

int BinarySearchWord(char * word)
{  
  int minPosition =0, maxPostion = totalWords -1, posToSearch;
  
  posToSearch = (minPosition + maxPostion) /2;
  while(minPosition <= maxPostion){
 
    if( (strcasecmp(word, fileStorage[posToSearch])) ==0) // same words
      return 1;
    else if( (strcasecmp(word, fileStorage[posToSearch])) >0)
      minPosition = posToSearch +1;
    else
      maxPostion = posToSearch -1;  
      
    posToSearch = (minPosition + maxPostion) /2;
    
  }
  
  
  return 0; // not found
}


int main(int argc, char * argv[])
{
  char word[MAXWORD];
  if(argc<2){
    printf("Usage: %s <File>\n", argv[0]);
    exit(1);
  }
  
  if( (load_dictionary(argv[1])) <=0){
    printf("File %s could not be open\n", argv[1]);
    exit(1);
  }
  
  bubblesort(fileStorage, totalWords);
  while( (fgets(word, MAXWORD, stdin)) ){
    word[strcspn(word, "\n")] = 0; // remove \n
    if(BinarySearchWord(word))
      printf("'%s' OK\n", word); 
    else
      printf("'%s' NOT FOUND\n", word); 
  
  }
  return 0;
  
  
}

