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