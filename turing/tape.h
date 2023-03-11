#ifndef TAPE_H
#define TAPE_H

#include <iostream>
#include <string>
#include <vector>

class Tape {
  
  const std::string blank; // what symbol is blank (what tape is initialized to)
  int pos; // position along tape
  int size; // size of tape
  std::string *data; // tape
  
public:

  Tape(std::string b); // construct with blank
  Tape(std::string b, std::vector<std::string> init); // construct with blank and initial values
  ~Tape();
  
  // movement
  void right();
  void left();
  
  // read/write
  std::string get();
  void set(std::string s);
  
  friend std::ostream &operator<<(std::ostream &out, Tape &t);
};

std::ostream &operator<<(std::ostream &out, Tape &t);

#endif
