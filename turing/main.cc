#include <iostream>

#include "tape.h"
#include "instr.h"
#include "table.h"

#define R true
#define L false

// run turing machine from given state, with given tape and instruction table
// stops if table is at a loss or reaches end state
// returns ending state (in case it ends prematurely)
int run(int state, Tape &tape, Table &table, int end) {
  do {
    
    Instr *in = table.lookup(state, tape.get());
    
    if(in) { // follow instruction
      tape.set(in->print);
      
      if(in->right)
        tape.right();
      else
        tape.left();

      if(state == 9 && in->dest == 1) {
        std::cout << state << " --- " << tape;
      }
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

  const char B = ' ';
  const int H = 100;
  const int start = 1;

  table.add(1, '0', '0', R, 1   );
  table.add(1, 'Y', 'Y', R, 1   );
  table.add(1, '1', 'Y', L, 2   );
  table.add(1, ' ', ' ', L, 4   );

  table.add(2, '0', '0', L, 2   );
  table.add(2, 'Y', 'Y', L, 2   );
  table.add(2, 'F', 'F', L, 2   );
  table.add(2, ' ', 'F', R, 3   );

  table.add(3, 'F', 'F', R, 3   );
  table.add(3, '0', '0', R, 1   );
  table.add(3, 'Y', 'Y', R, 1   );

  table.add(4, '0', '0', L, 4   );
  table.add(4, 'Y', '1', L, 4   );
  table.add(4, ' ', ' ', R, H   );
  table.add(4, 'F', 'F', L, 5   );

  table.add(5, 'F', 'F', L, 5   );
  table.add(5, ' ', ' ', R, 6   );

  table.add(6, 'F', ' ', R, 7   );

  table.add(7, 'X', '0', R, 7   );
  table.add(7, 'Y', '1', R, 7   );
  table.add(7, '1', '0', L, 9   );
  table.add(7, '0', '1', L, 9   );
  table.add(7, 'F', 'F', R, 10  );

  // no state 8

  table.add(9, '0', '0', L, 9   );
  table.add(9, '1', '1', L, 9   );
  table.add(9, ' ', ' ', R, 1   );

  table.add(10, 'Y', 'Y', R, 10 );
  table.add(10, 'X', 'X', R, 10 );
  table.add(10, 'F', 'F', R, 10 );
  table.add(10, '1', 'Y', L, 11 );
  table.add(10, '0', 'X', L, 11 );

  table.add(11, 'X', 'X', L, 11 );
  table.add(11, 'Y', 'Y', L, 11 );
  table.add(11, 'F', 'F', L, 5  );
    
  Tape tape {B, "10110100"};

  int state = start;
  std::cout << state << " --- " << tape;
  state = run(state, tape, table, H);
  std::cout << state << " --- " << tape;
}
