#include "table.h"

Table::Table(): num{0}, size{1} {
  instrs = new Instr[size];
}

Table::~Table() {
  delete[] instrs;
}

bool Table::add(Instr &in) {
  // check for collisions
  for(int i = 0; i < num; i++)
  {
    // matching starting state and symbol -> collision
    if(instrs[i].src == in.src
        && instrs[i].scan == in.scan) {
      return false;
    }
  }
  
  // resize if necessary
  if(num == size) {
    size *= 2;
    Instr *_instrs = new Instr[size];
    
    for(int i = 0; i < num; i++)
    {
      _instrs[i] = instrs[i];
    }

    delete[] instrs;
    instrs = _instrs;
  }

  instrs[num] = in;
  num++;
  return true;
}

Instr *Table::lookup(int state, int symbol) {
  for(int i = 0; i < num; i++)
  {
    if(instrs[i].src == state
        && instrs[i].scan == symbol) {
      return instrs + i;
    }
  }

  return nullptr;
}
