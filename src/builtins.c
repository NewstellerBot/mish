#include "builtins.h"
#include "mish.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int cmd_cd(char **args) {
  if (args[1] == NULL || args[2] != NULL) {
    // cd requires exactly one argument
    write(STDERR_FILENO, error_message, strlen(error_message));
  } else {
    if (chdir(args[1]) != 0) {
      write(STDERR_FILENO, error_message, strlen(error_message));
    }
  }
  return 1;
}

int cmd_exit(char **args) {
  if (args[1] != NULL) {
    // exit does not take arguments
    write(STDERR_FILENO, error_message, strlen(error_message));
    return 1;
  }

// For testing, check a flag
#ifdef TESTING
  return 0; // Indicate that exit was called
#else
  exit(0);
#endif
}

int cmd_path(char **args) {
  // free old path
  for (int i = 0; i < path_count; i++) {
    free(path[i]);
  }
  free(path);

  // update path with new arguments
  path_count = 0;
  int i = 1;
  while (args[i] != NULL) {
    path_count++;
    i++;
  }

  path = malloc(sizeof(char *) * path_count);
  for (int j = 0; j < path_count; j++) {
    path[j] = strdup(args[j + 1]);
  }

  return 1;
}
