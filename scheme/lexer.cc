#include "lexer.h"

#include <ctype.h>
#include <string.h>

// boolean identifier integer ' ( )

bool isext(char c) {
  static char ext[] = "!$%&*+-./:<=>?@^_~";
  return strchr(ext, c);
}

bool isident(std::string s) {
  bool hasletter = false;
  for(char c : s) {
    if(isalpha(c)) {
      hasletter = true;
    }

    if(!isalpha(c) && !isdigit(c) && !isext(c)) {
      return false;
    }
  }

  return hasletter;
}
