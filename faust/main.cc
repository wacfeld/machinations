#include <iostream>
#include <stdlib.h>
#include <fstream>

#include "instr.h"

// return false if comment (first non-whitespace is #) or blank
bool isvalid(std::string line) {
  for(long unsigned i = 0; i < line.length(); i++)
  {
    if(line[i] == '#')
      return false;

    else if(!isspace(line[i])) {
      return true;
    }
  }

  return false;
}

void read(int argc, char **argv, std::vector<Instr> &instrs) {
  if(argc < 2) {
    std::cerr << "usage: " << argv[0] << " INSTRUCTIONS [SYMBOL...]\n";
    exit(1);
  }

  std::ifstream ifs{argv[1]};
  std::string line;
  while(getline(ifs, line)) {
    if(!isvalid(line)) {
      continue;
    }
    
    Instr in;
    read_inst(line, in);
    instrs.push_back(in);
  }
}

// // true if exists direct epsilon move s1 -> s2
// std::set<int> eps(int s, std::vector<Instr> &instrs) {
//   std::set<int> dests;
  
//   for(Instr in : instrs) {
//     if(in.scan == "" && in.src == s) {
//       dests.insert(in.dest);
//     }
//   }

//   return dests;
// }

std::set<int> eps_closure(std::set<int> states, std::vector<Instr> &instrs) {
  
  do {
    
    // populate new_states
    std::set<int> new_states;
    for(int s : states) {
      for(Instr in : instrs) {
        if(in.scan == "" && in.src == s) {
          if(!states.contains(in.dest)) {
            new_states.insert(in.dest);
          }
        }
      }
    }

    // union new_states with states
    for(int s : new_states) {
      states.insert(s);
    }
    
  } while(!new_states.empty());

  return states;
}

std::set<int> transition(std::set<int> states, int symbol, std::vector<Instr> &instrs) {
  
  std::set<int> dests;
  
  // follow all state transitions for given symbol
  for(Instr in : instrs) {
    if(states.contains(state) && in.scan == symbol) {
      for(int d : in.dests) {
        dests.insert(d);
      }
    }
  }

  
}

int main(int argc, char **argv)
{
  std::vector<Instr> instrs;
  read(argc, argv, instrs);
}
