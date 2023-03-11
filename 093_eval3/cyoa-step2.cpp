#include "file.hpp"
#include <string>
#include <stdlib.h>
#include <fstream>

//check the validation of the composing of the dictionary and start to read story
int main(int argc, char** argv){
  if(argc!=2){
    std::cerr<<"The cyoa-step2 program should only take one single command line argument: a directory name!"<<std::endl;
    exit(EXIT_FAILURE);
  }
  File f;
  f.readFile(argv[1]);
  f.checkPages();
  f.startReadingStory();
  return EXIT_SUCCESS;
}