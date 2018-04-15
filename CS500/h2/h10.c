
/**
 * Create a program that:
 * 1) May or may not take a single command line parameter to use as a seed to
 *    the random number generator (use atoi() to convert argv[1] to a integer
 *    feed the result to srand(3), but only if argc is > 1.
 * 2) Emulates rolling two 10 sided dice using the rand(3) function call and
 *    adding the result together. (should give a result between 2 and 20.
 * 3) Keep track of the results of 500 rounds of rolling the two dice.
 * 4) Print a sideways histogram plot of the results:
 * Example input/output:
 * ./h10
 *  2: #
 *  3: #########
 *  4: ##############
 *  5: #####################
 *  6: ###########################
 * ...
 * 18: ##################
 * 19: ############
 * 20: ######
 */

/* Author: Thiago Santos
 * Date: 08/30/2017
 * CS500
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  
  int seed, result, sumTotal[19] = {0};
 
  if(argc>1){
      seed = atoi(argv[1]);
      if(seed<=0){
	printf("Please, enter a valid digit!!!\n");
	return -1;
      }
  }

  else
    seed =3; // default
  
  
  srand(seed); // start seed
  
  for(int j = 0; j < 500; j++) {
      
      result =  (  (rand() %10 +1) + (rand() %10 +1) ); // 2 dices
      
      sumTotal[result-2]++;
      
  }
  
  for(int i=0; i<19;i++){
   
    printf("%2d: ", i+2);
    
    for(int j=0; j<sumTotal[i]; j++){
    
      printf("#");
    }
    printf("\n");
 
    
  }
  
  
  return 0;
  
  
}
