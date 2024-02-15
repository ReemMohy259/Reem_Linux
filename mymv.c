#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <unistd.h>

#define RET_STATUS 0

int
main (int argc, char *argv[])
{

  int fd, fd1, num_read, num_write, delete;
  unsigned char buf[100];

  if (argc != 3)		// if there is an argument miss print an error message 
    {
      printf ("Usage: %s file_name\n", argv[0]);
      return -1;
    }

  fd = open (argv[1], O_RDONLY);	// open the source file 

  if (fd < 0)
    {				// if we cant open the source file 
      printf (">> Could not open the file\n");
      return -1;
    }
  printf (">> the file opend with fd = %d\n", fd);	// if the source file is opened 

  fd1 = open (argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);	//open the destination file if the file is not found so it will creat it and trunkate thefile first (delet all iths content)


  while ((num_read = read (fd, buf, 100)) != 0)
    {				//read the content of the source file with maximmum 100 byte each iterration 
      if (num_read < 0)
	{
	  printf (">> Could not read from the file\n");
	  return -1;
	}
      printf (">> I read %d bytes\n", num_read);

      num_write = write (fd1, buf, num_read);	// write the read bytes from source to the destination file 
      if (num_write < 0)
	{
	  printf (">> Could not write to the destination\n");
	  return -1;
	}
      printf ("\n>> I wrote %d bytes\n", num_write);
    }




// close the opened files 
  close (fd);
  close (fd1);

  delete = unlink (argv[1]);	// delte the source file 
  if (delete != 0)
    {
      printf (">> Failed to delete the file\n");
    }
  else
    printf (">> The file %s has been deleted\n", argv[1]);

  return RET_STATUS;
}
