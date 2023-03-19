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

void readrunFA(int argc, char **argv, bool verbose) {
  // read instructions
  Table tab;
  read(argc, argv, tab);

  // bool verbose = true;

  if(verbose) {
    std::cerr << "start " << tab.start << " end ";
    std::cerr << tab.final;

    for(Instr &in : tab.instrs) {
      std::cerr << in;
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
    std::cerr << "accepted\n";
  } else {
    std::cerr << "rejected\n";
  }
}


int main(int argc, char **argv)
{
  // Regex *r = cat("hello");
  Regex *num = alt("0123456789");
  // Regex *lower = alt("abc");
  // Regex *upper = alt("ABC");
  // Regex *alpha = alt(std::vector<Regex *>{lower, upper});

  Regex *number = plus(num);
  Regex *NUMBER = cat(RV {quest('-'), number});

  // Regex *username = cat({alpha, star(alpha), num, star(num)});
  
  Table *tab = r2fa(*NUMBER, 0);
  
  // std::cerr << *tab;
  
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
  
  bool accept = match(*tab, str);
  std::cerr << (accept ? "ACCEPT" : "REJECT") << std::endl;

  // tab2dot(std::cout, *tab);

  delete tab;
  // delete r;
}
