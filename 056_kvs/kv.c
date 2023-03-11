#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  kvarray_t * res = malloc(sizeof(*res));
  res->pairs = malloc(sizeof(*res->pairs));
  res->len = 0;
  FILE * f = fopen(fname,"r");
  char * line = NULL;
  size_t size = 0;
  while(getline(&line,&size,f)>=0){
    res->len += 1;
    res->pairs = realloc(res->pairs,res->len*sizeof(*res->pairs));
    char * pos = strchr(line,'=');
    res->pairs[res->len-1].key = strndup(line,pos-line);
    pos++;
    char * pos_n = strchr(line,'\n');
    res->pairs[res->len-1].value = strndup(pos,pos_n-pos);
    free(line);
    line = NULL;
  } 
  free(line);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!\n");
    exit(EXIT_FAILURE);
  }
  return res;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for(size_t i = 0;i<pairs->len;i++){
    free(pairs->pairs[i].key);
    free(pairs->pairs[i].value);
  }
  free(pairs->pairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for(size_t i = 0;i<pairs->len;i++){
    printf("key = '%s' value = '%s'\n",pairs->pairs[i].key,pairs->pairs[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for(size_t i = 0;i<pairs->len;i++){
    if(strcmp(pairs->pairs[i].key,key)==0){
      return pairs->pairs[i].value;
    }
  }
  return NULL;
}
