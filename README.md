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

- Remove borders, use different backgrounds instead (?)
- Add an ASCII table in the help
	- or maybe it is its own controller?
- What should be printed out if there's nothing on the stack???
	Popping from empty stacks gives out zero.
- Hide the cursor, show it when needed
	- there is a call to do this, but it does not seem to do anything.
- Clear the stdin when done.
- Copy data files on build

- Normalize board format as far as files are concerned (perhaps board first, info later????).
- board info: name, intended output, starting stack values
- Normalize puzzle set structure (a directory with a set.dat file with info and the boards listed).

