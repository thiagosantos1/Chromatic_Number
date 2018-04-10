
#include <stdio.h>

typedef
  __uint128_t
ubig;

void print128(int ndigits, ubig x);

int main()
{
  ubig y;
  int i;

  y = 1;
  for(i=0;i<50;i++)
    y = y * (ubig) 3;
  print128(45,y);
}
void print128(int ndigits, ubig x)
{
  char s[ndigits+2];
  int i,j,k;
  
  k = ndigits+2;
  s[--k] = 0;
  s[--k] = '\n';
  while(x){
    j = (int) ( x % (ubig) 10);
    s[--k] = j + '0';
    x = x / (ubig) 10;
  }
  for(i=0;i<k;i++)
    s[i] = ' ';
  printf("%s", s);
}
