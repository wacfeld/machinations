#include "defaults.h"
#include "forms.h"

// syntactic forms are quote, if, begin, cond, etc.
std::set<std::string> forms {
  "quote",
};

// true if e is syntactic form
bool is_form(Sexp *e)
{
  if(!e->atom)
    return false;

  if(e->a.type != SYMBOL)
    return false;

  return forms.count(e->a.symb);
}

void check_length(std::string &f, Sexp *e, int len) {
  int ll = list_len(e);
  if(ll != len) {
    std::cerr << f << " requires " << len << " argument(s); received " << ll << std::endl;
    longjmp(repl_start, 1);
  }
}

Sexp *eval_form(Sexp *e)
{
  std::string &f = e->car->a.symb;

  if(f == "quote") {
    check_length(f, e->cdr, 1);

    return index(e, 2);
  }

  else if(f == "if") {
    check_length(f, e->cdr, 3);

    Sexp *cond = eval(e->cdr->car);
  }

  else {
    std::cerr << "don't recognize syntactic form " << f << std::endl;
    // exit(1);
    longjmp(repl_start, 1);
  }
}
