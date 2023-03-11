#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int breaker(FILE * f){
  int c;
  int maxC=0;
  int maxF=0; 
  int count[26]={0};
  while((c=fgetc(f))!=EOF){
    if(isalpha(c)){
       c = tolower(c);
       if(++count[c-'a']>maxF){
         maxF = count[c-'a'];
         maxC = c-'a';
       }
    }
  }
  if(maxF==0){
    fprintf(stderr, "The file is empty.\n");
    exit(EXIT_FAILURE);
  }
  return maxC-4;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr,"Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  
  int key = breaker(f);
  fprintf(stdout, "%d\n", key>=0?key:26+key);
  
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
