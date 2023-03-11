#include "file.hpp"
#include <string>
#include <stdlib.h>
#include <fstream>

//add new functionality of player equipment and choice conditions
int main(int argc, char** argv){
  if(argc!=2){
    std::cerr<<"The cyoa-step4 program should only take one single command line argument: a directory name!"<<std::endl;
    exit(EXIT_FAILURE);
  }
  File f;
  f.readFile(argv[1]);
  f.checkPages();
  f.startReadingStory();
  return EXIT_SUCCESS;
}