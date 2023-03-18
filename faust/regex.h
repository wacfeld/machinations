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

  // friend Regex *star(Regex *r);
  // friend Regex *alt(std::vector<Regex *> rs);
  // friend Regex *cat(std::vector<Regex *> rs);
  // friend Regex *lit(char s);
  // friend Regex *alt(std::string s);
  // friend Regex *cat(std::string s);
  
// private:
  Regex(rtype type, std::vector<Regex *> children, std::string lit);
  
};

// memory management
void cleanup();

Regex *plus(Regex *r);
Regex *star(Regex *r);
Regex *quest(Regex *r);
Regex *alt(std::vector<Regex *> rs);
Regex *alt(std::string s);
Regex *cat(std::vector<Regex *> rs);
Regex *cat(std::string s);
Regex *lit(char s);
Regex *quest(char c);

Table *r2fa(Regex &reg, int minstate);
Table *r2fa(Regex &reg);

typedef std::vector<Regex*> RV;


#endif
