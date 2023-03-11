#include "file.hpp"
#include <string>
#include <stdlib.h>
#include <fstream>

//find and print all the paths leading to WIN page
int main(int argc, char** argv){
  if(argc!=2){
    std::cerr<<"The cyoa-step3 program should only take one single command line argument: a directory name!"<<std::endl;
    exit(EXIT_FAILURE);
  }
  File f;
  f.readFile(argv[1]);
  f.checkPages();
  f.findPathsToSuccess();
  return EXIT_SUCCESS;
}