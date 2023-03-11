#include <iostream>

#include "table.h"
#include "instr.h"

Table::Table(): num{0}, size{1} {
  instrs = new Instr[size];
}

Table::~Table() {
  delete[] instrs;
}

bool Table::add(int src, std::string scan, std::string print, bool right, int dest) {
  // check for collisions
  for(int i = 0; i < num; i++)
  {
    // matching starting state and symbol -> collision
    if(instrs[i].src == src
        && instrs[i].scan == scan) {
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

  instrs[num] = {src, scan, print, right, dest};
  num++;
  return true;
}

Instr *Table::lookup(int state, std::string symbol) {
  for(int i = 0; i < num; i++)
  {
    if(instrs[i].src == state
        && instrs[i].scan == symbol) {
      return instrs + i;
    }
  }

  return nullptr;
}

std::ostream &operator<<(std::ostream &out, Table &t) {
  for(int i = 0; i < t.num; i++)
  {
    // Instr &in = t.instrs[i];
    // char dir = in.right ? 'R' : 'L';
    // std::cout << in.src << ' ' << in.scan << " : " << in.print << ' ' << dir << " -> " << in.dest << std::endl;
    std::cout << t.instrs[i];
  }

  return out;
}
