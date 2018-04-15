#include <stdlib.h>
#include <stdio.h>

/**
 * Create a function called printfile that takes a character string called
 * 'filename' and returns an integer as its return status.
 * - Open the file for reading and print the contents of the file one line at a
 *   time to the screen with (substitute the name of the file for %s):
 *     "---- %s ----\n"
 *   before and after the contents of the file.
 * - If you cannot open the file, return with a -1 from the function otherwise
 *   return a 0.
 */



/**
 * Create a main function that takes command line arguments:
 * - If no command line arguments are provided print the usage:
 *    "Usage %s <files...>\n" (where %s is replaced with argv[0])
 * - Otherwise pass each argv[i], i >= 1 to the printfile() function defined
 *   above.  If the return status of printfile is < 0, print the error message:
 *    "Unable to open %s for reading.\n" where %s is the file-name.
 * Example input/output:
 * ./h2 test/h1-testdata foo
 * ---- test/h1-testdata ----
 * 5.7 * 2.0
 * 6 + 3
 * 7 / 2
 * 8 * 3
 * 5 - 2
 * ---- test/h1-testdata ----
 * Unable to open foo for reading.
 */

int printfile(const char * fileName)
{

  FILE * fp;
  int ch;

  fp= fopen(fileName, "r");

  if(fp == NULL)
    return -1;

  printf("---- %s ----\n", fileName);
  while((ch=fgetc(fp)) != EOF){
    putchar(ch);
  }
  printf("---- %s ----\n", fileName);
  
  /* Or
   * 
   * while(fgets(buffer, sizeBuffer, fp) != NULL
   * 	printf(%s, buffer)
   * 
   * 
   * 
   */

  fclose(fp);

  return 0;

}

int main(int argc, char const *argv[])
{
  if(argc <2){
    printf("Usade %s <File Name>\n", argv[0]);
    exit(1);
  }

  for (int argument = 1; argument < argc; argument++){
    if(printfile(argv[argument]) < 0)
      printf("Unable to open %s for reading.\n", argv[argument]);
  }	
  return 0;
}








