#ifndef INSTR_H
#define INSTR_H

#include <vector>
#include <string>
#include <iostream>

class Instr {
public:
  int src;
  std::string scan; // "" means epsilon
  std::vector<int> dests;
  bool print; // print after occuring if true

  friend std::ostream &operator<<(std::ostream &out, Instr &in);
  friend void read_inst(std::string &line, Instr &inst);
};

std::ostream &operator<<(std::ostream &out, Instr &in);

void read_inst(std::string &line, Instr &inst);
#endif
