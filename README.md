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

- The stack is signed, 32 bit.
- The cell is unsigned 8 bit.
- What should be printed out if there's nothing on the stack???
	Popping from empty stacks gives out zero.
- Experiment with getch alternatives...
- Finish the interpreter with the missing commands. I am only missing the input stuff.
- Hide the cursor, show it when needed
	- there is a call to do this, but it does not seem to do anything.
- Clear the stdin when done.
- Copy data files on build

- Normalize board format as far as files are concerned (perhaps board first, info later????).
- board info: name, intended output, starting stack values
- Normalize puzzle set structure (a directory with a set.dat file with info and the boards listed).

