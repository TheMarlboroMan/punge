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

- If we have different sizes:
	- How do we indicate that a board is of a different size?
		- Metadata after line 25?
	- Who reads the metadata??? the board loader? or a metadata loader?
		- Are these kept in separate entities or we just add default values to them?
	- I say we add the stuff to the map entity to keep the application simple. 
		It will surely not break anything to have empty fields around.
	- If a map has no metadata then we have the slight problem of enlarging it
		to fit into 80x25 cells...
	- Ok, there is some "read board info" and more calls there. I am sure we
		can work something out, like read the metadata in read board info
		for files with more than 25 lines, read the extra metadata and so on.
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
- It says ?25h at the end...
