#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
/**
 * Create a program that works like something like the "colrm" program. It take
 * up to two integer parameters. It should read characters from standard input
 * and output to standard output.  It should remove selected columns from the
 * input if the columns (starting at 1) are specified on the command line. If
 * no parameters are given, print the input as-is.  If only the first column
 * is specified, remove all columns starting at that column.  If both a first
 * and last column are specified, remove the specified columns.  If the last
 * column is less than the first, swap the first and last values.
 * Example input/output:
 * ./h6 2 4 < test/h3-testa
 * T A
 * T B
 * T C
 * T D
 * T E
 * T F
 */




int main(int argc, char const *argv[])
{
  int num1=0, num2=0;
  int ch;
  int column =1;
  if(argc >2){
    num1 = atoi(argv[1]);
    num2 = atoi(argv[2]);
    if(num1 > num2){
      int temp = num1;
      num1 = num2;
      num2 = temp;
    }
    
  }else if (argc >1){
	  num1 = atoi(argv[1]);

	}

  while( (ch=getchar()) != EOF){

    if( num1 <=0 && num2 <=0){
      printf("%c",ch );

    }else if(num1 > 1 && num2 >1){

	  if( (column < num1) || (column > num2) || (ch=='\n') )
	    printf("%c",ch );
				
    }else{
	if( (column < num1) || (ch == '\n') )
	  printf("%c",ch );
    }
    
    column++;

    if(ch == '\n'){
      column =1;
    }

  }
	
  return 0;
}

