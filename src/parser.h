#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>

char *read_line(FILE *input_stream);
char **tokenize_line(char *line);

#endif
