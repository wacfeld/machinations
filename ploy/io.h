#ifndef IO_H
#define IO_H

#include "lexer.h"
#include "sexp.h"
#include "form.h"
#include "repl.h"

std::ostream &operator<<(std::ostream &out, Sexp *e);
std::ostream &operator<<(std::ostream &out, Atom &a);
void put_sexp(std::ostream &out, Sexp *e, int indent=0);
void flat_sexp(std::ostream &out, Sexp *e, bool open=true);

std::ostream &operator<<(std::ostream &out, std::vector<Token> &toks);
std::ostream &operator<<(std::ostream &out, ttype t);
std::ostream &operator<<(std::ostream &out, Token t);

#endif
