// main.c

#include "shell.h"
#include "wish.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  FILE *input_stream = NULL;

  // initialize path to include /bin by default
  path_count = 1;
  path = malloc(sizeof(char *) * MAX_PATHS);
  path[0] = strdup("/bin");

  // if no argument is provided, run interactive shell
  if (argc == 1)
  {
    // if interactive set input_stream to stdin
    input_stream = stdin;
    shell_loop(input_stream);
  }
  else if (argc == 2)
  {
    // batch mode
    input_stream = fopen(argv[1], "r");
    // make sure file is opened
    if (input_stream == NULL)
    {
      write(STDERR_FILENO, error_message, strlen(error_message));
      exit(1);
    }
    // run shell loop
    shell_loop(input_stream);
    fclose(input_stream);
  }
  else
  {
    // Error: too many arguments
    write(STDERR_FILENO, error_message, strlen(error_message));
    exit(1);
  }

  // Cleanup and exit
  for (int i = 0; i < path_count; i++)
  {
    free(path[i]);
  }
  free(path);
  return 0;
}
