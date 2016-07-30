#include "debug.hpp"

#include <iostream>

void debug_prompt()
{
	if (debug)
	{
		std::cout << "[Debug] Press any key to continue..\n";
		getchar();
		std::exit(1);
	}
	std::exit(1);
}