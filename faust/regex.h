#ifndef REGEX_H
#define REGEX_H

#include <vector>

#include "table.h"
#include "instr.h"

enum rtype {CAT, ALT, LIT, STAR};

class Regex {
public:
  rtype type;
  std::vector<Regex *> children;
  std::string lit;
};

Table *r2fa(Regex &reg, int minstate);

#endif
