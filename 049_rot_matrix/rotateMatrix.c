#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void rotateMatrix(FILE * f){
  char res[10][10];
  char line[12];
  int countLine = 0;
  while(fgets(line,12,f)!=NULL){
    //fprintf(stderr, "%c",line[11]);
    if(strchr(line,'\n')==NULL){
      fprintf(stderr, "Only 10 characters are allowed in each line.\n");
      exit(EXIT_FAILURE);
    }
    if(line[10]!='\n'){
      fprintf(stderr, "The characters in the line is less than 10.\n");
      exit(EXIT_FAILURE);
    }
    for(int i = 0;i<10;i++){
      res[i][10-countLine-1]=line[i];
    }
    if(++countLine>10){
      fprintf(stderr, "There are too many rows.\n");
      exit(EXIT_FAILURE);
    }
  }
  if(countLine<10){
    fprintf(stderr, "There are too less rows.\n");
    exit(EXIT_FAILURE);
  }
  for(int i = 0;i<10;i++){
    for(int j = 0;j<10;j++){
      fprintf(stdout,"%c",res[i][j]);
    }
    fprintf(stdout,"\n");
  }
}


int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr,"Usage: rotateMatrix inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  
  rotateMatrix(f);
  
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}