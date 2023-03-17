#include "io.h"

std::ostream &operator<<(std::ostream &out, std::set<int> S) {
  std::string space = "";
  for(int s : S) {
    out << space << s;
    space = " ";
  }
  out << std::endl;
  return out;
}

std::ostream &operator<<(std::ostream &out, std::vector<int> S) {
  std::string space = "";
  for(int s : S) {
    out << space << s;
    space = " ";
  }
  out << std::endl;
  return out;
}


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

// escape double quotes and backslashes in string
std::string escape(std::string in) {
  std::string out;
  for(char c : in) {
    if(c == '\\' || c == '"') {
      out += '\\';
    }
    out += c;
  }

  return out;
}

void tab2dot(std::ostream &out, Table &tab) {
  // header & footer
  static const std::string header = "digraph G {\ngraph [layout=dot rankdir=LR]\n";
  static const std::string footer = "}\n";
  
  // unicode epsilon
  static const std::string eps = "ε";

  out << header;

  // make nodes circle-shaped by default
  out << "node [shape=circle]\n";
  // make start state box-shaped
  out << tab.start << " [shape=box]\n";
  // make final states double circles
  for(int s : tab.final) {
    out << s << " [shape=doublecircle]\n";
  }

  // draw instructions
  // e.x. 5 -> { 6 7 8 } []
  for(Instr &in : tab.instrs) {
    out << in.src << " -> { ";
    for(int d : in.dests) {
      out << d << ' ';
    }
    out << '}';

    // label
    out << "[label=\"";
    if(in.scan == "") {
      out << eps;
    } else {
      out << escape(in.scan);
    }
    out << "\"];\n";
  }

  out << footer;
}
