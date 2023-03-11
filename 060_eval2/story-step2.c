#include "rand_story.h"

//create, print and free the catarray_t
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Missing or having too many input files!\n");
    exit(EXIT_FAILURE);
  }
  catarray_t * cat = getCatarray(argv[1], 1);
  freeCatarray(cat);
  return EXIT_SUCCESS;
}
