#include "defaults.h"
#include "lexer.h"
#include "proc.h"

void defaults()
{
  // bind("length", list_len);
  bind("+", add);
}

// get length of list
int list_len(Sexp *e)
{
  if(e->atom) {
    std::cerr << "cannot get length of non-list\n";
    exit(1);
  }
  
  else if(e == the_empty_list) {
    return 0;
  }
  
  else {
    return 1 + list_len(e->cdr);
  }
}

bool isnum(Sexp *e)
{
  return e->atom && (e->a.type == NUMBER);
}

Sexp *add(Sexp *args)
{
  static std::string usage = "usage: (add NUM NUM)";
  if(list_len(args) != 2) {
    std::cerr << usage << std::endl;
    exit(1);
  }

  Sexp *a = args->car;
  Sexp *b = args->cdr->car;

  if(!isnum(a) || !isnum(b)) {
    std::cerr << usage << std::endl;
    exit(1);
  }

  int sum = a->a.num + b->a.num;
  Sexp *e = new Sexp{true};
  e->a.type = NUMBER;
  e->a.num = sum;
  
  return e;
}
