#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>

int main(int argc, char ** argv){
  if(argc==1){
    std::string str;
    std::vector<std::string> line;
    while(getline(std::cin,str)){
      line.push_back(str);
    }
    std::sort(line.begin(),line.end());
    std::vector<std::string>::iterator it = line.begin();
    while(it!=line.end()){
      std::cout<<*it<<std::endl;
      ++it;
    }
  }else{
    for(int i = 1;i<argc;i++){
      std::ifstream is(argv[i],std::ifstream::in);
      if(!is.is_open()){
        std::cerr<<"Can't open file"<<std::endl;
        exit(EXIT_FAILURE);
      }
      std::string str;
      std::vector<std::string> line;
      while(getline(is,str)){
        line.push_back(str);
      }
      std::sort(line.begin(),line.end());
      std::vector<std::string>::iterator it = line.begin();
      while(it!=line.end()){
        std::cout<<*it<<std::endl;
        ++it;
      }
      is.close();
    }
  }
  return EXIT_SUCCESS;
}