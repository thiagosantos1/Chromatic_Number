
/**
 * Make a program that reads characters from the stdin and keeps track of how
 * many of each letter (a-z) it reads.  Uppercase letters should be counted the
 * same as a lowercase letter (i.e. 'a' and 'A' are both counted as an 'a'.)
 * After all the characters have been read, print out a listing of the counts
 * for each letter in the form of "letter : count".
 * 
 * Example input/output:
 * ./h5 < Makefile
 * a : 22
 * b : 9
 * c : 35
 * d : 18
 * e : 9
 * f : 23
 * ...
 * 
 * Hint: To do this problem correctly, you need an array that is 26 integers
 * in size.  Initialize the arrays elements to all zero before entering the
 * input loop.  For each character read, if it's a letter add one to that
 * characters array index ('a' (and 'A') should be index 0, 'b' index 1, and so
 * on.). After the loop, print out the values in the array with the character
 * it represents.
 */

