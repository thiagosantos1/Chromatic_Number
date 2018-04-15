/**
 * Like h1, create a program that opens and reads up to 1000 long integers from
 * a file, name provided on the command line, into an array.  Format the numbers
 * into evenly sized columns that fit inside of 50 columns.
 * Use the sprintf(3) function to determine how many characters each number is
 * and remember the width of the longest number and make each number column
 * that width + 2 spaces.
 * Remember to print a final newline for the last line if it requires it.
 * If the numbers read are:
 * AAA
 * BBBBB
 * CC
 * Then the program should output:
 *   AAA  BBBBB     CC  
 * Example input/output:
 * ./h7 test/h7-testdata
 *         1          10         100        1000  
 *     10000      100000     1000000    10000000  
 * 100000000          -1         -10        -100  
 *     -1000      -10000     -100000    -1000000  
 * -10000000  -100000000
 */

