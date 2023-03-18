#include "lexer.h"

std::map<ttype, Table *> exprs;

ttype classify(std::string s) {
  for(auto const &x : exprs) {
    ttype type = x.first;
    Table *tab = x.second;
    if(match(*tab, s)) {
      return type;
    }
  }

  return NONE;
}

void setup() {
  Regex *lower = alt("abcdefghijklmnopqrstuvwxyz");
  Regex *upper = alt("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  Regex *alpha = alt(RV {lower, upper});
  Regex *digit = alt("0123456789");
  Regex *alphanum = alt(RV {alpha, digit});
  Regex *ext = alt("!$%&*+-./:<=>?@^_~");
  
  Regex *sign = alt("+-");
  Regex *number = cat(RV{quest(sign), plus(digit)});
  exprs[NUM] = r2fa(*number);

  Regex *letter = alt(RV{alphanum, ext});
  Regex *ident = plus(letter);
  exprs[IDENT] = r2fa(*ident);
  
  Regex *boolean = alt(RV {cat("#t"), cat("#f")});
  exprs[BOOL] = r2fa(*boolean);

  Regex *opar = lit('(');
  exprs[OPAR] = r2fa(*opar);

  Regex *cpar = lit(')');
  exprs[CPAR] = r2fa(*cpar);

  Regex *quot = lit('\'');
  exprs[QUOT] = r2fa(*quot);

  // std::cerr << "success\n";
  
  cleanup();
}

// uncomment()
