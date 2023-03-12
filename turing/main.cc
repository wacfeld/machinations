#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <ctype.h>
#include <vector>

#include "tape.h"
#include "instr.h"
#include "table.h"
#include "turing.h"

int main(int argc, char **argv)
{

  Table table;

  // read instructions from argv[1]
  read(argc, argv, table);
  // std::cerr << "starting state " << table.start << std::endl;
  // std::cerr << "ending state " << table.end << std::endl;
  // std::cerr << "blank " << table.blank << std::endl;

  std::vector<std::string> init;
  // any remaining args are put onto the tape
  if(argc >= 3) {
    for(int i = 2; i < argc; i++)
    {
      init.push_back(argv[i]);
    }
  } else {
    init.push_back(table.blank);
  }

  Tape tape {table.blank, init};

  int state = table.start;

  std::cout << state << " : " << tape;
  std::cout << "BEGIN\n";

  state = run(state, tape, table, table.end);

  std::cout << "HALT\n";
  std::cout << state << " : " << tape;
}
