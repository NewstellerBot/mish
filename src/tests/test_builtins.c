// tests/test_builtins.c

#include "../builtins.h"
#include "../wish.h" // To access global variables
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

void assert_int_equal(int expected, int actual, const char *test_name) {
  if (expected == actual) {
    printf("PASSED: %s\n", test_name);
  } else {
    printf("FAILED: %s\n\tExpected: %d\n\tActual: %d\n", test_name, expected,
           actual);
  }
}

// Test cmd_path function
void test_cmd_path() {
  char *args1[] = {"path", "/bin", "/usr/bin", NULL};
  cmd_path(args1);

  // Check path count and first path
  assert_int_equal(2, path_count, "test_cmd_path - path_count");
  assert_equal("/bin", path[0], "test_cmd_path - path[0]");
  assert_equal("/usr/bin", path[1], "test_cmd_path - path[1]");

  // Free paths for next test
  for (int i = 0; i < path_count; i++) {
    free(path[i]);
  }
  path_count = 0;
}

// Main function to run all tests
int main() {
  printf("Running tests for built-ins...\n");
  test_cmd_path();
  return 0;
}

