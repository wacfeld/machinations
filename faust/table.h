#ifndef TABLE_H
#define TABLE_H

#include <vector>

#include "instr.h"

class Table {
public:
  std::vector<Instr> instrs;
  int start; // starting state
  std::vector<int> final; // final states
  
  // Instr *lookup(int state, std::string symbol);
  void add(Instr in) {
    instrs.push_back(in);
  }

  void add(Table *t) {
    for(Instr in : t->instrs) {
      instrs.push_back(in);
    }
  }
};

std::ostream &operator<<(std::ostream &out, Table &tab);

#endif
