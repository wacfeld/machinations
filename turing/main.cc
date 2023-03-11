#include <iostream>

#include "tape.h"
#include "instr.h"
#include "table.h"

// run turing machine from given state, with given tape and instruction table
// stops if table is at a loss or reaches end state
// returns ending state (in case it ends prematurely)
int run(int state, Tape &tape, Table &table, int end) {
  do {
    
    std::cout << (char) state << ' ' << tape;
    Instr *in = table.lookup(state, tape.get());
    
    if(in) { // follow instruction
      tape.set(in->print);
      
      if(in->right)
        tape.right();
      else
        tape.left();

      state = in->dest;
    }

    else { // table is at a loss
      return state;
    }
    
  } while(state != end);

  return state;
}

int main()
{
  Table table;
  table.add('A', '0', '1', true, 'B');
  table.add('A', '1', '1', false, 'B');
  table.add('B', '0', '1', false, 'A');
  table.add('B', '1', '1', true, 'E');
  
  Tape tape {'0'};

  run('A', tape, table, 'E');
  
  std::cout << tape;
}
