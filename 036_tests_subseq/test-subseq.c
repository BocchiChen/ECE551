#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void check_case(int * arr, size_t n, size_t expected) {
  if (expected != maxSeq(arr, n)) {
    exit(EXIT_FAILURE);
  }
}

int main() {
  int arr1[] = {0, 0, 0};
  check_case(arr1, 3, 1);
  int arr2[] = {1, 1, 2, 2};
  check_case(arr2, 4, 2);
  int arr3[] = {-1, -1, -1, -1};
  check_case(arr3, 4, 1);
  check_case(NULL, 0, 0);
  int arr4[] = {-9, -4, 2, 5, 2, -4, 11, 7, 9};
  check_case(arr4, 9, 4);
  return EXIT_SUCCESS;
}
