// tests/test_parser.c

#include "../parser.h"
#include "../wish.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple assertion function
void assert_equal(const char *expected, const char *actual,
                  const char *test_name) {
  if (strcmp(expected, actual) == 0) {
    printf("PASSED: %s\n", test_name);
  } else {
    printf("FAILED: %s\n\tExpected: %s\n\tActual: %s\n", test_name, expected,
           actual);
  }
}

void test_tokenize_line() {
  char line[] = "ls -l > output.txt";
  char **tokens = tokenize_line(line);

  // Check if tokens match expected values
  assert_equal("ls", tokens[0], "test_tokenize_line - tokens[0]");
  assert_equal("-l", tokens[1], "test_tokenize_line - tokens[1]");
  assert_equal(">", tokens[2], "test_tokenize_line - tokens[2]");
  assert_equal("output.txt", tokens[3], "test_tokenize_line - tokens[3]");

  // Clean up
  for (int i = 0; tokens[i] != NULL; i++) {
    free(tokens[i]);
  }
  free(tokens);
}

int main() {
  printf("Running tests for parser...\n");
  test_tokenize_line();
  return 0;
}
