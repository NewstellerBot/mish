#include "shell.h"
#include "execute.h"
#include "parser.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

void shell_loop(FILE *input_stream) {
  char *line;
  int status = 1;

  do {
    // for interactive mode
    if (input_stream == stdin) {
      printf("mish> ");
      fflush(stdout);
    }

    // read line
    line = read_line(input_stream);
    if (line == NULL) {
      // EOF reached
      break;
    }

    // split line by '&' for parallel commands
    char *cmd_line;
    char *saveptr;
    char *line_copy = strdup(line);
    cmd_line = strtok_r(line_copy, "&", &saveptr);

    char *cmds[256];
    int cmd_count = 0;

    // splitting line by '&'
    while (cmd_line != NULL) {
      // remove leading and trailing whitespace from cmd_line
      while (isspace(*cmd_line))
        // \0 corresponds to null character
        cmd_line++;
      char *end = cmd_line + strlen(cmd_line) - 1;
      while (end > cmd_line && isspace(*end))
        *end-- = '\0';

      // copy of commands without leading/trailing whitespace
      cmds[cmd_count] = strdup(cmd_line);
      cmd_count++;
      // continue with next command
      cmd_line = strtok_r(NULL, "&", &saveptr);
    }

    // for storing processes ids
    pid_t pids[256];
    int bg = (cmd_count > 1) ? 1 : 0;

    // execute each command
    for (int i = 0; i < cmd_count; i++) {
      char **args = tokenize_line(cmds[i]);
      if (args[0] != NULL) {
        status = execute_command(args, bg, &pids[i]);
      } else {
        // empty command, continue
        pids[i] = -1; // no process id
      }
      // free args properly
      for (int j = 0; args[j] != NULL; j++) {
        free(args[j]);
      }
      free(args);
      free(cmds[i]);
    }

    // wait for all child processes if in parallel mode
    if (bg) {
      for (int i = 0; i < cmd_count; i++) {
        if (pids[i] > 0) {
          waitpid(pids[i], NULL, 0);
        }
      }
    }

    // Free memory
    free(line);
    free(line_copy);

  } while (status);
}
