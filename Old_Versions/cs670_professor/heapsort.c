
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10000

void printlist(char *s, int a[], int n);
void downheap(int a[], int n, int pos);
void heapsort(int a[], int n);

int main()
{
  int a[N];                     // malloc and realloc in a real program
  int i,j,k,n;

  n = 0;
  while(scanf("%d",&k) == 1)
    a[n++] = k;

  heapsort(a,n);
}
void printlist(char *s, int a[], int n)
{
  int i;

  printf("%s\n",s);
  for(i=0;i<n;i++)
    printf("%d\n",a[i]);
}
void downheap(int a[], int n, int pos)
{
  int lc,rc,mc;  /* indices of left, right and maximum child */

  for(;;){
    lc = (pos << 1) + 1;
    if(lc >= n)
      return;
    rc = lc + 1;
    if(rc >= n){
      mc = lc;
    } else {
      mc = (a[lc] >= a[rc]) ? lc : rc;
    }
    if(a[pos] >= a[mc])
      return;
    a[pos] ^= a[mc];
    a[mc]  ^= a[pos];
    a[pos] ^= a[mc];
    pos = mc;
  }
}
void heapsort(int a[], int n)
{
  int i;

/* start by making a heap */

  printlist("before making heap",a,n);
  for(i=(n-2)/2 ; i>=0 ; --i){         // (n-2)/2 is the last element with children
    downheap(a,n,i);
  }
  printlist("after makeheap",a,n);

/* move top elements to the end, reduce size of heap by one, until size is 1 */

  for(i=n-1;i>0;--i){
    a[0] ^= a[i];
    a[i] ^= a[0];
    a[0] ^= a[i];
    downheap(a,i,0);
  }
  printlist("after sorting",a,n);
}
