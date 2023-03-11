#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * strs = malloc(sizeof(*strs));
  strs->strings = NULL;
  strs->len = 0;
  strs->unknown_count = 0;
  return strs;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if(name==NULL){
    c->unknown_count++;
    return;
  }
  for(size_t i = 0;i<c->len;i++){
    if(strcmp(name,c->strings[i].string)==0){
      c->strings[i].count++;
      return;
    }
  }
  c->len++;
  c->strings = realloc(c->strings,c->len*sizeof(*c->strings));
  one_count_t str;
  str.string = strdup(name);
  str.count = 1;
  c->strings[c->len-1] = str;
  return;
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for(size_t i = 0;i<c->len;i++){
    fprintf(outFile,"%s: %lu\n",c->strings[i].string,c->strings[i].count);
  }
  if(c->unknown_count!=0){
    fprintf(outFile,"<unknown> : %lu\n",c->unknown_count);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for(size_t i = 0;i<c->len;i++){
    free(c->strings[i].string);
  }
  free(c->strings);
  free(c);
}
