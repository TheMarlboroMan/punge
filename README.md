# punge

An idea of a puzzle game based in the Befunge language.

## Building

You will need the libraries from the following projects of mine:

- tools
- terminal-tools
- log
- utf8-tools

Then just do the cmake dance.

## TODO and routemap

- Read metadata, put it in the board.
- Make sure exit checks the output and declares a status!!
- Background for bottom line too.
- Add an ASCII table in the help
	- or maybe it is its own controller?
- Hide the cursor, show it when needed
	- there is a call to do this, but it does not seem to do anything.
- Clear the stdin when done.
- Copy data files on build

- Normalize board format as far as files are concerned (perhaps board first, info later????).
	- board first, sure... how do we signal the metadata?? some string or just anything beyond the 25st line.
	- metadata could be signales from the 26 line, as pairs of key:value, one in each line
- board info: name, intended output, starting stack values, author
- Normalize puzzle set structure (a directory with a set.dat file with info and the boards listed).
	- author
	- comments
	- board list

## Bugs and FIXME
- Board centering is irregular at best
	- Actually, the board is centered... it's the border what is not!!
	- Oh well... let it be??
- It says ?25h at the end...
