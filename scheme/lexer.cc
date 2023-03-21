#include "lexer.h"

#include <ctype.h>
#include <string.h>
#include <iostream>

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

// write next token from s into t
int nexttoken(std::string s, Token &t) {
  for(int i = 1; i < s.size(); i++) {
    
  }
}

// boolean identifier integer ' ( )

bool isext(char c)
{
  static char ext[] = "!$%&*+-./:<=>?@^_~";
  return strchr(ext, c);
}

bool isident(std::string s)
{
  if(s.empty()) {
    return false;
  }
  
  bool hasnondigit = false;
  for(char c : s) {
    if(isalpha(c) || isext(c)) {
      hasnondigit = true;
    }

    if(!isalpha(c) && !isdigit(c) && !isext(c)) {
      return false;
    }
  }

  return hasnondigit;
}

bool isbool(std::string s)
{
  return (s == "#f") || (s == "#t");
}

bool issign(char c)
{
  return (c == '+') || (c == '-');
}

// optional sign followed by 1 or more digits
bool isint(std::string s)
{
  if(s.empty()) {
    return false;
  }

  if(issign(s[0])) {
    if(s.size() == 1) {
      return false;
    }
  } else if(!isdigit(s[0])) {
    return false;
  }
  
  for(unsigned long i = 1; i < s.size(); i++) {
    if(!isdigit(s[i])) {
      return false;
    }
  }
  
  return true;
}

bool isquote(std::string s)
{
  return s == "'";
}

bool isopar(std::string s)
{
  return s == "(";
}

bool iscpar(std::string s)
{
  return s == ")";
}
