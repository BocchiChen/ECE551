#include <cmath>
#include <iostream>
#include <assert.h>
#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high);

class CountedIntFn : public Function<int,int>{
protected:
  unsigned remaining;
  Function<int,int> * f;
  const char * mesg;
public:
  CountedIntFn(unsigned n, Function<int,int> * fn, const char * m): remaining(n), f(fn), mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr,"Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }

};

class LinearFunction: public Function<int, int>{
public:
  virtual int invoke(int arg){
    return arg;
  }
};

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int invoke_times;
  if (high > low) {
    invoke_times = log2(high - low) + 1;
  }
  else {
    invoke_times = 1;
  }
  CountedIntFn * fc = new CountedIntFn(invoke_times, f, mesg);
  int ans = binarySearchForZero(fc, low, high);
  if (ans != expected_ans) {
    fprintf(stderr, "The result of the binary search function is wrong!:%s\n",mesg);
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  LinearFunction lf;
  check(&lf, -5, 7, 0, "including positive and negative integers\n");
  check(&lf, 0, 5, 0, "integers including zero\n");
  check(&lf, -9, 0, -1, "integers excluding zero\n");
  check(&lf, 3, 9, 3, "all positive integers\n");
  check(&lf, -11, -1, -2, "all negative integers\n");
  return EXIT_SUCCESS;
}