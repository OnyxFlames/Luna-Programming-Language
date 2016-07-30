## Source File
As of now, Luna only supports ASCII source files.


### Character
A character is defined as any value ranged between \000 - \127 treated as a byte.

### Whitespace
Whitespace in Luna is any character with the values of:
* \32
* \9
* \10

### Comments
Comments in Luna are not unfamiliar to Lua's comments
-- this is a line comment
--[[
    This is a multi-line comment
]]--

### Tokens
Now to the actual lexical tokens of Luna:

Identifier          - (a-z/A-Z)

StringLiteral       - any ASCII character(s) enclosed between to parathesis (")

CharacterLiteral    - any ASCII **character** enclosed in single quotation (')

IntegerLiteral      - any numerical value not enclosed in quotation or pre/suffixed with characters

FloatLiteral        - any decimal value (contains a . betweeen values to denote decimal) or suffixed with an 'f'

Keyword             - any exact word from Luna's keyword pool (capitalization matters!)

/

\*

\+

\-

(

)

=

==

!=

[

]

++

--

;

### Keywords
```var```
```gbl```
```if```
```else```
```def```
```for```
```while```
```true```
```false```
