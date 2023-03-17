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

  // ~Regex() {
  //   for(Regex *r : children) {
  //     delete r;
  //   }
  // }

  friend Regex *star(Regex *r);
  friend Regex *alt(std::vector<Regex *> rs);
  friend Regex *cat(std::vector<Regex *> rs);
  friend Regex *lit(char s);
  friend Regex *alt(std::string s);
  friend Regex *cat(std::string s);
  
private:
  Regex(rtype type, std::vector<Regex *> children, std::string lit):
    type{type}, children{children}, lit{lit} {}
  
};

Regex *star(Regex *r);
Regex *alt(std::vector<Regex *> rs);
Regex *alt(std::string s);
Regex *cat(std::vector<Regex *> rs);
Regex *cat(std::string s);
Regex *lit(char s);

Table *r2fa(Regex &reg, int minstate);

#endif
