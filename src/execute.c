#include "execute.h"
#include "builtins.h"
#include "mish.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// executes a command
// returns 0 if everything is OK
// returns 1 if an error occurred
int execute_command(char **args, int background, pid_t *pid_out)
{
  if (args[0] == NULL)
  {
    // if command is empty return error
    return 1;
  }

  // from test 12: first argument cannot be a redirection operator
  // check if the first token is a redirection operator
  if (strcmp(args[0], ">") == 0)
  {
    write(STDERR_FILENO, error_message, strlen(error_message));
    return 1;
  }

  // check for built-in commands
  if (strcmp(args[0], "exit") == 0)
  {
    return cmd_exit(args);
  }
  else if (strcmp(args[0], "cd") == 0)
  {
    return cmd_cd(args);
  }
  else if (strcmp(args[0], "path") == 0)
  {
    return cmd_path(args);
  }

  // handle redirection
  char *output_file = NULL;
  int redirect_count = 0;
  int i = 0;
  while (args[i] != NULL)
  {
    if (strcmp(args[i], ">") == 0)
    {
      redirect_count++;
      if (redirect_count > 1)
      {
        // multiple redirection operators
        write(STDERR_FILENO, error_message, strlen(error_message));
        return 1;
      }
      if (args[i + 1] == NULL)
      {
        // missing output file
        write(STDERR_FILENO, error_message, strlen(error_message));
        return 1;
      }
      output_file = args[i + 1];
      args[i] = NULL; // terminate the args before '>'
      break;
    }
    i++;
  }

  // after handling redirection, ensure no extra arguments exist
  if (args[i + 2] != NULL)
  {
    // extra arguments after output file
    write(STDERR_FILENO, error_message, strlen(error_message));
    return 1;
  }
  return launch_program(args, background, output_file, pid_out);
}

int launch_program(char **args, int background, char *output_file,
                   pid_t *pid_out)
{
  pid_t pid;
  int status;
  char executable_path[1024];
  int found = 0;

  pid = fork();
  if (pid == 0)
  {
    // child process

    // handle output redirection
    if (output_file != NULL)
    {
      // open the output file
      int fd = open(output_file, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
      if (fd < 0)
      {
        // error opening the file
        write(STDERR_FILENO, error_message, strlen(error_message));
        exit(1);
      }
      // redirect stdout and stderr to the file
      // dup2 will close the file descriptor if it is already open
      dup2(fd, STDOUT_FILENO);
      dup2(fd, STDERR_FILENO);
      close(fd);
    }

    // search for executable in the path directories
    for (int i = 0; i < path_count; i++)
    {
      // construct the full path to the executable
      snprintf(executable_path, sizeof(executable_path), "%s/%s", path[i],
               args[0]);
      if (access(executable_path, X_OK) == 0)
      {
        found = 1;
        execv(executable_path, args);
        // if execv returns, an error occurred
        write(STDERR_FILENO, error_message, strlen(error_message));
        exit(1);
      }
    }
    if (!found)
    {
      // command not found in any path
      write(STDERR_FILENO, error_message, strlen(error_message));
      exit(1);
    }
  }
  else if (pid < 0)
  {
    // fork failed
    write(STDERR_FILENO, error_message, strlen(error_message));
    return 1;
  }
  else
  {
    // parent process
    *pid_out = pid;
    if (!background)
    {
      waitpid(pid, &status, 0);
    }
  }

  return 1;
}
