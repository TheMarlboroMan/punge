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

- There is a problem here with the whole map thing. The parser owns the board,
	and then it should own the metadata too. The parser SEEMS to load the 
	board too, which is... weird. My take is that we should feed the board and
	the extensions to the parser externally with a set_board and set_extensions
	and the parser should make a copy of these. 
- Make sure exit checks the output and declares a status!!
- Background for bottom line too.
- Add an ASCII table in the help
	- or maybe it is its own controller?
- Hide the cursor, show it when needed
	- there is a call to do this, but it does not seem to do anything.
- Clear the stdin when done.
- Copy data files on build

- Normalize puzzle set structure (a directory with a set.dat file with info and the boards listed).
	- author
	- comments
	- board list

## Bugs and FIXME
- Board centering is irregular at best
	- Actually, the board is centered... it's the border what is not!!
	- Oh well... let it be??
- It says ?25h at the end...
