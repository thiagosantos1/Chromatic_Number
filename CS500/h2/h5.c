
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

/* Author: Thiago Santos
 * Date: 08/30/2017
 * CS500
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(){
  
  
  int letter, countAlfabet[26];
  
  // inicialize vector 
  for(int i=0;i<26;i++)
    countAlfabet[i] = 0;
  
  letter=getchar();
  while(!feof(stdin)){
    letter = toupper(letter);
    if(letter == 'A')  
      countAlfabet[letter - 'A' ]++; 
     else if(letter == 'B')
      countAlfabet[letter - 'A' ]++; 
      else if(letter == 'C')
      countAlfabet[letter - 'A' ]++; 
	else if(letter == 'D')
	    countAlfabet[letter - 'A' ]++; 
	  else if(letter == 'E')
	    countAlfabet[letter - 'A' ]++; 
	    else if(letter == 'F')
		countAlfabet[letter - 'A' ]++; 
	      else if(letter == 'G')
		  countAlfabet[letter - 'A' ]++; 
		else if(letter == 'H')
		    countAlfabet[letter - 'A' ]++; 
		  else if(letter == 'I')
		      countAlfabet[letter - 'A' ]++; 
		    else if(letter == 'J')
			countAlfabet[letter - 'A' ]++; 
		      else if(letter == 'K')
			  countAlfabet[letter - 'A' ]++; 
			else if(letter == 'L')
			    countAlfabet[letter - 'A' ]++; 
			  else if(letter == 'M')
			      countAlfabet[letter - 'A' ]++; 
			    else if(letter == 'N')
				countAlfabet[letter - 'A' ]++;  
			      else if(letter == 'O')
				 countAlfabet[letter - 'A' ]++; 
				else if(letter == 'P')
				    countAlfabet[letter - 'A' ]++; 
				  else if(letter == 'Q')
				      countAlfabet[letter - 'A' ]++;  
				    else if(letter == 'R')
					countAlfabet[letter - 'A' ]++; 
				      else if(letter == 'S')
					  countAlfabet[letter - 'A' ]++; 
					else if(letter == 'T')
					      countAlfabet[letter - 'A' ]++; 
					  else if(letter == 'U')
					      countAlfabet[letter - 'A' ]++; 
					    else if(letter == 'V')
						countAlfabet[letter - 'A' ]++; 
					      else if(letter == 'X')
						countAlfabet[letter - 'A' ]++; 
						else if(letter == 'Z')
						    countAlfabet[letter - 'A' ]++; 
						  else if(letter == 'W')
						      countAlfabet[letter - 'A' ]++; 
						    else if(letter == 'Y')
							 countAlfabet[letter - 'A' ]++;  
   
    
  
    
	letter=getchar();					    
						    
  }

  printf("a : %d\nb : %d\nc : %d\nd : %d\ne : %d\n",countAlfabet[0], countAlfabet[1], countAlfabet[2], countAlfabet[3], countAlfabet[4]);
  printf("f : %d\ng : %d\nh : %d\ni : %d\nj : %d\n",countAlfabet[5], countAlfabet[6], countAlfabet[7], countAlfabet[8], countAlfabet[9]);
  printf("k : %d\nl : %d\nm : %d\nn : %d\no : %d\n",countAlfabet[10], countAlfabet[11], countAlfabet[12], countAlfabet[13], countAlfabet[14]);
  printf("p : %d\nq : %d\nr : %d\ns : %d\nt : %d\n",countAlfabet[15], countAlfabet[16], countAlfabet[17], countAlfabet[18], countAlfabet[19]);
  printf("u : %d\nv : %d\nw : %d\nx : %d\ny : %d\nz : %d\n",countAlfabet[20], countAlfabet[21], countAlfabet[22], countAlfabet[23], countAlfabet[24],countAlfabet[25]);
  

  
  return 0;
  
}