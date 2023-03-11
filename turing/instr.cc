#include "instr.h"

std::ostream &operator<<(std::ostream &out, Instr &in) {
  char dir = in.right ? 'R' : 'L';
  std::cout << in.src << ' ' << in.scan << " : " << in.print << ' ' << dir << " -> " << in.dest << std::endl;

  return out;
}
