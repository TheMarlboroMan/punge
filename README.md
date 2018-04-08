# punge

An idea of a puzzle game based in the Befunge language.

## Building

You will need to have with the following object files in your system

	- terminaltools.o (located in terminal-tools/obj/ after building my terminal-tools github project).
	- log.o (located in log/obj after building my log github project).

You will need to add the include paths to:

	- number_generator.h (located in class/ in my tools github repo).
	- terminaltools.h (located in class/ in my terminal-tools github repo).
	- log.h (located in class in my log github repo).

Once these paths are sorted out in the makefile, just run "make all".

## TODO:

- Finish the interpreter with the missing commands.
- Hide the cursor and clear the standard input.
- Separate the stack slice... perhaps we can use the stack manipulator for that?

- Normalize board format (perhaps board first, info later????).
- Normalize puzzle set structure.
- Experiment with getch alternatives...

## For my own reference: befunge-93 instruction list

0-9 	Push this number on the stack
+ 	Addition: Pop a and b, then push a+b
- 	Subtraction: Pop a and b, then push b-a
* 	Multiplication: Pop a and b, then push a*b
/ 	Integer division: Pop a and b, then push b/a, rounded towards 0.
% 	Modulo: Pop a and b, then push the remainder of the integer division of b/a.
! 	Logical NOT: Pop a value. If the value is zero, push 1; otherwise, push zero.
` 	Greater than: Pop a and b, then push 1 if b>a, otherwise zero.
> 	Start moving right
< 	Start moving left
^ 	Start moving up
v 	Start moving down
? 	Start moving in a random cardinal direction
_ 	Pop a value; move right if value=0, left otherwise
| 	Pop a value; move down if value=0, up otherwise
" 	Start string mode: push each character's ASCII value all the way up to the next "
: 	Duplicate value on top of the stack
\ 	Swap two values on top of the stack
$ 	Pop value from the stack and discard it
. 	Pop value and output as an integer followed by a space
, 	Pop value and output as ASCII character
# 	Bridge: Skip next cell
p 	A "put" call (a way to store a value for later use). Pop y, x, and v, then change the character at (x,y) in the program to the character with ASCII value v
g 	A "get" call (a way to retrieve data in storage). Pop y and x, then push ASCII value of the character at that position in the program
& 	Ask user for a number and push it
~ 	Ask user for a character and push its ASCII value
@ 	End program
(space) 	No-op. Does nothing
