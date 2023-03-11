#include "tape.h"

Tape::Tape(int b): blank{b}, pos{0}, size{1} {
  data = new int[size];
  data[0] = blank;
}

// recommended to make b a printable character so that init can contain it
Tape::Tape(int b, std::string init): blank{b}, pos{0} {
  size = init.length();
  data = new int[size];

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
    int *d = new int[size*2];
    
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
    int *d = new int[size*2];
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

int Tape::get() {
  return data[pos];
}

void Tape::set(int s) {
  data[pos] = s;
}

std::ostream &operator<<(std::ostream &out, Tape &t) {
  for(int i = 0; i < t.size; i++)
  {
    if(i == t.pos) {
      std::cout << '[' << (char) t.data[i] << ']';
    } else {
      std::cout << ' ' << (char) t.data[i] << ' ';
    }
  }

  std::cout << std::endl;
  return out;
}

