#include <stdio.h>
#include <stdlib.h>

#define MAXLARGEST 10

/* 2 points */
/**
 * Create a program that takes a file-name from the command line and prints the
 * 10 largest values in the file in descending order.  If there are fewer than
 * 10 values, then print only those values.
 * Example input/output:
 * > ./h5 test/numbers
 * 968
 * 955
 * 932
 * 914
 * 912
 * 906
 * 855
 * 851
 * 834
 * 777
 */


long int largest10[MAXLARGEST];
int numRead=0;

void printArray()
{

  for (int i = numRead-1; i >=0 ; i--){
    printf("%ld\n", largest10[i] );
  }
}

void bubleSort()
{
  for (int j = 0; j < numRead -1; j++) {
    for (int i = 0; i < numRead -1; i++) {
      if(largest10[i] > largest10[i+1]){
	long int temp = largest10[i];
	largest10[i] = largest10[i +1];
	largest10[i +1] = temp;
      }
     }
  }
}

void swap(int end, long int numToInsert) // begining you already know, it's 0
{
  long int temp = largest10[end];
  int i;
  largest10[end] = numToInsert;
  for (i = 0; i < end-1; i++){
    largest10[i] = largest10[i+1];		
  }
  largest10[i] = temp;
}

void insert(long int num )
{
  int done =0;

  for (int i = 0; i < numRead; i++){
    if(num< largest10[i]){
      swap(i-1, num);
      done =1;
      break;
    }

  }

  if(! done) swap(numRead-1, num);
}

void readFile(const char * fileName)
{
  FILE * fp = fopen(fileName, "r");
  long int num;

  // read just the first 10 and then sort
  while( (fscanf(fp,"%ld", &num) ==1) && (numRead <10) ) largest10[numRead++] = num;

  bubleSort();
  
  // read the rest, just checking if it should be in the array
  // if so,  insert
  if(numRead >9){
    if(num > largest10[0])
      insert(num);
  }
  while( fscanf(fp,"%ld", &num) ==1){ 
    if(num > largest10[0])
      insert(num);
    
  }
}
 
 int main(int argc, char const *argv[])
 {
 	
  if(argc<2){
    printf("Usege <File> %s\n", argv[0]);
    exit(1);
  }
  readFile(argv[1]);
  printArray();
  return 0;
 }

