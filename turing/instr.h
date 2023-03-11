#ifndef INSTR_H
#define INSTR_H

#include <iostream>

class Instr {
public:

  int src;
  std::string scan, print;
  bool right;
  int dest;
  bool status;

  Instr(int src, std::string scan, std::string print, bool right, int dest): src{src}, scan{scan}, print{print}, right{right}, dest{dest}, status{false} {}
  Instr(): status{false} {}

  friend std::ostream &operator<<(std::ostream &out, Instr &in);
};

std::ostream &operator<<(std::ostream &out, Instr &in);
#endif
