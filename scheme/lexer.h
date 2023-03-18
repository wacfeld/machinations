#ifndef LEXER_H
#define LEXER_H

#include "../faust/instr.h"
#include "../faust/table.h"
#include "../faust/regex.h"
#include "../faust/io.h"

// token type
enum ttype {BOOL, SYMB, NUM, OPAR, CPAR, QUOT};

class Token {
public:
  ttype type;
  bool b;
  std::string c; // cymbal
  int n;

  Token(bool b): type{BOOL}, b{b} {}
  Token(int n): type{NUM}, n{n} {}
  Token(std::string c): type{SYMB}, c{c} {}
  Token(ttype t): type{t} {}
};

std::map<ttype, Table *> exprs;

#endif
