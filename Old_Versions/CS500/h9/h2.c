#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* 2 points */
 
/**
 * Create a program that reads the stdin one character at a time (do not use
 * fgets or scanf, etc, only use getchar()) and prints all the numbers found on
 * a line of input separated by spaces (periods should be included also if they
 * are preceded by a number) and terminated by a newline. E.g. if it
 * reads: "for(i=0; i < 10; i+=2)\n" then it should print:
 * 0 10 2\n
 * If there are no numbers in the line of input, it should print nothing,
 * including the newline.
 * Example input/output:
 * > ./h2 < test/testfile
 * 888 403 485 46
 * 5.9 0 5.9 0
 * 5.9 1.1 5.9 1
 * 5.9 33 5.8 1
 * 5.9 0 5.9 0
 * 100 0 100 0
 */

int main(int argc, char const *argv[])
{
	int ch, digit_on=0, prev=0, sequence_on=0;

	while((ch = getchar())!= EOF){
		
		if(ch =='.'){
			if(isdigit(prev))
				putchar('.');
		}
		if( (isdigit(ch)) || (ch =='\n' && digit_on) ){
			putchar(ch);
			digit_on = ch =='\n' ? 0:1; // reset to 0 if is going to a new line, or set to 1 if there is a digit(must print \n)
			sequence_on = digit_on ? 1:0;
		}

		if(ch==' ' && sequence_on){
			putchar(ch);
			sequence_on = 0;
		}

		prev = ch;
	}
	return 0;
}
