
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int a;
int b=3;
int c;
int d=4;

int fun(int f);

int main()
{
   int e;

   printf("main=%p\n", main);
   printf("fun =%p\n", fun);
   printf("printf = %p\n", printf);

   printf("a=%p\n", &a);
   printf("b=%p\n", &b);
   printf("c=%p\n", &c);
   printf("d=%p\n", &d);
   printf("e=%p\n", &e);
   fun(2);
}
int fun(int f)
{
   int g;
   int *h;

   h = malloc(10);
   printf("f=%p\n", &f);
   printf("g=%p\n", &g);
   printf("h=%p\n", &h);
   printf("x=%p\n",  h);

   if(f == 2)
     fun(1);
   return 1;
}

