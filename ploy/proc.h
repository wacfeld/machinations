#ifndef PROC_H
#define PROC_H

#include <map>
#include <string>

#include "sexp.h"

class Proc {
public:
  
};

extern std::map<std::string, Sexp*> bindings;
void bind(std::string name, Sexp *e);

#endif
