#include <stdio.h>
#include <stdlib.h>

unsigned power (unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans){
  if(power(x,y)!=expected_ans){
    printf("On no! The answer is incorrect!");
    exit(EXIT_FAILURE);
  }
}

int main(){
  run_check(2,2,4);
  run_check(8,5,32768);
  run_check(0,0,1);
  run_check(27362,2,748679044);
  return EXIT_SUCCESS;
}