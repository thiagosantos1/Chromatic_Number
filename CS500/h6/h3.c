#include <stdio.h>
#include <stdlib.h>
/* 1 point */
/**
 * Open a file (path given on the command line), containing long integers, one
 * to a line, and process them.  Print the sum, average, minimum and maximum of
 * the numbers found in the file.
 * Example input/output:
 * > ./h3 test/numbers
 * sum = 23655, avg = 473, min = 15, max = 968
 */

void readFile(const char * fileName, long int * sum, long int * avg, long int * min, long int * max){


  FILE * fp = fopen(fileName, "r");
  long int num, totalNums=1;

  fscanf(fp,"%ld", &num);
  *min = *max = *sum =num;
  while(fscanf(fp,"%ld", &num) ==1){
    if(num<*min){
      *min = num;
    }else if(num > *max){
      *max = num;
    }
    *sum +=num;
    totalNums++;

  }

  *avg = *sum/totalNums;
	
}
 

 int main(int argc, char const *argv[])
 {
  long int sum=0, avg=0, min =0, max=0;
  if(argc<2){
    printf("Usege <File> %s\n", argv[0]);
    exit(1);
  }

  readFile(argv[1], &sum, &avg, &min, &max);

  printf("sum = %ld, avg = %ld, min = %ld, max = %ld\n", sum, avg, min, max);
  
  return 0;
 }
