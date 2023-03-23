#include "defaults.h"
#include "lexer.h"
#include "proc.h"
#include "forms.h"

void defaults()
{
  // bind("length", list_len);
  bind("+", add);
  bind("cons", cons);
}

bool isnum(Sexp *e)
{
  return e->atom && (e->a.type == NUMBER);
}

Sexp *cons(Sexp *args)
{
  check_length(__func__, args, 2);
  Sexp *a = args->car;
  Sexp *b = args->cdr->car;
  
  Sexp *e = new Sexp{false};
  e->car = a;
  e->cdr = b;
  return e;
}

Sexp *add(Sexp *args)
{
  static std::string usage = "usage: (add NUM NUM)";
  // if(list_len(args) != 2) {
  //   std::cerr << usage << std::endl;
  //   // exit(1);
  //   longjmp(repl_start, 1);
  // }
  check_length(__func__, args, 2);

  Sexp *a = args->car;
  Sexp *b = args->cdr->car;

  if(!isnum(a) || !isnum(b)) {
    std::cerr << usage << std::endl;
    longjmp(repl_start, 1);
  }

  int sum = a->a.num + b->a.num;
  Sexp *e = new Sexp{true};
  e->a.type = NUMBER;
  e->a.num = sum;
  
  return e;
}
