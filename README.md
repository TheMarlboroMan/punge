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

- Maybe add a top bar always, with the title???
- A display interface should hold how many columns and rows can it fit...
	To avoid breaking containing rules, maybe it is a property of the driver
	that passes a reference along to whoever needs it.
- In the help controller, tabs should be interpreted as N spaces for the 
	purposes of the formatter.
- What should be printed out if there's nothing on the stack???
- Experiment with getch alternatives...
- Finish the interpreter with the missing commands. I am only missing the input stuff.
- Hide the cursor, show it when needed.
- Clear the stdin when done.
- Copy data files on build

- Normalize board format as far as files are concerned (perhaps board first, info later????).
- Normalize puzzle set structure (a directory with a set.dat file with info and the boards listed).

