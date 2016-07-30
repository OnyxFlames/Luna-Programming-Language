#include "arguments.hpp"
#include "debug.hpp"


#include <cstring>

extern bool debug;
extern bool help;
extern bool l_dump;
extern bool p_dump;
extern bool output_file;
extern std::string output_file_name;
extern std::vector<std::string> input_files;

void handle_args(int argc, char* argv[])
{
	for (int i = 1; i < argc; i++)
	{
		if (std::strcmp("-help", argv[i]) == 0)
			help = true;
		else if (std::strcmp("-l--dump", argv[i]) == 0)
			l_dump = true;
		else if (std::strcmp("-p--dump", argv[i]) == 0)
			p_dump = true;
		else if (std::strcmp("-debug", argv[i]) == 0)
			debug = true;
		else if (std::strcmp("-o", argv[i]) == 0 && i < (argc -1)) // argc needs to have one more argument for -o to work.
		{
			output_file = true;
			output_file_name = argv[i + 1];
			i++;
		}
		else
		{
			input_files.push_back(argv[i]);
		}
	}
}

void print_usage()
{
	std::cout << "Usage: Luna -help\nPress return to continue..\n";
	debug_prompt();
}

void print_help()
{
	std::cout << 
		" -help		-- lists all the supported commands and their behavior.\n"
		" -l--dump	-- dumps all of the parsed tokens into the stdout for debugging purposes.\n"
		" -p--dump	-- dumps all of the semantic 'phrases' (statements, expressions, function declarations, etc) into the stdout for debugging purposes.\n"
		" -lua <file>	-- loads a Lua source file into the compiler to be parsed and added onto the Luna source code(functions, variables, etc).\n"
		" -debug	-- turns on debug messages during compilation phases.\n"
		" -o <name>	-- outputs the transpiled Lua code from the Luna source file under the filename of <name>.\n";
	std::exit(0);
}

void dump_lex(std::vector<token> &_tokens)
{
	for (auto it : _tokens)
	{
		std::cout << "Value:\t" << it.val << "\nStart:\t" << it.start << "\nEnd:\t" << it.end << "\nType:\t" << enum_to_string(it.token_type) << "\n---\n";
	}
}

void dump_parse()
{
	std::cout << "TODO: Implement dump_parse() function.\n";
}

void gen_output()
{
	std::cout << "TODO: Implement gen_ouput() function.\n";
}