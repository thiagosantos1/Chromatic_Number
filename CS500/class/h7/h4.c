/* 3 points */
/**
 * Define a structure called line, with two members:
 *   data - a character pointer (a string).
 *   next - a pointer to a line structure.
 */


/**
 * Define a function called trim, that takes a character array and trims the
 * white-space off the end of the string and returns the string as its value.
 */




/**
 * Create a function called newline that takes a character array (string) as
 * its parameter and creates a new line structure and fills in data with a copy
 * of the string passed to the function.  It should return address of the newly
 * allocated structure as its value.
 */




/**
 * Create a function called readfile that takes a path as its parameter.  It
 * should open the file and read lines from it, trimming them and allocating
 * line structures (using newline) into a linked list ordered in reverse order.
 * i.e. the last line in the file should be at the head of the linked list.
 * Return the head of the linked list or NULL if you fail to open the file.
 */




/**
 * Do not modify the main function below.
 * Example input/output:
 * ./h4 test/testfile 
 * Bubbles
 * Dave
 * Randy
 * Butters
 * ...
 */
int main(int argc, char *argv[])
{
  if (argc < 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    return 0;
  }
  struct line *lines = readfile(argv[1]);
  if (lines == NULL) {
    printf("Unable to read file.\n");
    return 1;
  }
  for(struct line *p = lines; p != NULL; p = p->next) {
    printf("%s\n", p->data);
  }
  return 0;
}
