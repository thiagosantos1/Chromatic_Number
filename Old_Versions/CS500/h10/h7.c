/* 2 points */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/**
 * Proposed data structures you may wish to use for this assignment.  You may
 * not need or want to use all the aspects of the following structures. I for
 * instance didn't need the length property of array, however you don't need
 * necessarily to make your array data a linked list, but could be an array
 * of values, in which case you would probably need to use length.
 */
typedef enum { T_NUMBER, T_ARRAY } dtype_t;

typedef struct value {
  dtype_t dt;
  union {
    int num;
    struct array *arr;
  };
  struct value *next;
} value;

typedef struct array {
  int length;
  value *data;
} array;

/**
 * should allocate a return a new empty array:
 */
array *newarray()
{

}

/**
 * Should allocate a new value.  dt is the data-type and d is a void pointer
 * to either the number or an array.  Use type-casting to properly assign the
 * value in d to the num or arr union value in the value element based on the
 * type in dt.
 */
value *newvalue(dtype_t dt, void *d)
{

}

/**
 * Main entry point to the JSON parsing, this function should be recursive.  s
 * is the start of the string to be parsed. end is an optional pointer pointing
 * to where the parsing stopped at (same kind of mechanism used by strtol()).
 * Howto:
 * - Allocate a new array.
 * - Skip the first character (a [ which always starts a new array)
 * - As long as the current character is not null:
 *   - If the character is a [, start a new array (recursively call JSON_parse)
 *   - otherwise it must be a number, use strtol(s,&s,10) to get the number and
 *     move s past it.
 *   - Add either the new sub-array or number to the current array.
 *   - If the current character is now a ], skip past it and break from the
 *     loop.
 *   - If the current character is a comma, skip it and continue.
 * - If end is not NULL, set the dereference of it to the current value of s.
 * - return the array.
 */
array *JSON_parse(char *s, char **end)
{

}

/**
 * Prints out the array, it can be recursive and/or have helper functions.  It
 * needs to only handle 2D arrays.  It should display the data like:
 * [
 *   [ a, b, c ... ],
 *   [ d, e, f ... ],
 *   ...
 * ]
 * where the numbers are right padded to 6 characters. level is a helper value
 * indicating the depth into your array, which you may wish to use if you use
 * this function recursively.
 */
void print_array(array *a, int level)
{

}

/**
 * Function to read a file into a single string and return that string.  Hints:
 * - stat(2) the function to get it's size and allocate the buffer for that size.
 * - fread() the whole thing into the buffer.
 * - Return your allocated buffer -- make sure it's null byte terminated.
 */
char *readfile(char *filename)
{

}

/**
 * Do not modify main, you must use this main as given, you may add dgooebugging
 * statements as necessary.
 * Example input/output:
 * ./h7 test/matrix
 * [
 *   [   -10,  -319,   175,   175,   -62],
 *   [   133,   494,  -148,  -243,   -21],
 *   [   381,  -332,  -155,  -284,   303],
 *   [    45,  -345,    -8,   484,  -163],
 *   [  -258,  -173,   471,  -261,  -194]
 * ]
 */
int main(int argc, char *argv[])
{
  if (argc < 2) {
    printf("%s <JSON file>\n", argv[0]);
    return 0;
  }
  char *data = readfile(argv[1]);
  if (data == NULL) {
    printf("Failed to read file [%s]\n", argv[1]);
    return 1;
  }
  array *a = JSON_parse(data, NULL);
  if (a == NULL) {
    printf("Failed to parse JSON data.\n");
    return 1;
  }
  print_array(a, 0);
  return 0;
}
