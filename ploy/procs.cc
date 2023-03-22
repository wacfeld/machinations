#include "procs.h"
#include "lexer.h"

void defaults()
{
  bind("length", list_len);
}

// get length of list
int list_len(Sexp *e)
{
  if(e->atom) {
    std::cerr << "cannot get length of non-list\n";
    exit(1);
  }
  
  else if(e == the_empty_list) {
    return 0;
  }
  
  else {
    return 1 + list_len(e->cdr);
  }
}
