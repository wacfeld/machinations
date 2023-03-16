#ifndef REGEX_H
#define REGEX_H

#include <vector>

enum rtype {CAT, ALT, LIT, STAR};

class Regex {
public:
  rtype typ;
  std::vector<Regex *> data;
  char lit;
};

#endif
