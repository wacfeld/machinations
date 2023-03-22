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
    // if(list_len(e->cdr) != 1) {
    //   std::cerr << f << " requires 1 argument\n";
    //   longjmp(repl_start, 1);
    // }
    check_length(f, e->cdr, 1);

    return e->cdr->car;
  }

  // else if(f == "if") {
  //   if(list_len(
  // }

  else {
    std::cerr << "don't recognize syntactic form " << f << std::endl;
    // exit(1);
    longjmp(repl_start, 1);
  }
}
