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

  Token(): type{NONE} {}
  Token(bool b): type{BOOL}, b{b} {}
  Token(int n): type{NUM}, n{n} {}
  Token(std::string i): type{IDENT}, i{i} {}
  Token(ttype t): type{t} {}
};

int nexttoken(std::string s, Token &T);

bool hasbool(std::string s);
bool hasquote(std::string s);
bool hasopar(std::string s);
bool hascpar(std::string s);
int longestident(std::string s);
int longestint(std::string s);

std::ostream &operator<<(std::ostream &out, ttype t);
std::ostream &operator<<(std::ostream &out, Token t);

#endif
