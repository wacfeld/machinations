#include <stdlib.h>

#include "regex.h"

std::vector<Regex *> regs;

Regex::Regex(rtype type, std::vector<Regex *> children, std::string lit):
  type{type}, children{children}, lit{lit}
{
  regs.push_back(this);
  // std::cout << "deleting reg\n";
}

void cleanup() {
  // std::cerr << "deleting " << regs.size() << " regexes\n";
  for(Regex *r : regs) {
    delete r;
  }

  regs = {};
}

Table *r2fa(Regex &reg) {
  return r2fa(reg, 0);
}

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

    Table *t = r2fa(*reg.children[0], minstate);
    tab->add({tab->start, "", {t->start}});
    tab->add(t);
    tab->add({t->final[0], "", {t->start}});
    minstate  = t->final[0] + 1;
    tab->add({t->start, "", {minstate}});
    tab->final = {minstate};
    minstate++;
    delete t;

    return tab;
  }
  
  else {
    std::cerr << "unrecognized rtype " << reg.type << std::endl;
    exit(1);
  }
}

std::set<int> eps_closure(std::set<int> states, Table &tab) {
  
  std::set<int> new_states;
  do {
    // populate new_states
    new_states = {};
    
    for(int s : states) {
      for(Instr &in : tab.instrs) {
        if(in.scan == "" && in.src == s) {
          for(int d : in.dests) {
            if(!states.count(d)) {
              new_states.insert(d);
            }
          }
        }
      }
    }

    // union new_states with states
    for(int s : new_states) {
      states.insert(s);
    }
    
  } while(!new_states.empty());

  return states;
}

std::set<int> transition(std::set<int> states, std::string symbol, Table &tab) {
  
  std::set<int> dests;
  
  // follow all state transitions for given symbol
  for(Instr &in : tab.instrs) {
    if(states.count(in.src) && in.scan == symbol) {
      for(int d : in.dests) {
        dests.insert(d);
      }
    }
  }

  dests = eps_closure(dests, tab);
  return dests;
}

// returns true if accepted
bool run(Table &tab, std::vector<std::string> tape, bool verbose) {
  std::set<int> states{tab.start};
  states = eps_closure(states, tab);
  
  if(verbose) {
    std::cerr << "starting states ";
    std::cerr << states;
  }

  for(std::string s : tape) {
    states = transition(states, s, tab);
    // for(int s : states) {
    //   std::cout << s << " ";
    // }
    // std::cout << std::endl;
    if(verbose) {
      std::cerr << states;
    }
  }

  bool accept = false;
  for(int f : tab.final) {
    if(states.count(f)) {
      accept = true;
    }
  }

  return accept;
}

bool run(Table &tab, std::vector<char> tape, bool verbose) {
  std::vector<std::string> newtape;
  for(char c : tape) {
    newtape.push_back(std::string(1,c));
  }

  return run(tab, newtape, verbose);
}

bool match(Table &tab, std::string tape) {
  std::vector<std::string> newtape;
  for(char c : tape) {
    newtape.push_back(std::string(1,c));
  }

  return run(tab, newtape, false);
}

Regex *star(Regex *r) {
  return new Regex {STAR, {r}, ""};
}

Regex *plus(Regex *r) {
  return cat(RV {r, star(r)});
}

Regex *quest(Regex *r) {
  return alt(RV {cat(RV {}), r});
}

Regex *quest(char c) {
  return quest(lit(c));
}

Regex *alt(std::vector<Regex *> rv) {
  return new Regex{ALT, rv, ""};
}

Regex *alt(std::string s) {
  std::vector<Regex *> rv;
  for(char c : s) {
    rv.push_back(lit(c));
  }

  return alt(rv);
}

Regex *cat(std::vector<Regex *> rv) {
  return new Regex{CAT, rv, ""};
}

Regex *cat(std::string s) {
  std::vector<Regex *> rv;
  for(char c : s) {
    rv.push_back(lit(c));
  }

  return cat(rv);
}

Regex *lit(char c) {
  return new Regex{LIT, {}, std::string(1,c)};
}


