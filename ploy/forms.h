#ifndef FORMS_H
#define FORMS_H

#include <set>
#include <string>

#include "sexp.h"
#include "io.h"
#include "repl.h"

extern std::set<std::string> forms;
bool is_form(Sexp *e);
Sexp *eval_form(Sexp *e);
void check_length(const std::string &f, Sexp *e, int len);

#endif
