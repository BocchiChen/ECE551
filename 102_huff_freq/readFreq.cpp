#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  std::ifstream ifs;
  ifs.open(fname, std::ios::in);
  char c;
  uint64_t * count = new uint64_t[257]();
  count[256] = 1;
  while (ifs.get(c)) {
    ++count[(unsigned char)c];
  }
  ifs.close();
  return count;
}
