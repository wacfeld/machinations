#ifndef IO_H
#define IO_H

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <set>

#include "instr.h"
#include "table.h"
#include "regex.h"

void usage(std::string exec);
bool isvalid(std::string line);
void read(int argc, char **argv, Table &tab);

#endif
