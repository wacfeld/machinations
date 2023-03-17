#include "table.h"

// Instr *Table::lookup(int state, std::string symbol) {
//   for(Instr &in : instrs)
//   {
//     if(in.src == state
//         && in.scan == symbol) {
//       return &in;
//     }
//   }

//   return nullptr;
// }

std::ostream &operator<<(std::ostream &out, Table &tab) {
  out << "start " << tab.start << std::endl;
  
  out << "final";
  for(int f : tab.final) {
    out << " " << f;
  }
  out << std::endl;

  for(Instr &in : tab.instrs) {
    out << in;
  }

  return out;
}


