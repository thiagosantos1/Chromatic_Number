#include <stdlib.h>
#include <stdio.h>
/**
 * Create a main function that takes command line arguments.
 * - This program opens two files (paths provided on the command line) and
 *   combines the two files one line at a time into one output.
 * - The first file provided is a line of text. Remove any trailing white-space
 *   from the end of the its line (white-space includes newlines (\n), tabs (\t)
 *   and spaces ( ).
 * - The second file is a list of numbers, each of which you must add one to
 *   when printing to the output.
 * - The two columns should be separated by a tab character.
 * 
 * To do this, open filea and fileb at the same time.  Use fgets(3) to read from
 * filea and fscanf(3) to read from fileb at the same time.  Stop if either
 * filea or fileb runs out of input.
 *
 * Example input/output:
 * ./h3 test/h3-testa test/h3-testb 
 * Test A  11
 * Test B  51
 * Test C  91
 * Test D  26
 * Test E  17
 * Test F  76
 */

int printfile(const char * fileName1, const char * fileName2)
{

  FILE * fp1, * fp2;
  int ch;
  int num;

  fp1= fopen(fileName1, "r");
  fp2= fopen(fileName2, "r"); 

  if(fp1 == NULL || fp2 == NULL)
    return -1;

  while( ((fscanf(fp2,"%d", &num)) != EOF) && (ch != EOF) )  {

    while( (((ch=fgetc(fp1)) != EOF)) ) {
      if(ch != '\b' && ch !='\t' && ch != '\n')
	putchar(ch);

      if(ch == '\n')
	break;

    }	
    if(ch != EOF)
      printf("\t%d\n", num +1);
  }
	fclose(fp1);
	fclose(fp2);

	return 0;

}

int main(int argc, char const *argv[])
{
  if(argc <2){
    printf("Usade %s <File Name>\n", argv[0]);
    exit(1);
  }
  if(printfile(argv[1], argv[2]) < 0)
    printf("Unable to open %s or %s for reading.\n", argv[1], argv[2]);
	
  return 0;
}




