#pragma once

#include <iostream>
#include <vector>

#include "token.hpp"

void handle_args(int argc, char* argv[]);

void print_usage();

void print_help();

void dump_lex(std::vector<token> &_tokens);

void dump_parse();

void gen_output();