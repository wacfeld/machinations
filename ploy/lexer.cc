#include <ctype.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <vector>

#include "lexer.h"

std::ostream &operator<<(std::ostream &out, Token t)
{
  out << t.type << ' ';
  if(t.type == BOOL) {
    out << t.b;
  } else if(t.type == IDENT) {
    out << t.i;
  } else if(t.type == NUM) {
    out << t.n;
  }

  return out;
}


std::ostream &operator<<(std::ostream &out, ttype t)
{
  if(t == BOOL) out << "BOOL";
  else if(t == IDENT) out << "IDENT";
  else if(t == NUM) out << "NUM";
  else if(t == OPAR) out << "OPAR";
  else if(t == CPAR) out << "CPAR";
  else if(t == QUOT) out << "QUOT";
  else if(t == NONE) out << "NONE";
  return out;
}

// std::vector<Token>

// write next token from s into t
// return length of token read
int nexttoken(std::string s, Token &T)
{
  // #t #f
  if(hasbool(s)) {
    if(s[1] == 't') {
      T = Token {true};
    } else {
      T = Token {false};
    }

    return 2;
  }

  // '
  else if(hasquote(s)) {
    T = Token {QUOT};
    return 1;
  }
  
  // (
  else if(hasopar(s)) {
    T = Token {OPAR};
    return 1;
  }

  // )
  else if(hascpar(s)) {
    T = Token {CPAR};
    return 1;
  }

  int lint = longestint(s);
  int lident = longestident(s);
  
  if((lint >= lident) && lint) {
    int n;
    std::istringstream iss{s};
    iss >> n;
    T = Token {n};
    return lint;
  }

  else if(lident) {
    std::string id;
    for(int i = 0; i < lident; i++) {
      id += s[i];
    }
    T = Token {id};
    return lident;
  }

  else {
    // std::cerr << "couldn't recognize token from " << s << std::endl;
    // exit(1);
    return 0;
  }
}

// boolean identifier integer ' ( )

bool isext(char c)
{
  static char ext[] = "!$%&*+-./:<=>?@^_~";
  return strchr(ext, c);
}

int longestident(std::string s)
{
  bool hasnondigit = false;
  unsigned long i;
  
  for(i = 0; i < s.size(); i++) {
    if(!isdigit(s[i]) && !isalpha(s[i]) && !isext(s[i])) {
      break;
    }

    if(!isdigit(s[i])) {
      hasnondigit = true;
    }
  }

  if(hasnondigit) {
    return i;
  } else {
    return 0;
  }
}

bool issign(char c)
{
  return (c == '+') || (c == '-');
}

int longestint(std::string s)
{
  if(s.empty()) {
    return 0;
  }

  if(issign(s[0])) {
    if(s.size() == 1 || !isdigit(s[1])) {
      return 0;
    }
  } else if(!isdigit(s[0])) {
    return 0;
  }
  
  unsigned long i;
  for(i = 1; i < s.size(); i++) {
    if(!isdigit(s[i])) {
      break;
    }
  }

  return i;
}

bool hasbool(std::string s)
{
  if(s.size() < 2) return false;
  return (s[0] == '#') && ((s[1] == 'f') || (s[1] == 't'));
}

bool hasquote(std::string s)
{
  if(s.empty()) return false;
  return s[0] == '\'';
}

bool hasopar(std::string s)
{
  if(s.empty()) return false;
  return s[0] == '(';
}

bool hascpar(std::string s)
{
  if(s.empty()) return false;
  return s[0] == ')';
}
