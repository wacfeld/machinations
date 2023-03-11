#ifndef TAPE_H
#define TAPE_H

#include <iostream>
#include <string>

class Tape {
  
  const int blank; // what symbol is blank (what tape is initialized to)
  int pos; // position along tape
  int size; // size of tape
  int *data; // tape
  
public:

  Tape(int b); // construct with blank
  Tape(int b, std::string init); // construct with blank and initial values
  ~Tape();
  
  // movement
  void right();
  void left();
  
  // read/write
  int get();
  void set(int s);
  
  friend std::ostream &operator<<(std::ostream &out, Tape &t);
};

std::ostream &operator<<(std::ostream &out, Tape &t);

#endif
