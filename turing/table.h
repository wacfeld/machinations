#ifndef TABLE_H
#define TABLE_H

#include <string>

#include "instr.h"

class Table {
  Instr *instrs;
  int num;
  int size;

public:

  int start;
  int end;
  std::string blank;
  
  Table();
  ~Table();

  bool add(int src, std::string scan, std::string print, bool right, int dest); // returns false on failure to add (collision)
  Instr *lookup(int state, std::string symbol); // returns matching instruction or nullptr if not found

  friend std::ostream &operator<<(std::ostream &out, Table &t);
  
};

std::ostream &operator<<(std::ostream &out, Table &t);

#endif
