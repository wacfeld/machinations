#ifndef PROC_H
#define PROC_H

#include <map>
#include <string>

class Sexp;

class Proc {
public:
  bool prim;
  Sexp *(*f)(Sexp *);
};

extern std::map<std::string, Sexp*> bindings;
void bind(std::string name, Sexp *e);

Sexp *call(Proc proc, Sexp *args);

#endif
