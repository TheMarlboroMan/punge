all: main.cpp src/board.h
	g++ main.cpp ../terminal-tools/obj/terminaltools.o -I../terminal-tools/src/ --std=c++11
