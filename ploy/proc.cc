#include "proc.h"

std::map<std::string, Sexp*> bindings;

void bind(std::string name, Sexp *e)
{
  bindings[name] = e;
}

void bind(std::string name, Sexp *(*f)(Sexp *))
{
  // Sexp *e = new Sexp{false};
}
