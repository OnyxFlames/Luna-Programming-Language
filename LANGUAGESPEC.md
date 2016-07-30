## Legend
< > denotes mandatory
( ) denotes optional

## Variable Declaration
var <variable-name> (= value | expr) <;>
gbl <variable-name> <= value | expr> <;>

## If Declaration
if <expr> 
<{>
<statement-body>
<}>
#### If statements also have else conditionals
if <expr> 
<{>
<statement-body> <;>
<}>
else <{>
(else-body)
<}>

##### else if's can be chained infinitely.

## Function Declaration
def <function-name> <(>(args ...)<)> 
<{>
<function-body>
<}>

### Function calls
How to call a Luna function:
```lua
functionname("this-is-an-arg-string");
```

## Loops

Luna has two types of loops, ```for```, and ```while```

### While loop declaration

while<(><expr><)>
<{>
<while-body>
<}>

### For loop declaration

for <(><variable-declaration>, <conditional-statement>, <increment><)>
<{>
<for-body>
<}>