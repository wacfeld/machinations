#include "instr.h"
#include <stdlib.h>
#include <sstream>

std::ostream &operator<<(std::ostream &out, Instr &in) {
  out << in.src << " ";
  
  if(in.scan == "") {
    out << "EPS";
  } else {
    out << in.scan;
  }
  
  for(int d : in.dests) {
    out << " " << d;
  }

  // if(in.scan == "") {
  //   out << " (epsilon)";
  // }

  out << std::endl;
  return out;
}

void complain(std::string line) {
  std::cerr << line << std::endl;
  std::cerr << "bad" << std::endl;
}

void read_inst(std::string &line, Instr &inst) {
  // std::string line;
  // getline(in, line);

  std::istringstream iss{line};

  if(!(iss >> inst.src >> inst.scan)) {
    complain(line);
    exit(1);
  }

  if(inst.scan == "EPS") {
    inst.scan = "";
  }
  
  int d;
  while(iss >> d) {
    inst.dests.push_back(d);
  }

  // test for trailing characters
  std::string temp;
  iss.clear();
  iss >> temp;
  if(temp != "") {

    // if(temp == "P") { // print transition
    //   inst.print = true;
    // }

    // else {
      complain(line);
      exit(1);
    // }
  }
}
