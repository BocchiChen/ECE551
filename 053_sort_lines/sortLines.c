#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void sortAndPrint(FILE * f){
  char ** lines = NULL;
  char * line = NULL;
  size_t sz = 0;
  size_t len = 0;
  while (getline(&line,&sz, f) >= 0) {
    lines = realloc(lines,(len+1)*sizeof(*lines));
    lines[len++] = line;
    line = NULL;
  }
  free(line);
  sortData(lines,len);
  for(int i = 0;i<len;i++){
    printf("%s",lines[i]);
    free(lines[i]);
  }
  free(lines);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if(argc==1){
    FILE *f = stdin;
    if (f == NULL) {
      perror("Could not open the file!");
      return EXIT_FAILURE;
    }
    sortAndPrint(f);
  }else if(argc > 1){
    for(int i = 1; i<argc;i++){
      FILE *f = fopen(argv[i],"r");
      if (f == NULL) {
        fprintf(stderr,"Could not open file:%s",argv[i]);
        return EXIT_FAILURE;
      }
      sortAndPrint(f);
      if (fclose(f) != 0) {
        fprintf(stderr,"Failed to close the input file:%s",argv[i]);
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
