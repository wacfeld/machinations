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

Sexp *eval_form(Sexp *e)
{
  std::string &f = e->car->a.symb;

  if(f == "quote") {
    if(list_len(e->cdr) != 1) {
      std::cerr << f << " requires 1 argument\n";
    }

    return e->cdr->car;
  }

  else {
    std::cerr << "don't recognize syntactic form " << f << std::endl;
    exit(1);
  }
}
