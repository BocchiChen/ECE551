#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  size_t sz = 0;
  while(inputName[sz]!='\0'){
    sz++;
  }
  char * res = malloc((sz+8)*sizeof(*res));
  for(size_t i = 0;i<sz;i++){
    res[i] = inputName[i];
  }
  char * tail = ".counts";
  for(size_t i = 0;i<7;i++){
    res[sz+i] = tail[i];
  }
  res[sz+7] = '\0';
  return res;
}
