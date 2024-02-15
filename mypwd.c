#include <stdio.h>
#include <unistd.h>


#define RET_STATUS 0

int
main (int argc, char *argv[])
{
  char buff[100];
  char *path_name;


  if (argc != 1)
    {
      printf ("Usage: %s file_name\n", argv[0]);
      return -1;
    }

  path_name = getcwd (buff, 100);
  if (path_name == NULL)
    {
      printf (">> Failed to get the  current working directory");
      return -1;
    }

  printf ("%s \n", path_name);

  return RET_STATUS;
}
