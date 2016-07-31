#include "lexer.hpp"

#include "debug.hpp"

#include <cctype>

extern bool debug;

Lexer::Lexer(std::vector<token> &_tokens)
{
	tokens = &_tokens;
}

Lexer::Lexer(const std::string &file_name, std::vector<token> &_tokens)
{
	load_file(file_name);
	tokens = &_tokens;
}
bool Lexer::lex()
{
	if (!input.is_open())
	{
		std::cerr << "Error running Lexer::lex()! No file opened for instance. Call Lexer::load_file() successfully before calling Lexer::lex().\n";
		return false;
	}
	std::string buffer;
	int token_start = 0;
	int token_end = 0;
	int val = input.get();
	while (!input.eof())
	{
		buffer = "";
		if (std::isalpha(val))
		{
			// only start filling the buffer if the character is alphabetic, not alphanumeric.
			buffer += val;
			token_start = (int)input.tellg();
			val = input.get();
			while (std::isalnum(val))
			{
				// now we can fill the buffer with alphanumeric values
				buffer += val;
				if (debug)
					std::cout << "[Debug] Lexer::lex() buffer contains: " << buffer << "\n";
				val = input.get();
			}
			if (input.eof())
				token_end = (token_start + buffer.size());
			else 
				token_end = (int)input.tellg();
			handle_identifier(buffer, token_start, token_end);
		}
		else if (std::isspace(val))
		{
			while (std::isspace(val))
				val = input.get();
		}
		else if (std::ispunct(val))
		{
			if (val == '\"')
			{
				token_start = (int)input.tellg();
				handle_string_literal(token_start);
				val = input.get();
				continue;
			}

			while (std::ispunct(val))
			{
				token_start = (int)input.tellg();
				if (does_make_operator(val, input.peek()))
				{
					buffer += val;
					val = input.get();
					buffer += val;
				}
				// Peek for double-charactered operators
				// Move this to the store_binop() section, putting each double-charactered operator underneath their single equalivalents (if available)
				if (is_operator(buffer))
				{
					switch (get_operator(buffer))
					{
					case 0x00:
						std::cerr << "\"" << buffer << "\" is not an operator! get_operator() returned 0x00. is_operator() failed!\n";
						debug_prompt();
						break;
					case op_increment:
						token_end = (int)input.tellg();
						tokens->push_back(create_token("++", token_start, token_end, op_increment));
						break;
					case op_decrement:
						token_end = (int)input.tellg();
						tokens->push_back(create_token("--", token_start, token_end, op_decrement));
						break;
					case op_isnotequal:
						token_end = (int)input.tellg();
						tokens->push_back(create_token("!=", token_start, token_end, op_isnotequal));
						break;
					case op_isequal:
						token_end = (int)input.tellg();
						tokens->push_back(create_token("==", token_start, token_end, op_isequal));
						break;
					}
					buffer = "";
					val = input.get();
				}
				else
				{
					store_binop(val, token_start);
					val = input.get();
				}
			}
			// next iteration
			val = input.get();
		}
		else
			return false;
	}
	return false; // to stop the compiler from complaining
}

bool Lexer::load_file(const std::string file_name)
{
	if (input.is_open())
		input.close();
	input.open(file_name);
	if (!input.is_open())
	{
		std::cerr << "Error opening \"" << file_name << "\" for reading. Lexer::load_file() failed.\n";
		return false;
	}
	return true;
}
bool Lexer::is_keyword(const std::string &word, std::vector<std::string> word_pool)
{
	for (auto it : word_pool)
	{
		if (it == word)
			return true;
	} 
		return false;
}

