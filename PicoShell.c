#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>


void
sigintHandler (int sig_num)	// Function that prevent termination from the whole shell using ctrl+c
{
  /* Reset handler to catch SIGINT next time.
     Refer http://en.cppreference.com/w/c/program/signal */
  signal (SIGINT, sigintHandler);
  printf
    ("\nPico Shell is not terminated using Ctrl+C \nUse (exit) command to terminate the shell \n");
  fflush (stdout);
}



void
ParsingStrings (char entered_string[], char *myargv[], int size)	// Function that parse the bassed command line
{

  char *token;
  int i = 0, j;

  token = strtok (entered_string, " ");

  while (token != NULL && i < size)
    {
      myargv[i] = strdup (token);	// Store the tokens in myargv array  
      token = strtok (NULL, " ");	// Tokatizing the same string 
      i++;
    }

  j = i;
  while (j < size)		// Fill myargv till the end by NULL pointers
    {
      myargv[j] = NULL;
      j++;
    }
}


int
main ()
{
  char entered_string[100];
  char *myargv[100];
  int i = 0;


  signal (SIGINT, sigintHandler);	// To prevent termination from the hole shell using ctrl+c

  while (1)
    {

      printf ("Enter your command: ");

      fgets (entered_string, sizeof (entered_string), stdin);

      entered_string[strlen (entered_string) - 1] = 0;	// Remove the \n character before parsing this string

      ParsingStrings (entered_string, myargv, 100);	// Tokanize the entered string


      // If the entered command is from the built in shell commands
      if (strcmp (myargv[0], "exit") == 0 || strcmp (myargv[0], "pwd") == 0
	  || strcmp (myargv[0], "echo") == 0 || strcmp (myargv[0], "cd") == 0)
	{

	  if (strcmp (myargv[0], "exit") == 0 && myargv[1] == NULL)	// If the command name is exit and with no arguments
	    {
	      printf ("Good Bye :) \n");
	      break;
	    }

	  if (strcmp (myargv[0], "pwd") == 0 && myargv[1] == NULL)	// If the command name is pwd and with no arguments
	    {
	      char buff[100];
	      char *path_name;

	      path_name = getcwd (buff, 100);
	      if (path_name == NULL)
		{
		  printf (">> Failed to get the  current working directory");
		  return -1;
		}
	      printf ("%s \n", path_name);

	    }

	  if (strcmp (myargv[0], "echo") == 0)	// If the command name is echo
	    {
	      int i = 1;

	      while (myargv[i])
		{
		  printf ("%s ", myargv[i]);
		  i++;
		}

	      printf ("\n");

	    }

	  if (strcmp (myargv[0], "cd") == 0)	// If the command name is cd
	    {
	      char *path = myargv[1];

	      if (chdir (path) != 0)
		{
		  printf ("Failed to chenge the directory\n");
		}
	    }
	}

      else			// If the command is not a build in command
	{
	  pid_t returned_pid = fork ();

	  if (returned_pid > 0)
	    {
	      int wstatus;
	      wait (&wstatus);
	    }

	  else if (returned_pid == 0)
	    {
	      char *new_program_envp[] = { NULL };

	      execvp (myargv[0], myargv);

	      printf ("ERROR\n");	// If the exec failed

	      return -1;
	    }

	  else
	    {
	      printf ("ERROR: I could not get a child\n");
	    }
	}

      for (int i = 0; i < 100 && myargv[i] != NULL; i++)	// Free the array of strings that dynamically allocated with strdup() function
	{
	  free (myargv[i]);
	}
    }
  return 0;
}
