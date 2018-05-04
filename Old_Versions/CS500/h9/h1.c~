#include <stdio.h>
#include <stdlib.h>

/* 2 points */ 

/**
 * To make your life easier, consider making a "binary" function that returns
 * a pointer to a static buffer that contains the binary representation of
 * the number passed to it suitable for printing with printf.
 */

/**
 * Make a program that prints four columns.  The first column is the numbers
 * 0 through 63 followed by the number in binary (#'s for 1's and -'s for 0's)
 * with a colon between the numbers.  The second through 4th columns are the
 * values between 64-127, 128-191 and 192-255 respectively (i.e. each column
 * is 64 values apart.)  The numbers are padded to 3 characters.
 * Example output:
 * > ./h1
 *   0 : --------    64 : -#------   128 : #-------   192 : ##------
 *   1 : -------#    65 : -#-----#   129 : #------#   193 : ##-----#
 *   2 : ------#-    66 : -#----#-   130 : #-----#-   194 : ##----#-
 *   3 : ------##    67 : -#----##   131 : #-----##   195 : ##----##
 * ...
 *  62 : --#####-   126 : -######-   190 : #-#####-   254 : #######-
 *  63 : --######   127 : -#######   191 : #-######   255 : ########
 */

char * binaryRepresentation(unsigned int num)
{
	char * re = malloc(sizeof(num)*2); // 8 bits only
	int pos=0;
	for(int i= sizeof(num)*2 -1; i>=0; i--){

		if( num &(1<<i))
			re[pos++] = '#';
		else
			re[pos++] = '-';
	}

	return re;

}

int main(int argc, char const *argv[])
{	
	int  rows= 64, columns = 4;
	for (int r = 0; r < rows; r++){
		printf("%3d : %s   ",r,binaryRepresentation(r) );
		for (int c = 1; c < columns; c++){
			printf("%3d : %s",c*rows+r,binaryRepresentation(c*rows+r) );
			if(c<columns-1)
				printf("   ");
		}
		printf("\n");	
	}
	return 0;
}

