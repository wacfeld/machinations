#include <iostream>
#include <vector>

#include "lexer.h"
#include "sexp.h"
#include "repl.h"
#include "io.h"

jmp_buf repl_start;

void repl()
{
  setjmp(repl_start);
  
  while(true) {
    std::vector<Token> toks = read_tokens(std::cin);
    if(toks.empty()) {
      std::cerr << "bye\n";
      exit(0);
    }

    toks = expand_quote(toks);
    Sexp *e = get_sexp(toks);
    Sexp *f = eval(e);
    std::cout << *f << std::endl;
  }
}
