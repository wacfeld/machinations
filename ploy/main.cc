#include <iostream>
#include <stdlib.h>

#include "lexer.h"

int main(int argc, char **argv) {
  std::string s;
  while(std::cin >> s) {
    Token T;
    int n;
    while((n = nexttoken(s, T)) != 0) {
      std::cout << "  " << T << std::endl;
      s = s.substr(n);
    }

    if(!s.empty()) {
      std::cerr << "no tokens in sight: " << s << std::endl;
      exit(1);
    }
  }
}
