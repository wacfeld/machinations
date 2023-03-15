#ifndef TABLE_H
#define TABLE_H

#include <vector>

#include "instr.h"

class Table {
public:
  std::vector<Instr> instrs;
  int start; // starting state
  std::vector<int> final; // final states
  
  Instr *lookup(int state, std::string symbol);
};

#endif
