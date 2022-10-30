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

- Can't go further than the start screen in terminology.
- Remove borders, use different backgrounds instead (?)
	- Sure... How would this even go???
	- What if... the boards don't have a size?? Nah, we can still have a VERY large terminal.
	- background should be black, that's for sure. Maybe dark blue for the outer part?
	- Or maybe borders show only on non-standard sizes?
- The whole size thing... We cannot represent anything larger than the min size, so maybe we scrap that?? 
	- I say we scrap it, 80x25 and that's it, this makes the border problem dissapear.
- Add an ASCII table in the help
	- or maybe it is its own controller?
- Hide the cursor, show it when needed
	- there is a call to do this, but it does not seem to do anything.
- Clear the stdin when done.
- Copy data files on build

- Normalize board format as far as files are concerned (perhaps board first, info later????).
	- board first, sure... how do we signal the metadata?? some string or just anything beyond the 25st line.
	- but this would break with non-standard board sizes...
- board info: name, intended output, starting stack values, author
- Normalize puzzle set structure (a directory with a set.dat file with info and the boards listed).
	- author
	- comments
	- board list

