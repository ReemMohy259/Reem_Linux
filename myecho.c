#include <stdio.h>


#define RET_STATUS 0

int
main (int argc, char *argv[])
{

  int i = 1;

  if (argc < 2)
    {
      printf ("Usage: %s file_name\n", argv[0]);
      return -1;
    }

  while (argv[i])
    {

      printf ("%s ", argv[i]);
      i++;
    }

  printf ("\n");




  return RET_STATUS;
}