void Lexer::store_binop(int val, int _token_start)
{
	int token_end{ 0 };
	if (input.eof())	// if we're at the end of the file, this operator is the very last token. (which is an error, but let the parse handle that)
	{
		token_end = _token_start;
	}
	else
	{
		token_end = (int)input.tellg();
	}
	switch (val)
	{
	case '/':
		tokens->push_back(create_token("/", _token_start, token_end, op_divide));
		break;
	case '*':
		tokens->push_back(create_token("*", _token_start, token_end, op_multiply));
		break;
	case '+':
		tokens->push_back(create_token("+", _token_start, token_end, op_add));
		break;
	case '-':
		tokens->push_back(create_token("-", _token_start, token_end, op_subtract));
		break;
	case '(':
		tokens->push_back(create_token("(", _token_start, token_end, op_leftparan));
		break;
	case ')':
		tokens->push_back(create_token(")", _token_start, token_end, op_rightparan));
		break;
	case '=':
		tokens->push_back(create_token("=", _token_start, token_end, op_equals));
		break;
	case '[':
		tokens->push_back(create_token("[", _token_start, token_end, op_leftbracket));
		break;
	case ']':
		tokens->push_back(create_token("]", _token_start, token_end, op_rightbracket));
		break;
	case ';':
		tokens->push_back(create_token(";", _token_start, token_end, op_semicolon));
		break;
	case '{':
		tokens->push_back(create_token("{", _token_start, token_end, op_leftbrace));
		break;
	case '}':
		tokens->push_back(create_token("}", _token_start, token_end, op_rightbrace));
		break;
	case '!':
		tokens->push_back(create_token("!", _token_start, token_end, op_not));
		break;
	default:
		std::cerr << "Error \"" << (char)val << "\" is not a valid BinOp! Lexer::store_binop() failed.\n";
		std::exit(-1);
	}
}

void Lexer::handle_identifier(const std::string val, int start, int end)
{
	if (is_keyword(val, std::vector<std::string>(keywords.data(), keywords.data() + keywords.size())))
	{
		handle_keyword(val, start, end);
	}
	else
	{
		tokens->push_back(create_token(val, start, end, Identifer));
	}
}

void Lexer::handle_keyword(const std::string &val, int start, int end)
{
	if (keyword_to_enum(val) == -1)
	{
		std::cout << "keyword_to_enum() returned -1. Lexer::handle_keyword() was passed invalid data!\n";
		debug_prompt();
	}	
	else
		tokens->push_back(create_token(val, start, end, Keyword));
}

void Lexer::handle_string_literal(int _token_start)
{
	bool escape_found = false;
	int val = 0;
	std::string str_buffer = "\"";	// start the buffer with the quotation.
	while (!input.eof())
	{
		val = input.get();
		if (val == '\\')
		{
			val = input.get();
			switch (val)
			{
			case 'a':
				str_buffer += "\\a";
				escape_found = true;
				break;
			case 'b':
				str_buffer += "\\b";
				escape_found = true;
				break;
			case 'f':
				str_buffer += "\\f";
				escape_found = true;
				break;
			case 'n':
				str_buffer += "\\n";
				escape_found = true;
				break;
			case 'r':
				str_buffer += "\\r";
				escape_found = true;
				break;
			case 't':
				str_buffer += "\\t";
				escape_found = true;
				break;
			case 'v':
				str_buffer += "\\v";
				escape_found = true;
				break;
			case '\\':
				str_buffer += "\\\\";
				escape_found = true;
				break;
			case '"':
				str_buffer += "\\\"";
				escape_found = true;
				break;
			case '\'':
				str_buffer += "\\\'";
				escape_found = true;
				break;
			case '[':
				str_buffer += "\\[";
				escape_found = true;
				break;
			case ']':
				str_buffer += "\\]";
				escape_found = true;
				break;
			default:
				std::cerr << "Error \'\\" << (char)val << "\' is not a valid escape character! Exiting..\n";
				escape_found = true;
				debug_prompt();
				break;
			}
		}
		else
		{
			if (val == '\"')
			{
				if (str_buffer[str_buffer.size()] == '\\')
					std::cerr << "Escape character was missed!";
				else
				{
					str_buffer += (char)val;
					break;
				}
			}
			str_buffer += (char)val;
		}
	}
	// end of loop
	//str_buffer += "\"";									// vvv 'token_end' is the token_start plus the string size.
	tokens->push_back(create_token(str_buffer, _token_start, str_buffer.size(), StringLiteral));
}

Lexer::~Lexer()
{
}
