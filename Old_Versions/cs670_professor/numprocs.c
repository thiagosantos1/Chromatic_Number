
#include <stdio.h>
#include <sys/sysinfo.h>

int main(int argc, char *argv[])
{
  printf("%d %d\n", get_nprocs_conf(), get_nprocs());
  return 0;
}
