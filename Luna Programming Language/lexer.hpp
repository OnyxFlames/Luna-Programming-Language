#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "token.hpp"

class Lexer
{
private:
	std::ifstream input;
	std::vector<token> *tokens;

	bool is_keyword(const std::string &word, std::vector<std::string> word_pool);
	void handle_identifier(std::string val, int start, int end);
	void handle_keyword(const std::string &val, int start, int end);
	void handle_string_literal(int _token_start);
	void handle_char_literal(int _token_start);
	void store_binop(int val, int _token_start);

public:
	Lexer::Lexer(std::vector<token> &_tokens);
	Lexer(const std::string &file_name, std::vector<token> &_tokens);
	bool load_file(const std::string file_name);
	bool lex();

	~Lexer();
};

