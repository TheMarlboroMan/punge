# punge

An idea of a puzzle game based in the Befunge language.

## Building

You will need the libraries from the following projects of mine:

- tools
- terminal-tools
- log
- utf8-tools

Then just do the cmake dance.

## TODO and FIX.

- Fix the controller interface, it makes no sense that the board is there when
	it should be a property of the controller itself.
- Add help with the instructions list and game instructions.
- What should be printed out if there's nothing on the stack???
- Experiment with getch alternatives...
- Finish the interpreter with the missing commands. I am only missing the input stuff.
- Hide the cursor, show it when needed.
- Clear the stdin when done.

- Normalize board format as far as files are concerned (perhaps board first, info later????).
- Normalize puzzle set structure (a directory with a set.dat file with info and the boards listed).

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
