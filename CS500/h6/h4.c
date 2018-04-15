#include <stdlib.h>
#include <stdio.h>
/* 2 points */
/** 
 * Make a program that takes a file-name on the command line and reads from it,
 * or input from stdin if no file-name is given, lines of "student" information
 * in the following format:
 * <flags> <firstname> <lastname>
 * <flags> is an integer representing a bitfield of flags, each bit having the
 *  following meaning:
 *  bit 0: "Born in Indiana"        bit 5: "Lives off campus"
 *  bit 1: "On probation"           bit 6: "Vegetarian"
 *  bit 2: "Owes tuition"           bit 7: "Transfer Student"
 *  bit 3: "Scholarship student"    bit 8: "Has overdue library books"
 *  bit 4: "No drivers license"
 *
 * For each line of input, print the students name (last name first) followed by
 * an itemized list of flags that apply to each student.
 * Example input/output:
 * > ./h4 test/students
 * Smith, Bob:
 *  - Born in Indiana
 *  - Owes tuition
 *  - Scholarship student
 *  - Lives off campus
 * 
 * Jones, Sally:
 *  - On probation
 *  - Scholarship student
 *  - No drivers license
 * ...
 */

int main(int argc, char const *argv[])
{
  char * flags[9] ={"Born in Indiana", "On probation","Owes tuition","Scholarship student","No drivers license",
		    "Lives off campus","Vegetarian","Transfer Student","Has overdue library books" };
  FILE * fp = stdin;
  char firstName[100], lastName [100];
  int  flag;
  
  if(argc>1)
    fp = fopen(argv[1],"r");

  while(fscanf(fp, "%d %s %s", &flag, firstName, lastName ) ==3) {
    
    printf("%s, %s:\n", lastName, firstName );
  
    for (int i = 0; i < 9; i++){
      if(flag & (1<<i)){
	printf(" - %s\n", flags[i]);

      }
    }
  printf("\n");

  }
  return 0;
}



