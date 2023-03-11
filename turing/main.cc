#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <ctype.h>
#include <vector>

#include "tape.h"
#include "instr.h"
#include "table.h"

#define R true
#define L false

// run turing machine from given state, with given tape and instruction table
// stops if table is at a loss or reaches end state
// returns ending state (in case it ends prematurely)
int run(int state, Tape &tape, Table &table, int end) {
  do {
    
    Instr *in = table.lookup(state, tape.get());
    
    if(in) { // follow instruction
      tape.set(in->print);
      
      if(in->right)
        tape.right();
      else
        tape.left();

      if(state == 9 && in->dest == 1) {
        std::cout << state << " --- " << tape;
      }
      state = in->dest;
    }

    else { // table is at a loss
      return state;
    }
    
  } while(state != end);

  return state;
}

void complain(int lnum) {
  std::cerr << "line " << lnum << " badly formatted\n";
  std::cerr << "format: INT STR STR BOOL INT\n";
}

Instr line2instr(std::string line, int lnum) {
  Instr in;
  std::istringstream iss{line};
    
  // src, scan, print
  if(!(iss >> in.src >> in.scan >> in.print)) {
    complain(lnum);
    exit(1);
  }

  // dir
  std::string LR; // "L" or "R"
  if(!(iss >> LR)) {
    complain(lnum);
    exit(1);
  }
  if((LR != "L") && (LR != "R")) {
    complain(lnum);
    exit(1);
  }
  in.right = (LR == "R");

  // dest
  if(!(iss >> in.dest)) {
    complain(lnum);
    exit(1);
  }

  // test for trailing characters
  std::string temp;
  if(iss >> temp) {
    complain(lnum);
    exit(1);
  }

  return in;
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

// read start state, end state, blank symbol into table
void read_header(std::string line, int lnum, Table &t) {
  std::istringstream iss{line};
  if(!(iss >> t.start >> t.end >> t.blank)) {
    std::cerr << "header (line " << lnum << "): INT INT STR\n";
    exit(1);
  }
}

void read(int argc, char **argv, Table &t) {
  // check arg count
  if(argc < 2) {
    std::cerr << "usage: " << argv[0] << " INSTRUCTIONS\n";
    exit(1);
  }

  // read from file
  std::ifstream ifs{argv[1]};
  int lnum = 0;
  std::string line;

  bool firstline = true;
  
  while(getline(ifs, line)) {
    lnum++;
    
    // ignore if comment or all whitespace
    if(!isvalid(line))
      continue;

    // first valid line must be header
    if(firstline) {
      firstline = false;
      read_header(line, lnum, t);
      continue;
    }

    Instr in = line2instr(line, lnum); // get instruction from line

    // try to add to table
    int success = t.add(in.src, in.scan, in.print, in.right, in.dest);
    if(!success) {
      std::cerr << "skipping line " << lnum << " (collision)\n";
    }
  }
}

int main(int argc, char **argv)
{

  Table table;

  // read instructions from argv[1]
  read(argc, argv, table);
  std::cerr << "starting state " << table.start << std::endl;
  std::cerr << "ending state " << table.end << std::endl;
  std::cerr << "blank " << table.blank << std::endl;

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
  std::cout << state << " --- " << tape;
  state = run(state, tape, table, table.end);
  std::cout << state << " --- " << tape;
}
