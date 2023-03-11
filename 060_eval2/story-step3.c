#include "rand_story.h"

//tell random story
int main(int argc, char ** argv){
  if(argc!=3){
    fprintf(stderr,"Missing or having too many input files!\n");
    exit(EXIT_FAILURE);
  }
  catarray_t * cat = getCatarray(argv[1], 0);
  printRandomStory(argv[2], cat, 0);
  return EXIT_SUCCESS;
}