#ifndef DEFAULTS_H
#define DEFAULTS_H

#include "sexp.h"
#include "repl.h"

// int list_len(Sexp *e);

void defaults();
bool isnum(Sexp *e);
Sexp *add(Sexp *args);

#endif
