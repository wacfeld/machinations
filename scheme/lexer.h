#ifndef LEXER_H
#define LEXER_H

#include <string>

// token type
enum ttype {NONE, BOOL, IDENT, NUM, OPAR, CPAR, QUOT};

class Token {
public:
  ttype type;
  bool b;
  std::string i;
  int n;

  Token(bool b): type{BOOL}, b{b} {}
  Token(int n): type{NUM}, n{n} {}
  Token(std::string i): type{IDENT}, i{i} {}
  Token(ttype t): type{t} {}
};

bool isident(std::string s);
bool isbool(std::string s);
bool isint(std::string s);
bool isquote(std::string s);
bool isopar(std::string s);
bool iscpar(std::string s);

std::ostream &operator<<(std::ostream &out, ttype t);
std::ostream &operator<<(std::ostream &out, Token t);

#endif
