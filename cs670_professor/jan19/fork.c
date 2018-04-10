
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
   int i;
   int forkpid, mypid;   // process id

   for(i = 0 ; i < 10 ; i++){
     forkpid = fork();
     if(forkpid == 0)
       break;
   }
   mypid = getpid();
   printf("My pid: %5d, fork return value: %5d\n",
     mypid, forkpid);
}
