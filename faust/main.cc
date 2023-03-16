#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <set>

#include "instr.h"
#include "table.h"

void usage(std::string exec) {
  std::cerr << "usage: " << exec << " INSTRUCTIONS SYMBOL...\n";
}

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

void read(int argc, char **argv, Table &tab) {
  if(argc < 2) {
    usage(argv[0]);
    exit(1);
  }

  std::ifstream ifs{argv[1]};
  std::string line;

  bool firstline = true;
  
  while(getline(ifs, line)) {
    if(!isvalid(line)) {
      continue;
    }

    if(firstline) {
      firstline = false;
      
      std::istringstream iss{line};
      if(!(iss >> tab.start)) {
        std::cerr << "bad header\n";
      }

      int d;
      while(iss >> d) {
        tab.final.push_back(d);
      }

      if(!iss.eof()) {
        std::cerr << "bad header\n";
      }
      continue;
    }
    
    Instr in;
    read_inst(line, in);
    tab.instrs.push_back(in);
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

std::set<int> eps_closure(std::set<int> states, Table &tab) {
  
  std::set<int> new_states;
  do {
    // populate new_states
    new_states = {};
    
    for(int s : states) {
      for(Instr in : tab.instrs) {
        if(in.scan == "" && in.src == s) {
          for(int d : in.dests) {
            if(!states.count(d)) {
              new_states.insert(d);
            }
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

std::set<int> transition(std::set<int> states, std::string symbol, Table &tab) {
  
  std::set<int> dests;
  
  // follow all state transitions for given symbol
  for(Instr in : tab.instrs) {
    if(states.count(in.src) && in.scan == symbol) {
      for(int d : in.dests) {
        dests.insert(d);
      }
    }
  }

  dests = eps_closure(dests, tab);
  return dests;
}

int main(int argc, char **argv)
{
  // read instructions
  Table tab;
  read(argc, argv, tab);

std::cout << "start " << tab.start << " end ";
for(int f : tab.final) {
  std::cout << f << " ";
}
std::cout << std::endl;

for(Instr in : tab.instrs) {
  std::cout << in;
}

  // perform epsilon closure on initial state
  std::set<int> states {tab.start};
  states = eps_closure(states, tab);

std::cout << "starting states ";
for(int s : states) {
  std::cout << s << " ";
}
std::cout << std::endl;

  if(argc < 3) {
    usage(argv[0]);
  }

  // run FA on tape
  for(int i = 2; i < argc; i++) {
    std::string symb = argv[i];
    states = transition(states, symb, tab);
  }
  
std::cout << "ending states ";
for(int s : states) {
  std::cout << s << " ";
}
std::cout << std::endl;
}