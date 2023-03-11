#ifndef TABLE_H
#define TABLE_H

class Table {
  Instr *instrs;
  int num;
  int size;

public:

  Table();
  ~Table();

  bool add(Instr &in); // returns false on failure to add (collision)
  Instr *lookup(int state, int symbol); // returns matching instruction or nullptr if not found
}

#endif
