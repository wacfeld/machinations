#ifndef TAPE_H
#define TAPE_H

class tape {
  const int blank; // what symbol is blank (what tape is initialized to)
  int pos;
  
public:
  
  void right();
  void left();
  
  void set(int s);
  int get();
};

#endif
