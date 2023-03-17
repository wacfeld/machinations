#include <stdlib.h>

#include "regex.h"

// invariant: final has exactly 1 element which is the max state number
Table *r2fa(Regex &reg, int minstate) {
  Table *tab = new Table;
  tab->start = minstate;
  tab->final = {minstate}; // by default this makes the table accept the empty string
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
      delete t;
    }

    return tab;
  }

  else if(reg.type == ALT) {
    std::vector<int> tails;
    for(Regex *r : reg.children) {
      Table *t = r2fa(*r, minstate);
      tab->add({tab->start, "", {t->start}});
      tab->add(t);
      tails.push_back(t->final[0]);
      minstate = t->final[0] + 1;
      delete t;
    }

    tab->final = {minstate};
    minstate++;
    for(int tl : tails) {
      tab->add({tl, "", {tab->final}});
    }

    return tab;
  }

  else if(reg.type == LIT) {
    tab->final = {minstate};
    Instr in {tab->start, reg.lit, {minstate}};
    tab->instrs.push_back(in);
    minstate++;

    return tab;
  }

  else if(reg.type == STAR) { // kleene closure
    if(reg.children.size() != 1) {
      std::cerr << "r2fa(): star regex has multiple children\n";
      exit(1);
    }

    Table *t = r2fa(reg.children[0], minstate);
    tab->add({tab->start, "", {t->start}});
    tab->add(t);
    tab->add({t->final[0], "", {t->start}});
    minstate  = t->final[0] + 1;
    tab->add({t->start, "", {minstate}});
    minstate++;
    delete t;

    return t;
  }
  
  else {
    std::cerr << "unrecognized rtype " << reg.type << std::endl;
    exit(1);
  }
}
