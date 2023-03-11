#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

#include "bstmap.h"
#include "map.h"

int main(void) {
  BstMap<int, int> map;
  try {
    map.add(1, 1);
    map.add(2, 2);

    std::cout << "Lookup key is: " << 1 << " value is: " << map.lookup(1) << std::endl;
    std::cout << "Lookup key is: " << 2 << " value is: " << map.lookup(2) << std::endl;

    map.remove(2);
    map.add(10, 3);
    map.add(5, 6);
    map.remove(5);
    //std::cout << "Lookup key is: " << 2 << " value is: " << map.lookup(2) << std::endl;
    //std::cout << "Lookup key is: " << 1 << " value is: " << map.lookup(1) << std::endl;
  }
  catch (std::exception & e) {
    std::cerr << e.what() << std::endl;
  }
  return EXIT_SUCCESS;
}