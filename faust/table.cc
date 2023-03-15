#include "table.h"

Instr *Table::lookup(int state, std::string symbol) {
  for(Instr &in : instrs)
  {
    if(in.src == state
        && in.scan == symbol) {
      return &in;
    }
  }

  return nullptr;
}
