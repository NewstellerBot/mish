#include "parser.h"
#include "wish.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *read_line(FILE *input_stream) {
  char *line = NULL;
  size_t bufsize = 0;
  ssize_t nread;

  nread = getline(&line, &bufsize, input_stream);
  if (nread == -1) {
    // EOF or error
    if (line) {
      free(line);
    }
    return NULL;
  }

  // Remove trailing newline character
  if (line[nread - 1] == '\n') {
    line[nread - 1] = '\0';
  }

  return line;
}
char **tokenize_line(char *line) {
  int bufsize = 64;
  int position = 0;
  char **tokens = malloc(sizeof(char *) * bufsize);
  // check if malloc failed
  if (!tokens) {
    write(STDERR_FILENO, error_message, strlen(error_message));
    exit(1);
  }

  int i = 0;
  while (line[i] != '\0') {
    // skip whitespace
    while (isspace(line[i]))
      i++;

    // check for end of line
    if (line[i] == '\0')
      break;

    // Check for operators
    if (line[i] == '>' || line[i] == '&') {
      char op[2] = {line[i], '\0'};
      tokens[position] = strdup(op);
      position++;
      i++;
    } else {
      // collect a word
      int start = i;
      while (line[i] != '\0' && !isspace(line[i]) && line[i] != '>' &&
             line[i] != '&') {
        i++;
      }
      int length = i - start;
      char *word = malloc(length + 1);
      strncpy(word, &line[start], length);
      word[length] = '\0';
      tokens[position++] = word;
    }

    // resize tokens array if necessary
    if (position >= bufsize) {
      bufsize += 64;
      tokens = realloc(tokens, sizeof(char *) * bufsize);
      if (!tokens) {
        write(STDERR_FILENO, error_message, strlen(error_message));
        exit(1);
      }
    }
  }
  tokens[position] = NULL;
  return tokens;
}
