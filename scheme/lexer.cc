#include "lexer.h"

std::map<ttype, Table *> exprs;

std::ostream &operator<<(std::ostream &out, ttype t) {
  if(t == BOOL) out << "BOOL";
  else if(t == IDENT) out << "IDENT";
  else if(t == NUM) out << "NUM";
  else if(t == OPAR) out << "OPAR";
  else if(t == CPAR) out << "CPAR";
  else if(t == QUOT) out << "QUOT";
  else if(t == NONE) out << "NONE";
  return out;
}

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
  // Regex *alphanum = alt(RV {alpha, digit});
  Regex *ext = alt("!$%&*+-./:<=>?@^_~");
  
  Regex *sign = alt("+-");
  Regex *number = cat(RV{quest(sign), plus(digit)});
  exprs[NUM] = r2fa(*number);

  Regex *alphaext = alt(RV{alpha, ext});
  Regex *alphanumext = alt(RV{alphaext, digit});
  // at least one non-digit
  Regex *ident = cat(RV{star(alphanumext), plus(alphaext), star(alphanumext)});
  exprs[IDENT] = r2fa(*ident);
  
  Regex *boolean = alt(RV {cat("#t"), cat("#f")});
  exprs[BOOL] = r2fa(*boolean);

  Regex *opar = lit('(');
  exprs[OPAR] = r2fa(*opar);

  Regex *cpar = lit(')');
  exprs[CPAR] = r2fa(*cpar);

  Regex *quot = lit('\'');
  exprs[QUOT] = r2fa(*quot);

  cleanup();
  std::cerr << "success\n";
  
}

// uncomment()
