#pragma once

#include <string>
#include <array>

struct token;

token create_token(std::string _val, int _start, int _end, short _tokentype);
std::string enum_to_string(short token_type);
bool is_operator(const std::string &val);
short get_operator(const std::string &val);
bool is_half_operator(int val);
bool does_make_operator(int val1, int val2);

static std::array<std::string, 9> keywords = {
	"var",
	"gbl",
	"if",
	"else",
	"def",
	"for",
	"while",
	"true",
	"false",
};


enum token_Type {
	Identifer = 1,
	StringLiteral,
	CharacterLiteral,
	IntegerLiteral,
	FloatLiteral,
	Keyword,

	op_divide,
	op_multiply,
	op_add,
	op_subtract,
	op_equals,
	op_isequal,
	op_isnotequal,
	op_leftbracket,
	op_rightbracket,
	op_increment,
	op_decrement,
	op_leftparan,
	op_rightparan,
	op_semicolon,
	op_leftbrace,
	op_rightbrace,
	op_not,
};

static std::array<std::string, 24> token_Type_strings =
{
	"MISSINGNO",
	"Identifer",
	"StringLiteral",
	"CharacterLiteral",
	"IntegerLiteral",
	"FloatLiteral",
	"Keyword",

	"op_divide",
	"op_multiply",
	"op_add",
	"op_subtract",
	"op_equals",
	"op_isequal",
	"op_isnotequal",
	"op_leftbracket",
	"op_rightbracket",
	"op_increment",
	"op_decrement",
	"op_leftparan",
	"op_rightparan",
	"op_semicolon",
	"op_leftbrace",
	"op_rightbrace",
	"op_not",
};

struct token
{
	std::string val;
	int start;
	int end;
	short token_type;
};