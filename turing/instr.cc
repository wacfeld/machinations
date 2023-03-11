#include "instr.h"

std::ostream &operator<<(std::ostream &out, Instr &in) {
  char dir = in.right ? 'R' : 'L';
  std::cout << (char) in.src << ' ' << (char) in.scan << " : " << (char) in.print << ' ' << dir << " -> " << (char) in.dest << std::endl;

  return out;
}
