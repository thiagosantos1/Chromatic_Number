#include <stdio.h>
#include <stdlib.h>
/* 2 points */
 
/**
 * Read the input, one character at a time.  If it the character is a newline
 * print it, if it's not, print the binary representation of the number using
 * asterisks (*) as 1's and spaces as 0's. 
 * Example input/output:
 * > ./h3 < test/testfile | colrm 78
 * *   **  ** *  * ** **   **  * * ***  ** ****  * ***  ** *** *   **  * * ** *
 *  * **** **  *   **  * * *** **   * **** ***  *  ** **** ** **** *** *    *  
 * **  *   **  * * *** **  *** *   ** ** * ***     **  **  ***  **  *       *  
 * ...
 */
char * binaryRepresentation(unsigned int num)
{

	char * re = malloc(sizeof(num)*2); // 8 bits only
	int pos=0;
	for(int i= sizeof(num)*2 -1; i>=0; i--){

		if( num &(1<<i))
			re[pos++] = '*';
		else
			re[pos++] = ' ';
	}

	return re;

}

int main(int argc, char const *argv[])
{
	int ch;

	while((ch = getchar())!= EOF){
		if(ch=='\n')
			putchar(ch);
		else
			printf("%s",binaryRepresentation(ch));
	}

	return 0;
}
