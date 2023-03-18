#include "lexer.h"

std::map<ttype, Table *> exprs;

void setup() {
  Regex *lower = alt("abcdefghijklmnopqrstuvwxyz");
  Regex *upper = alt("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  Regex *alpha = alt(RV {lower, upper});
  Regex *digit = alt("0123456789");
  Regex *alphanum = alt(RV {alpha, digit});
  Regex *ext = alt("!$%&*+-./:<=>?@^_~");
  
  // Regex *ident = alt(RV {alphanum, alt});
  Regex *boolean = alt(RV {cat("#t"), cat("#f")});
  // Regex *number = 
  
  cleanup();
}

// uncomment()
