#include <iostream>
#include <stdlib.h>

#include "lexer.h"
#include "sexp.h"

int main(int argc, char **argv) {
  the_empty_list = new Sexp{false};
  // Token T;
  // while(nexttoken(std::cin, T)) {
  //   std::cout << "  " << T << std::endl;
  // }

  std::vector<Token> toks = read_tokens(std::cin);
  for(Token &T : toks) {
    std::cout << "  " << T << std::endl;
  }

  Sexp *e = get_sexp(toks);
  put_sexp(std::cout, e);
}
