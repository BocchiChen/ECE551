#include "rand_story.h"

//tell random story with specific function
int main(int argc, char ** argv){
  if(argc<3||argc>4){
    fprintf(stderr,"Missing or having too many input files!\n");
    exit(EXIT_FAILURE);
  }
  char argu[] = "-n";
  if(argc==4&&strcmp(argv[1],argu)==0){
    catarray_t * cat = getCatarray(argv[2], 0);
    printRandomStory(argv[3], cat, 1);
  }else if(argc==3&&strcmp(argv[1],argu)!=0){
    catarray_t * cat = getCatarray(argv[1], 0);
    printRandomStory(argv[2], cat, 0);
  }else{
    fprintf(stderr,"The order of inputs is incorrect!\n");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}