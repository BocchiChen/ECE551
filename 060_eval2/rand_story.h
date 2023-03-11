#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "provided.h"

//any functions you want your main to use

int checkNumber(char * str, int len);
category_t * createLRU();
int adjustLRU(category_t * LRU, const char * word);
void freeLRU(category_t * LRU);
void preventReuseWords(catarray_t * catarray, char * cat, const char * usedWord, int option);
int printRandomStory(char * filename, catarray_t * catarray, int option);
catarray_t * getCatarray(char * filename, int printOrNot);
void freeCatarray(catarray_t * cat);

#endif
