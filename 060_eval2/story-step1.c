#include "rand_story.h"

//replace tags with "cat"
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Missing or having too many input files!\n");
    exit(EXIT_FAILURE);
  }
  printRandomStory(argv[1], NULL, 0);
  return EXIT_SUCCESS;
}
