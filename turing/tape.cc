#include "tape.h"

Tape::Tape(int b): blank{b}, pos{0}, size{1} {
  data = new int[1];
  data[0] = blank;
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
      std::cout << '[' << t.data[i] << ']';
    } else {
      std::cout << ' ' << t.data[i] << ' ';
    }
  }

  std::cout << std::endl;
  return out;
}

