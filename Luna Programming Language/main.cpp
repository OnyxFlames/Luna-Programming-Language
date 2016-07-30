#include <iostream>
#include <string>
#include <vector>

#include "token.hpp"
#include "lexer.hpp"
#include "arguments.hpp"

#include "debug.hpp"

extern "C"
{
	#include "lua/lua.h"
	#include "lua/lauxlib.h"
	#include "lua/lualib.h"
}

// flags
bool debug = false;
bool help = false;
bool l_dump = false;
bool p_dump = false;
bool output_file = false;
std::string output_file_name = "";

std::vector<std::string> input_files;

//token_vector is a global so we can use the "-l--dump" flag with ease.
std::vector<token> token_vector;

int main(int argc, char* argv[])
{
	if (argc < 2)
		print_usage();
	else
		handle_args(argc, argv);
	if (help) print_help();

	/* This wont be used until we start testing code generation.
	lua_State *L = luaL_newstate(); 
	luaL_openlibs(L); 
	luaL_dostring(L, "io.write(\"Hello world!\")");*/

	Lexer lexer(token_vector);
	for (auto &it : input_files)
	{
		lexer.load_file(it);
		lexer.lex();
	}

	if (l_dump) dump_lex(token_vector);
	if (p_dump) dump_parse(/*expressions*/);	// no implementation yet.
	if (output_file) gen_output(/*output*/);	// no implementation yet

	debug_prompt();
	return 0;
}