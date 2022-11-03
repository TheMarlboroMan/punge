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

- Load available input somewhere, the driver for now.
- Where do we draw the available input??? I guess we could add it in the lower line of edit mode and pray its long enough xD
	- TODO: How do we know we can RETRIEVE a tile the player placed?
	- I guess we keep track of them and paint them in a different color...
	- TODO: What happens when the player RETRIEVES a tile that was FULL? How do we put the tile as it was?	
	- TODO: How do we distingish between NO MORE TILES and no limitations?
- Make the player be able to place the limited tiles. Should actually be easy.
- Make sure exit checks the output and declares a status!!
- Background for bottom line too.
- Add an ASCII table in the help
	- or maybe it is its own controller?
- Hide the cursor, show it when needed
	- there is a call to do this, but it does not seem to do anything.
- Clear the stdin when done.
- Play mode should copy the board from the editor before starting so changes won't bleed back!!!:w

- Normalize puzzle set structure (a directory with a set.dat file with info and the boards listed).
	- author
	- comments
	- board list

## Bugs and FIXME
- Board centering is irregular at best
	- Actually, the board is centered... it's the border what is not!!
	- Oh well... let it be??
- It says ?25h at the end...
