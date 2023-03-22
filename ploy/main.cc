#include <iostream>
#include <stdlib.h>

#include "lexer.h"
#include "sexp.h"
#include "io.h"
#include "defaults.h"
#include "repl.h"

int main(int argc, char **argv)
{
  defaults();
  the_empty_list = new Sexp{false};

  repl();
}
