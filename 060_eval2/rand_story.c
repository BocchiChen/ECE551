#include "rand_story.h"

//This function check whether a string is an integer
int checkNumber(char * str, int len) {
  if (len == 0) {
    return 0;
  }
  int skip = 0;
  for (size_t i = 0; i < len; i++) {
    //skip the leading whitespaces and tabs
    if (skip == 0 && (str[i] == ' ' || str[i] == '\t'))
      continue;
    skip = 1;
    //check whether the string is a positive integer
    if (str[i] <= '0' || str[i] > '9') {
      return 0;
    }
  }
  return skip == 0 ? 0 : 1;
}

//This function create a LRU to record the most and least recently used word
category_t * createLRU() {
  category_t * LRU = malloc(sizeof(*LRU));
  LRU->name = NULL;
  LRU->words = NULL;
  LRU->n_words = 0;
  return LRU;
}

/*
This function adjusts the sequence of LRU whenever a word is used
The principle is to adjust the pointers in words, let the first pointer points to the most recently used word
Other pointers points to the words that are ordered by the used frequency
The last pointer always points to the least used word 
*/
int adjustLRU(category_t * LRU, const char * word) {
  //realloc to increase the LRU's space by 1,
  //adjust pointers other than the first one to point to the word one step above the word originally points to
  LRU->n_words++;
  LRU->words = realloc(LRU->words, LRU->n_words * sizeof(*LRU->words));
  for (size_t i = LRU->n_words - 1; i >= 1; i--) {
    LRU->words[i] = LRU->words[i - 1];
  }
  //make a copy of the word and let the first pointer points to it
  LRU->words[0] = strndup(word, strlen(word));
  return 1;
}

//This function frees the space occupied by the LRU
void freeLRU(category_t * LRU) {
  for (size_t i = 0; i < LRU->n_words; i++) {
    free(LRU->words[i]);
  }
  free(LRU->words);
  free(LRU->name);
  free(LRU);
}

/*
This function prevent chooseWord from choosing the word that has been used before
It implements the function by create a new words array with one less size than the
original one, and copy all the pointers' addresses to the new array except the pointer's
address pointing to the recently used word, which is freed. 
*/
void preventReuseWords(catarray_t * catarray,
                       char * cat,
                       const char * usedWord,
                       int option) {
  if (option == 0)
    return;
  for (size_t i = 0; i < catarray->n; i++) {
    if (strcmp(catarray->arr[i].name, cat) == 0) {
      //create preUsedWord pointing to a copy of the recently used word
      char * preUsedWord = strndup(usedWord, strlen(usedWord));
      //create another words array to replace the original one
      char ** newWords = catarray->arr[i].n_words - 1 == 0
                             ? NULL
                             : malloc((catarray->arr[i].n_words - 1) * sizeof(*newWords));
      size_t k = 0;
      //replaced is used to check whether the used word has been freed
      int replaced = 0;
      for (size_t j = 0; j < catarray->arr[i].n_words; j++) {
        if (replaced == 0 && strcmp(catarray->arr[i].words[j], preUsedWord) == 0) {
          //free the space of used word and set the pointer pointing to it to NULL
          free(catarray->arr[i].words[j]);
          catarray->arr[i].words[j] = NULL;
          replaced = 1;
        }
        else {
          //save the unaffected pointers to the replaced array
          newWords[k] = catarray->arr[i].words[j];
          catarray->arr[i].words[j] = NULL;
          k++;
        }
      }
      free(preUsedWord);
      //free the original words array
      free(catarray->arr[i].words);
      //replace words array in this category with the new one
      catarray->arr[i].words = newWords;
      catarray->arr[i].n_words--;
      return;
    }
  }
}

