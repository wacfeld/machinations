#include <iostream>
#include <stdlib.h>

#include "lexer.h"

int main(int argc, char **argv) {
  // Token T;
  // while(nexttoken(std::cin, T)) {
  //   std::cout << "  " << T << std::endl;
  // }

  std::vector<Token> toks = read_tokens(std::cin);
  for(Token &T : toks) {
    std::cout << "  " << T << std::endl;
  }
}
