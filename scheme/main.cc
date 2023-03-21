#include <iostream>

#include "lexer.h"

int main(int argc, char **argv) {
  std::string s;
  getline(std::cin, s);
  std::cout << longestint(s);
}
