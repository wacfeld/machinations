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

int main(int argc, char **argv)
{
  std::vector<Instr> instrs;
  read(argc, argv, instrs);
}
