#include <stdio.h>
/**
 * Create a main function.  It does not require command line arguments. This
 * program uses scanf(3) to read two numbers separated by a character operator
 * and performs the mathematical operation printing the result.
 * Example input/output:
 * ./h1 < test/h1-testdata
 * 5.1 * 2
 *         10.20
 * 20 / 3
 *         6.67
 * 5 & 2
 *         Unknown operator [&]
 */

int main(int argc, char *argv[])
{
  /* Define two floating point variables and a character variable: */

  /**
   * Create a loop using scanf to read: a float followed by a character followed
   * by another float with spaces between:
   * For best results, don't use \n in the scanf format string.
   */


    /**
     * Inside the loop use a switch on the character, which should be one of
     * +,-,*,/.  For each case print the result of adding/subtracting/multiplying
     * or dividing num1 and num2 with a leading tab character.  If the operator
     * is not one of +-* or /, then print "\tUnknown operator [%c]\n":
     */

  float num1, num2;
  char operator;

  while( (scanf("%f %c %f", &num1, &operator, &num2)) != EOF){
    
    switch(operator){
      case  '/' :{

        printf("\t%.2f\n", num1/num2 );
        break;
      }
      case '*' : {
        printf("\t%.2f\n", num1*num2 );
        break;
      }
      case '+' : {
        printf("\t%.2f\n", num1+num2 );
        break;
      }
      case '-' : {
        printf("\t%.2f\n", num1-num2 );
        break;
      }

      default :
        printf("\tUnknown operator [%c]\n", operator  );
        break;

    }
  }
  return 0;
}
