#ifndef OUT_H
#define OUT_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ios>
#include "./candidate/candidate.h"
#include "./timer.h"
#include "./state.h"
#include "./problems.h"

void to_file(std::string alg, std::string problem, Candidate& c, Timer& t);

void to_stdout(std::string problem, Candidate& c, Timer& t);

#endif

