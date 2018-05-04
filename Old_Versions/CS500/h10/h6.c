/* 2 points */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE	23
#define SIZEMT	5
/**
 * This program should create a playfair cipher cube:
 *   https://en.wikipedia.org/wiki/Playfair_cipher
 * a 5x5 matrix of characters that is initialized with the unique characters
 * of a "password" string (the playfair key.)
 */
/**
 * Steps:
 * 1) Point to the first command line argument with a variable called p.
 * 2) Create an empty string buffer called 'used' to keep track of used letters
 *    and an empty string buffer called key which will be unique characters of
 *    the input password pointed to by p.
 * 3) For each character in p add it to key if it is not already in key. If
 *    the character in p is a 'j', convert it to a i.  Note you cannot change
 *    the values of p since the string p points to is a read-only string.  Also
 *    add the same characters to 'used'.
 *    At the end of this step, if p == "playfairexample", then key should ==
 *   "playfirexm"
 * 4) Using the variable mat that will store a 5x5 2 dimensional array (an array
 *    of 5 sub-arrays with 5 elements each.) fill out the playfair matrix:
 * 5) For each row/column position (row/col) first add to mat[row][col] the
 *    values in key.  After placing all the characters of key into the matrix
 *    one at a time until all the characters of key are exhausted.  After which
 *    include all the characters of alpha that are not in used one at a time
 *    until all the row/columns have been filled in.
 * 6) Make sure that the included code at the bottom of main is the last step to
 *    print out your matrix.
 * 
 * Example input/output:
 * ./h6 playfairexample
 * p l a y f 
 * i r e x m 
 * b c d g h 
 * k n o q s 
 * t u v w z 
 */
// check if key has been already used
int keyUsed(char * used, char key)
{
  while(*used){
    if( (*used) == key)
      return 1;
    used++;
  }
  return 0; // not used
}

void fillMatrixKey(char mat[SIZEMT][SIZEMT], char * key)
{
  for(int i=0; i<SIZEMT; i++){
    
    for(int j=0; j<SIZEMT && *key; j++){
      mat[i][j] = *key;
      key++;
	
    }
  }
}

void fillMatrixAlpha(char mat[SIZEMT][SIZEMT], char * alpha, char * used, int sizeKey)
{
  // just to complete a line, in case need it
  for(int i=sizeKey/SIZEMT; i<(sizeKey/SIZEMT)+1; i++){
    
    for(int j=sizeKey % SIZEMT; j<SIZEMT && *alpha; j++){
      while(keyUsed(used, *alpha)) alpha++; // find the next alpha not used yet
      mat[i][j] = *alpha;
      alpha++;
	
    }
  }
  
  for(int i=(sizeKey/SIZEMT)+1; i<SIZEMT; i++){
    
    for(int j=0; j<SIZEMT && *alpha; j++){
      while(keyUsed(used, *alpha)) alpha++; // find the next alpha not used yet
      mat[i][j] = *alpha;
      alpha++;
    }
  }
}
int main(int argc, char *argv[])
{
  /* The playfair alphabet. Note that j is not used (j == i in playfair) */
  char *alpha = "abcdefghiklmnopqrstuvwxyz";
  char mat[5][5];

  if (argc < 2) {
    printf("Usage: %s <key>\n", argv[0]);
    return 0;
  }
  /* Add your code starting here: */
  
  char * p = argv[1];
  
  char used[SIZE]={' '};
  char key[SIZE];
  int index=0, indexUsed=0;
  char k;
  while(*p){
      k = *p=='j'? 'i':*p;
      if(! keyUsed(used, k)){
	key[index++] = k;
	used[indexUsed++] = k;
      }
      
      p++;
      
  }
  
  fillMatrixKey(mat,key);
  int sizeKey = strlen(key);
  fillMatrixAlpha(mat,alpha,used,sizeKey);

  /**
   * Do not remove the following.  It will output your playfair matrix:
   */
  for(int r=0; r < 5; r++) {
    for(int c=0; c < 5; c++)
      printf("%c ", mat[r][c]);
    printf("\n");
  }
}
