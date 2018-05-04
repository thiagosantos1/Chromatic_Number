#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

/* 3 points */
/**
 * Create a program that takes zero or more paths on the command line (and
 * defaults to "." if one is not provided) and recursively lists the files and
 * directories in those paths and prints at the end a report of how much space
 * (in bytes) is used by all of the files and directories and finally a tally
 * of how many files and directories were encountered.
 * Example input/output:
 * > ./h6 /u1/junk/cs151
 * /u1/junk/cs151
 * /u1/junk/cs151/fstab
 * /u1/junk/cs151/hosts
 * /u1/junk/cs151/rgb.txt
 * /u1/junk/cs151/services
 * /u1/junk/cs151/words
 * 
 * Total bytes = 468487
 * 0 directories, 5 files
 */

long int totalBytes =0;
int totalDirec =0;
int totalFiles =0;
int direcPrinted = 0; // when it's a direct, make sure it's already printed
void calcSize(struct stat st);
void calcTotaltypes(struct stat st, char * path);
void list(const char *path, char *name);
void listFiles(const char *path);

int main(int argc, char const *argv[])
{
  if(argc <2){
    listFiles(".");
  }
  else{
    for (int i = 1; i < argc; i++){
      listFiles(argv[i]);
    }
  }
  printf("\nTotal bytes = %ld\n",totalBytes );
  printf("%d directories, %d files\n", totalDirec,totalFiles);
  return 0;
}

void calcSize(struct stat st)
{
  totalBytes += st.st_size;
}
void calcTotaltypes(struct stat st, char * path) // original one use *
{
  switch (st.st_mode & S_IFMT) {
    case S_IFDIR:  
      totalDirec++; 
      direcPrinted =1; // directory already printed
      listFiles(path);
      break;
    case S_IFREG:  
      totalFiles++;
      break;          
    default:                     
      break;
  }
}

void list(const char *path, char *name)
{
  struct stat st;
  char pathName[100];
  sprintf(pathName,"%s/%s",path,name);
  if(stat(pathName,&st) < 0){    
    printf("File %s cannot be stat it\n", name);
    exit(1);
  }
  if( (strcmp(name,".") != 0) && (strcmp(name,"..") != 0)  ){ 
    printf("%s\n",pathName ); 
    calcSize(st);
    calcTotaltypes(st,pathName);
    
  }
}
void listFiles(const char *path)
{
  struct dirent **nameFiles;
  int numbOfFiles;
  numbOfFiles = scandir(path, &nameFiles, NULL, alphasort);
  if (numbOfFiles < 0)
    printf("Error opening files in directory\n");
  else {
    if(direcPrinted <1)
      printf("%s\n",path);
    direcPrinted =0;
    for (int i = 0; i < numbOfFiles; i++){    	
      list(path,nameFiles[i]->d_name);
      free(nameFiles[i]);
    }
    free(nameFiles);
    
  }
}