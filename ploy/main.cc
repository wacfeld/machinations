#include <iostream>
#include <stdlib.h>

#include "lexer.h"
#include "sexp.h"
#include "io.h"
#include "defaults.h"

void repl()
{
  while(true) {
    std::vector<Token> toks = read_tokens(std::cin);
    if(toks.empty()) {
      std::cerr << "bye\n";
      exit(0);
    }

    toks = expand_quote(toks);
    Sexp *e = get_sexp(toks);
    Sexp *f = eval(e);
    std::cout << f << std::endl;
  }
  
}

int main(int argc, char **argv)
{
  defaults();
  the_empty_list = new Sexp{false};
  // Token T;
  // while(nexttoken(std::cin, T)) {
  //   std::cout << "  " << T << std::endl;
  // }

  repl();

  // std::vector<Token> toks = read_tokens(std::cin);
  // toks = expand_quote(toks);
  // // for(Token &T : toks) {
  // //   std::cout << "  " << T << std::endl;
  // // }
  // // std::cout << toks << std::endl;
  
  // Sexp *e = get_sexp(toks);
  // std::cout << e << std::endl;
  // Sexp *f = eval(e);
  // std::cout << f << std::endl;
  // // std::cout << list_len(e) << std::endl;
}
