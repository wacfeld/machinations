#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <set>

#include "instr.h"
#include "table.h"
#include "regex.h"
#include "io.h"

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
      for(Instr &in : tab.instrs) {
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
  for(Instr &in : tab.instrs) {
    if(states.count(in.src) && in.scan == symbol) {
      for(int d : in.dests) {
        dests.insert(d);
      }
    }
  }

  dests = eps_closure(dests, tab);
  return dests;
}

// returns true if accepted
bool run(Table &tab, std::vector<std::string> tape, bool verbose) {
  std::set<int> states{tab.start};
  states = eps_closure(states, tab);
  
  if(verbose) {
    std::cout << "starting states ";
    std::cout << states;
  }

  for(std::string s : tape) {
    states = transition(states, s, tab);
    // for(int s : states) {
    //   std::cout << s << " ";
    // }
    // std::cout << std::endl;
    if(verbose) {
      std::cout << states;
    }
  }

  bool accept = false;
  for(int f : tab.final) {
    if(states.count(f)) {
      accept = true;
    }
  }

  return accept;
}

bool run(Table &tab, std::vector<char> tape, bool verbose) {
  std::vector<std::string> newtape;
  for(char c : tape) {
    newtape.push_back(std::string(1,c));
  }

  return run(tab, newtape, verbose);
}

bool run(Table &tab, std::string tape, bool verbose) {
  std::vector<std::string> newtape;
  for(char c : tape) {
    newtape.push_back(std::string(1,c));
  }

  return run(tab, newtape, verbose);
}

void readrunFA(int argc, char **argv, bool verbose) {
  // read instructions
  Table tab;
  read(argc, argv, tab);

  // bool verbose = true;

  if(verbose) {
    std::cout << "start " << tab.start << " end ";
    std::cout << tab.final;

    for(Instr &in : tab.instrs) {
      std::cout << in;
    }
  }

  if(argc < 3) {
    usage(argv[0]);
  }

  std::vector<std::string> tape;
  for(int i = 2; i < argc; i++) {
    tape.push_back(argv[i]);
  }

  bool accept = run(tab, tape, verbose);

  if(accept) {
    std::cout << "accepted\n";
  } else {
    std::cout << "rejected\n";
  }
}

int main(int argc, char **argv)
{
  Regex *r = cat("hello");
  Table *tab = r2fa(*r, 0);
  std::cout << *tab;
  
  std::string str;
  if(argc == 1) {
    str = "";
  }
  else if(argc == 2) {
    str = argv[1];
  }
  else {
    std::cerr << "usage: " << argv[0] << " TAPE\n";
  }
  
  bool accept = run(*tab, str, false);
  std::cout << (accept ? "ACCEPT" : "REJECT") << std::endl;

  tab2dot(std::cout, *tab);

  delete tab;
  delete r;
}
