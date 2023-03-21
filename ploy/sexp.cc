#include "sexp.h"

// convert tokens into sexp
// toks is guaranteed to contain exactly 1 sexp
Sexp *get_sexp(std::vector<Token> toks) {
  // atom
  if(toks.size() == 1) {
    Token &T = toks[0];
    
    Sexp *e = new Sexp(true);
    if(T.type == NUM) {
      e->a = Atom(T.n);
    }

    else if(T.type == IDENT) {
      e->a = Atom(T.i);
    }

    else if(T.type == BOOL) {
      e->a = Atom(T.b);
    }

    else {
      std::cerr << "unrecognized atom token" << T << std::endl;
      exit(1);
    }

    return e;
  }

  // list
  else {
    // remove opening and closing parenthesis
    if(toks[0].type != OPAR) {
      std::cerr << "list does not start with '('\n";
      exit(1);
    }
    toks.erase(toks.begin());

    if(toks.back().type != CPAR) {
      std::cerr << "list does not end with ')'\n";
      exit(1);
    }
    toks.pop_back();

    // recurse
    return get_list(toks);
  }
}

Sexp *get_list(std::vector<Token> toks) {
  
}

