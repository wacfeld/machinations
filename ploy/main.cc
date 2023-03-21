#include <iostream>
#include <stdlib.h>

#include "lexer.h"

int main(int argc, char **argv) {
  Token T;
  while(nexttoken(std::cin, T)) {
    std::cout << "  " << T << std::endl;
  }
}
