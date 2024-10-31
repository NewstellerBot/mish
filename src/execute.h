// execute.h

#ifndef EXECUTE_H
#define EXECUTE_H

#include <unistd.h>

int execute_command(char **args, int background, pid_t *pid_out);
int launch_program(char **args, int background, char *output_file, pid_t *pid_out);

#endif
