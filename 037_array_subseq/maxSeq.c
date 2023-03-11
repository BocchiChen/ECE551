#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n){
  size_t maxLen = 0;
  size_t len = 1;
  for(int i = 0;i<=n;i++){
    if(i==0||i==n){
      maxLen = len>maxLen? len:maxLen;
    }else{
      if(*(array+i)>*(array+i-1)){
        len+=1;
      }else{
        maxLen = len>maxLen? len:maxLen;
        len = 1;
      }
    }
  }
  return n==0? 0:maxLen;
}