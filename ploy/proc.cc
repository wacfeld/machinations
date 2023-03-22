#include "proc.h"
#include "sexp.h"

std::map<std::string, Sexp*> bindings;

void bind(std::string name, Sexp *e)
{
  bindings[name] = e;
}

void bind(std::string name, Sexp *(*f)(Sexp *))
{
  Sexp *e = new Sexp{true};
  e->a.type = PROCEDURE;
  e->a.proc.prim = true;
  e->a.proc.f = f;

  bind(name, e);
}
