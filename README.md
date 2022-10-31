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
		- This would surely preserve any "compatibility" with other program files.
	- Center the boards.
		- This should be easy enough.
	- Make sure borders are solid and visible.
		- Easy enough again.
	- How would we mark borders that cannot fit with title and status (24h)
		- This is the stuff of nightmares... I say we use just one border, like
		below and to the right.
	- Same for the w.
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
