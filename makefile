INCLUDES=-I../terminal-tools/src/ -I ../tools/class/ -I ../log/src/ -I ../utf8-tools/src/
COMPILER=g++
DEBUG=-g
EXTERNAL_DEPS=../terminal-tools/obj/terminal_in.o ../terminal-tools/obj/terminal_out.o ../log/obj/log.o ../utf8-tools/obj/utf8-tools.o
CFLAGS=-Wno-deprecated -Wall -ansi -pedantic -std=c++11 -Wfatal-errors

all: main.cpp
	$(COMPILER) $(DEBUG) main.cpp $(EXTERNAL_DEPS) $(INCLUDES) $(CFLAGS)
