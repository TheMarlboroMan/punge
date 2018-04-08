INCLUDES=-I../terminal-tools/src/ -I ../tools/class/ -I ../log/src/
COMPILER=g++
DEBUG=-g
EXTERNAL_DEPS=../terminal-tools/obj/terminaltools.o ../log/obj/log.o
CFLAGS=-Wno-deprecated -Wall -ansi -pedantic -std=c++11 -Wfatal-errors

all: main.cpp
	$(COMPILER) $(DEBUG) main.cpp $(EXTERNAL_DEPS) $(INCLUDES) $(CFLAGS)
