#include "io.h"

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
