#include "file.hpp"
#include <string>
#include <stdlib.h>
#include <fstream>

//print all pages based on the dictionary
int main(int argc, char** argv){
  if(argc!=2){
    std::cerr<<"The cyoa-step1 program should only take one single command line argument: a directory name!"<<std::endl;
    exit(EXIT_FAILURE);
  }
  File f;
  f.readFile(argv[1]);
  f.printAllPages();
  return EXIT_SUCCESS;
}
