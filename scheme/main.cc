#include <iostream>

#include "../faust/instr.h"
#include "../faust/table.h"
#include "../faust/regex.h"
#include "../faust/io.h"

#include "lexer.h"

int main(int argc, char **argv) {
  setup();
  if(argc != 2) {
    std::cerr << "please provide argument";
    return 1;
  }
  std::cerr << "classifying";
  ttype type = classify(argv[1]);
  std::cerr << "done!";
  std::cout << type << std::endl;
}
