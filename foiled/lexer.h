#ifndef LEXER_H
#define LEXER_H

#include <map>
#include <vector>

#include "../faust/instr.h"
#include "../faust/table.h"
#include "../faust/regex.h"
#include "../faust/io.h"

// token type
enum ttype {NONE, BOOL, IDENT, NUM, OPAR, CPAR, QUOT};

class Token {
public:
  ttype type;
  bool b;
  std::string i; // cymbal
  int n;

  Token(bool b): type{BOOL}, b{b} {}
  Token(int n): type{NUM}, n{n} {}
  Token(std::string i): type{IDENT}, i{i} {}
  Token(ttype t): type{t} {}
};

std::ostream &operator<<(std::ostream &out, ttype);

void setup();
ttype classify(std::string s);

#endif
