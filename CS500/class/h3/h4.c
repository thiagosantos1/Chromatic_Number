
/**
 * Do not modify main below. Write the function pyramid that takes an integer
 * argument and outputs a pyramid constructed of asterisks(*) that is that
 * number of rows high.
 * 
 * Example input/output:
 * ./h4 4
 *    *
 *   ***
 *  *****
 * *******
 */
int main(int argc, char *argv[])
{
  if (argc < 2) {
    printf("usage: h4 <number>\n");
    return 1;
  }
  pyramid(atoi(argv[1]));

  return 0;
}
