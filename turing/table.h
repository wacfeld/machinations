#ifndef TABLE_H
#define TABLE_H

#include "instr.h"

class Table {
  Instr *instrs;
  int num;
  int size;

public:

  Table();
  ~Table();

  bool add(int src, int scan, int print, bool right, int dest); // returns false on failure to add (collision)
  Instr *lookup(int state, int symbol); // returns matching instruction or nullptr if not found

  friend std::ostream &operator<<(std::ostream &out, Table &t);
  
};

std::ostream &operator<<(std::ostream &out, Table &t);

#endif
