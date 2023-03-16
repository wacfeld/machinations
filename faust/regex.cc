#include <stdlib.h>

#include "regex.h"

Table *r2fa(Regex &reg, int minstate) {
  Table *tab = new Table;
  tab->start = minstate;
  tab->final = {minstate};
  minstate++;
  
  if(reg.type == CAT) {
    for(Regex *r : reg.children) {
      Table *t = r2fa(*r, minstate);
      
      tab->add({tab->final[0], "", {t->start}});
      
      tab->add(t);
      
      minstate = t->final[0] + 1;
      tab->final = {minstate};
      tab->add({t->final[0], "", {minstate}});
      
      minstate++;
    }

    return tab;
  }

  else if(reg.type == ALT) {
    
  }

  else if(reg.type == LIT) {
    tab->final = {minstate};
    Instr in {tab->start, reg.lit, {minstate}};
    tab->instrs.push_back(in);
    minstate++;

    return tab;
  }

  else if(reg.type == STAR) {
    
  }
  
  else {
    std::cerr << "unrecognized rtype " << reg.type << std::endl;
    exit(1);
  }
}
