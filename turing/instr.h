#ifndef INSTR_H
#define INSTR_H

#include <iostream>

class Instr {
public:
  
  int src;
  std::string scan, print;
  bool right;
  int dest;
  
  // Instr(int src, int scan, int print, bool right, int dest): src{src}, scan{scan}, print{print}, right{right}, dest{dest} {}
  
  friend std::ostream &operator<<(std::ostream &out, Instr &in);
};

std::ostream &operator<<(std::ostream &out, Instr &in);
#endif
