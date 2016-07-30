# Luna
Luna is a proof-of-concept micro-programming language built of top of the Lua virtual machine. The Luna compilation suite is written in C++11, while Lua is written in C99.
# Goal
The end goal for Luna is to have a full compilation suite(lexer, parser, code-generator) to pave way for a more formal, fleshed out, general purpose programming language to be created.
# Use
Luna will be a command-line operated programming language currently only supporting MS Windows.

Usage:
```luna <args>```

For arguments, Luna will take a filename(preferably suffixed with ".luna") or supported flags to change the compilers behavior.
Supported flags:

-help		-- lists all the supported commands and their behavior.

-l--dump	-- dumps all of the parsed tokens into the stdout for debugging purposes.

-p--dump	-- dumps all of the semantic 'phrases' (statements, expressions, function declarations, etc) into the stdout for debugging purposes.

-lua <file>	-- loads a Lua source file into the compiler to be parsed and added onto the Luna source code(functions, variables, etc).

-o <name>	-- outputs the transpiled Lua code from the Luna source file under the filename of <name>.

