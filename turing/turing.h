#ifndef TURING_H
#define TURING_H

#include <iostream>
#include <sstream>
#include <fstream>

#include "table.h"
#include "tape.h"
#include "instr.h"

bool is_status(int state, Table &table);
int run(int state, Tape &tape, Table &table, int end);
void complain(std::string line, int lnum);
Instr line2instr(std::string line, int lnum);
bool isvalid(std::string line);
void complain_header(std::string line, int lnum);
void read_header(std::string line, int lnum, Table &t);
void read(int argc, char **argv, Table &t);

#endif
