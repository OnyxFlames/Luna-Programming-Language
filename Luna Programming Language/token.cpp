#include "token.hpp"

token create_token(std::string _val, int _start, int _end, short _tokentype)
{
	token ret;
	ret.val = _val;
	ret.start = _start;
	ret.end = _end;
	ret.token_type = _tokentype;
	return ret;
}
short keyword_to_enum(const std::string keyword)
{
	if (keyword == "var")
		return _var;
	else if (keyword == "gbl")
		return _gbl;
	else if (keyword == "if")
		return _if;
	else if (keyword == "else")
		return _else;
	else if (keyword == "def")
		return _def;
	else if (keyword == "for")
		return _for;
	else if (keyword == "while")
		return _while;
	else if (keyword == "true")
		return _true;
	else if (keyword == "false")
		return _false;
	else
		return -1;
}

std::string enum_to_string(short token_type)
{
	return token_Type_strings[token_type];
}

bool is_operator(const std::string &val)
{
	if (
		val == "++" ||
		val == "--" ||
		val == "!=" ||
		val == "==")
		return true;
	else
		return false;
}
bool is_half_operator(int val)
{
	if (val == '+' ||
		val == '-' ||
		val == '!' ||
		val == '=')
		return true;
	return false;
}

bool does_make_operator(int val1, int val2)
{
	if (val1 == '+' && val2 == '+')
		return true;
	else if (val1 == '-' && val2 == '-')
		return true;
	else if (val1 == '!' && val2 == '=')
		return true;
	else if (val1 == '=' && val2 == '=')
		return true;
	else 
		return false;
}

short get_operator(const std::string &val)
{
	if (val == "++")
		return op_increment;
	else if (val == "--")
		return op_decrement;
	else if (val == "!=")
		return op_isnotequal;
	else if (val == "==")
		return op_isequal;
	else
		return 0x00;
}