
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

char *cmd="/bin/ls";

char *args[]={
  "ls",
  "-l",
  "/",
  0
};

int main(int argc, char *argv[], char *envp[])
{
   int i;
   int status;
   int forkpid, mypid;   // process id

   forkpid = fork();
   if(forkpid == 0){
     execve(cmd, args, envp);
   } else {
     wait(&status);
     printf("child done\n");
   }
}
