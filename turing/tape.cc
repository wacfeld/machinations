#include "tape.h"

Tape::Tape(std::string b): blank{b}, pos{0}, size{1} {
  data = new std::string[size];
  data[0] = blank;
}

// recommended to make b a printable character so that init can contain it
Tape::Tape(std::string b, std::vector<std::string> init): blank{b}, pos{0} {
  size = init.size();
  data = new std::string[size];

  for(int i = 0; i < size; i++)
  {
    data[i] = init[i];
  }
}

Tape::~Tape() {
  delete[] data;
}

void Tape::right() {
  pos++;

  if(size == pos) { // out of bounds
    // expand
    std::string *d = new std::string[size*2];

    // copy over & write blanks
    for(int i = 0; i < size; i++) {
      d[i] = data[i];
      d[i+size] = blank;
    }

    // replace
    delete[] data;
    data = d;
    size *= 2;
  }
}

void Tape::left() {
  pos--;

  if(pos < 0) { // out of bounds
    // expand & shift
    std::string *d = new std::string[size*2];
    pos += size;

    // copy over & write blanks
    for(int i = 0; i < size; i++) {
      d[i+size] = data[i];
      d[i] = blank;
    }

    // replace
    delete[] data;
    data = d;
    size *= 2;
  }
}

std::string Tape::get() {
  return data[pos];
}

void Tape::set(std::string s) {
  data[pos] = s;
}

std::ostream &operator<<(std::ostream &out, Tape &t) {
  bool start = true;
  for(int i = 0; i < t.size; i++)
  {
    // skip leading blanks
    if(t.data[i] == t.blank && start)
      continue;
    else
      start = false;

    std::string symb = (t.data[i] == t.blank) ? " " : t.data[i];

    if(i == t.pos) {
      std::cout << '[' << symb << ']';
    } else {
      std::cout << ' ' << symb << ' ';
    }
  }

  std::cout << std::endl;
  return out;
}

