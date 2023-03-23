#ifndef DEFAULTS_H
#define DEFAULTS_H

#include "sexp.h"
#include "repl.h"

// int list_len(Sexp *e);

void defaults();
bool isnum(Sexp *e);
Sexp *cons(Sexp *args);
Sexp *car(Sexp *args);
Sexp *cdr(Sexp *args);
Sexp *add(Sexp *args);

#endif
