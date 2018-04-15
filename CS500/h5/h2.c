#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* 1 point */
/**
 * Fill in the bubblesort function:
 * https://en.wikipedia.org/wiki/Bubble_sort
 * Do not modify any of the below.
 * Provide credit any source you use in your code.
 */

/* Source used 
 * https://stackoverflow.com/questions/7065277/difference-between-char-and-char-in-c
 * http://www.geeksforgeeks.org/bubble-sort/ 
*/

#define MAX 60000

void bubblesort(char *a[], int n)
{
  for (int j = 0; j < n -1; j++) {
    for (int i = 0; i < n -1; i++) {
      if ( strcmp(a[i], a[i +1]) > 0) {
        char* temp = a[i];
        a[i] = a[i +1];
        a[i +1] = temp;
      }
    }
  }

}

int readwordsFile(char **fileStorage, const char * fileName) // return num of words
{ 
  
  int wordsCount =0;
  FILE * fp = fopen(fileName, "r");
  if(fp == NULL){
    printf("File %s could not be open\n", fileName);
    exit(1);
  }
  
  fileStorage[wordsCount] = (char *)malloc(MAX); // maloc size for the first position
  while (fscanf(fp, "%s", fileStorage[wordsCount++]) != EOF) { // read and save word for position wordsCount
    
    fileStorage[wordsCount] = (char *)malloc(MAX); // alocate memoray to save next word
  }  
  
  return wordsCount;
}

void printfWords(char ** fileStorage, int numWordsFile)
{
  for (int i = 1; i < numWordsFile; i++) {
    printf("%s\n", fileStorage[i]);
  }
  
}

/**
 * Create a main function that opens a file composed of words, one per line
 * and sorts them using the bubble-sort algorithm.
 * Usage: "Usage: %s <file>\n"
 * Example input/output:
 * ./h2 testfile
 * Bob
 * Bubbles
 * Butters
 * Dave
 * ...
 */

int main(int argc, char * argv[])
{
  
  char *fileStorage[MAX];
  int numWordsFile=0;
  if(argc<2){
    printf("Usage: %s <file>\n", argv[0]);
    exit(1);
  }
  
  numWordsFile = readwordsFile(fileStorage, argv[1]);
  
  if(numWordsFile <1){
    printf("No words found it in the file %s\n", argv[1]);
    exit(1);
  }
  
  bubblesort(fileStorage, numWordsFile);
  
  printfWords(fileStorage, numWordsFile);
  
  return 0;
  
  
}

