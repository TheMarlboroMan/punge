all: main.cpp
	g++ -g main.cpp ../terminal-tools/obj/terminaltools.o -I../terminal-tools/src/ --std=c++11