//This function prints the random story
int printRandomStory(char * filename, catarray_t * catarray, int option) {
  //create the LRU
  category_t * LRU = createLRU();
  FILE * f = fopen(filename, "r");
  //check whether the file exists
  if (f == NULL) {
    fprintf(stderr, "Cannot find the specified file: %s!\n", filename);
    exit(EXIT_FAILURE);
  }
  char * line = NULL;
  size_t sz = 0;
  char * res = NULL;
  size_t res_len = 0;
  ssize_t len = 0;
  while ((len = getline(&line, &sz, f)) >= 0) {
    for (ssize_t i = 0; i < len; i++) {
      //if the character read is not _, then realloc the space of res and save the word in res
      if (line[i] != '_') {
        res_len++;
        res = realloc(res, res_len * sizeof(*res));
        res[res_len - 1] = line[i];
      }
      else {
        char * start = &line[i + 1];
        size_t cat_len = 0;
        //check the end of _
        do {
          i++;
          cat_len++;
          //if we cannot find a corresponding _, a mistake is found
          if (line[i] == '\n' || line[i] == '\0') {
            fprintf(stderr, "Invalid input file!\n");
            exit(EXIT_FAILURE);
          }
        } while (line[i] != '_');
        char * cat = strndup(start, cat_len - 1);
        const char * replace_word = NULL;
        //check whether the category name is an integer or a string
        if (checkNumber(cat, cat_len - 1) == 0) {
          //call chooseWord to randomly select a word
          replace_word = chooseWord(cat, catarray);
          adjustLRU(LRU, replace_word);
        }
        else {
          if (strtoul(cat, NULL, 10) - 1 >= LRU->n_words) {
            fprintf(
                stderr,
                "Invalid story template, LRU does not have enough words to access!\n");
            exit(EXIT_FAILURE);
          }
          replace_word = LRU->words[strtoul(cat, NULL, 10) - 1];
          adjustLRU(LRU, replace_word);
          //add 1 to option to skip the process of preventing reused words if required
          if (option == 1)
            option++;
        }
        //replace the blank with replace_word
        for (size_t j = 0; replace_word[j] != '\0'; j++) {
          res_len++;
          res = realloc(res, res_len * sizeof(*res));
          res[res_len - 1] = replace_word[j];
        }
        //if option = 2, we know the original option is 1, and we do not want to call preventReuseWords since we
        //know LRU only saves words that have been used, so change option back to 1 to prepare for the next step
        if (option == 2)
          option = 1;
        else
          preventReuseWords(catarray, cat, replace_word, option);
        free(cat);
      }
    }
    free(line);
    line = NULL;
  }
  //free the occupied heap
  free(line);
  line = NULL;
  freeLRU(LRU);
  if (catarray != NULL)
    freeCatarray(catarray);
  //close the file
  if (fclose(f) != 0) {
    fprintf(stderr, "Fail to close the file!\n");
    exit(EXIT_FAILURE);
  }
  //add the final null terminator
  res_len++;
  res = realloc(res, res_len * sizeof(*res));
  res[res_len - 1] = '\0';
  //print the final result
  printf("%s", res);
  //free the space occupied by res
  free(res);
  res = NULL;
  return EXIT_SUCCESS;
}

//This function generates the category array
catarray_t * getCatarray(char * filename, int printOrNot) {
  FILE * f = fopen(filename, "r");
  //check whether the file exists
  if (f == NULL) {
    fprintf(stderr, "Cannot find the specified file: %s!\n", filename);
    exit(EXIT_FAILURE);
  }
  char * line = NULL;
  size_t sz = 0;
  ssize_t len = 0;
  catarray_t * res = malloc(sizeof(*res));
  res->n = 0;
  res->arr = NULL;
  while ((len = getline(&line, &sz, f)) >= 0) {
    //process the input line
    char * sep = strchr(line, ':');
    if (sep == NULL) {
      fprintf(stderr, "Cannot find a colon to separate category and name!\n");
      exit(EXIT_FAILURE);
    }
    size_t category_len = sep - line;
    size_t name_len =
        line[len - 1] == '\n' ? len - 2 - category_len : len - 1 - category_len;
    char * category = strndup(line, category_len);
    char * name = strndup(sep + 1, name_len);
    //check if the category name already exists in res (catarray_t)
    int found = 0;
    for (size_t i = 0; i < res->n; i++) {
      //search for the category name in res (catarray_t), if the category name appears in one category, then add the word to its words array
      if (strcmp(res->arr[i].name, category) == 0) {
        res->arr[i].n_words++;
        res->arr[i].words = realloc(res->arr[i].words,
                                    res->arr[i].n_words * sizeof(*(res->arr[i].words)));
        res->arr[i].words[res->arr[i].n_words - 1] = name;
        found = 1;
        free(category);
        category = NULL;
        break;
      }
    }
    //if the category name does not appear in res (catarray_t), then create a new category
    if (found == 0) {
      res->n++;
      res->arr = realloc(res->arr, res->n * sizeof(*res->arr));
      res->arr[res->n - 1].name = category;
      res->arr[res->n - 1].n_words = 1;
      res->arr[res->n - 1].words = malloc(sizeof(*(res->arr[res->n - 1].words)));
      res->arr[res->n - 1].words[0] = name;
    }
    //free space
    free(line);
    line = NULL;
  }
  free(line);
  line = NULL;
  if (fclose(f) != 0) {
    fprintf(stderr, "Fail to close the file!\n");
    exit(EXIT_FAILURE);
  }
  //print result
  if (printOrNot == 1)
    printWords(res);
  return res;
}

//This function frees the struct catarray_t
void freeCatarray(catarray_t * cat) {
  for (size_t i = 0; i < cat->n; i++) {
    free(cat->arr[i].name);
    for (size_t j = 0; j < cat->arr[i].n_words; j++) {
      if (cat->arr[i].words[j] != NULL)
        free(cat->arr[i].words[j]);
    }
    if (cat->arr[i].words != NULL)
      free(cat->arr[i].words);
  }
  free(cat->arr);
  free(cat);
}
