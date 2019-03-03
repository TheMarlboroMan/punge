INCLUDES=-I../terminal-tools/src/ -I ../tools/class/ -I ../log/src/ -I ../utf8-tools/src/
COMPILER=g++
DEBUG=-g
CFLAGS=-Wno-deprecated -Wall -ansi -pedantic -std=c++11 -Wfatal-errors
LINKER=

DIR_O=objects/
DIR_CLASS_APP=src/app/
DIR_CLASS_INTERPRETER=src/interpreter/

DEPS_EXTERNAL=../terminal-tools/obj/terminal_in.o\
../terminal-tools/obj/terminal_out.o\
../log/objects/log.o\
../log/objects/log_tools.o\
../utf8-tools/obj/utf8-tools.o\

DEPS_INTERPRETER=$(DIR_O)board_loader.o \
$(DIR_O)board.o \
$(DIR_O)tile.o \
$(DIR_O)cursor.o \
$(DIR_O)output.o \
$(DIR_O)register_item.o \
$(DIR_O)stack.o \
$(DIR_O)stack_manipulator.o \
$(DIR_O)parser.o\

DEPS_APP=$(DIR_O)terminal_display.o \
$(DIR_O)terminal_input.o \
$(DIR_O)driver.o \
$(DIR_O)state_play.o \
$(DIR_O)state_edit.o \
$(DIR_O)state_title.o \
$(DIR_O)drawing_routines.o \

#ifndef VERBOSE
#.SILENT:
#endif

all: a.out $(DIR_O)
	echo "Done";

clean:
	if [ -f a.out ]; then rm a.out; fi;
	if [ -d $(DIR_O) ]; then rm $(DIR_O)/*; fi;

a.out:\
$(DIR_O)\
$(DEPS_INTERPRETER)\
$(DEPS_APP)\
$(DEPS_EXTERNAL)\
main.cpp
	$(COMPILER) main.cpp -o a.out $(CFLAGS) $(INCLUDES) $(DEPS_INTERPRETER) $(DEPS_APP) $(DEPS_EXTERNAL) $(LINKER)

$(DIR_O):
	mkdir -p $(DIR_O)

#Interpreter...
$(DIR_O)board_loader.o:\
$(DIR_O)board.o\
$(DIR_CLASS_INTERPRETER)board_loader.cpp \
$(DIR_CLASS_INTERPRETER)board_loader.h
	$(COMPILER) -c $(DIR_CLASS_INTERPRETER)board_loader.cpp $(CFLAGS) $(INCLUDES) -o $(DIR_O)board_loader.o

$(DIR_O)board.o:\
$(DIR_O)tile.o\
$(DIR_CLASS_INTERPRETER)board.cpp \
$(DIR_CLASS_INTERPRETER)board.h
	$(COMPILER) -c $(DIR_CLASS_INTERPRETER)board.cpp $(CFLAGS) $(INCLUDES) -o $(DIR_O)board.o

$(DIR_O)tile.o:\
$(DIR_CLASS_INTERPRETER)tile.cpp \
$(DIR_CLASS_INTERPRETER)tile.h
	$(COMPILER) -c $(DIR_CLASS_INTERPRETER)tile.cpp $(CFLAGS) $(INCLUDES) -o $(DIR_O)tile.o

$(DIR_O)cursor.o:\
$(DIR_CLASS_INTERPRETER)cursor.cpp \
$(DIR_CLASS_INTERPRETER)cursor.h
	$(COMPILER) -c $(DIR_CLASS_INTERPRETER)cursor.cpp $(CFLAGS) $(INCLUDES) -o $(DIR_O)cursor.o

$(DIR_O)output.o:\
$(DIR_CLASS_INTERPRETER)output.cpp \
$(DIR_CLASS_INTERPRETER)output.h
	$(COMPILER) -c $(DIR_CLASS_INTERPRETER)output.cpp $(CFLAGS) $(INCLUDES) -o $(DIR_O)output.o

$(DIR_O)register_item.o:\
$(DIR_CLASS_INTERPRETER)register_item.cpp \
$(DIR_CLASS_INTERPRETER)register_item.h
	$(COMPILER) -c $(DIR_CLASS_INTERPRETER)register_item.cpp $(CFLAGS) $(INCLUDES) -o $(DIR_O)register_item.o

$(DIR_O)stack.o:\
$(DIR_O)register_item.o\
$(DIR_CLASS_INTERPRETER)stack.cpp \
$(DIR_CLASS_INTERPRETER)stack.h
	$(COMPILER) -c $(DIR_CLASS_INTERPRETER)stack.cpp $(CFLAGS) $(INCLUDES) -o $(DIR_O)stack.o

$(DIR_O)stack_manipulator.o:\
$(DIR_O)stack.o\
$(DIR_CLASS_INTERPRETER)stack_manipulator.cpp \
$(DIR_CLASS_INTERPRETER)stack_manipulator.h
	$(COMPILER) -c $(DIR_CLASS_INTERPRETER)stack_manipulator.cpp $(CFLAGS) $(INCLUDES) -o $(DIR_O)stack_manipulator.o

$(DIR_O)parser.o:\
$(DIR_O)board.o\
$(DIR_O)board_loader.o\
$(DIR_O)cursor.o\
$(DIR_O)output.o\
$(DIR_O)stack.o\
$(DIR_O)stack_manipulator.o\
$(DIR_CLASS_INTERPRETER)parser.cpp \
$(DIR_CLASS_INTERPRETER)parser.h
	$(COMPILER) -c $(DIR_CLASS_INTERPRETER)parser.cpp $(CFLAGS) $(INCLUDES) -o $(DIR_O)parser.o

#Application...

$(DIR_O)terminal_display.o:\
$(DEPS_INTERPRETER)\
$(DIR_CLASS_APP)terminal_display.cpp \
$(DIR_CLASS_APP)terminal_display.h \
$(DIR_CLASS_APP)display_interface.h
	$(COMPILER) -c $(DIR_CLASS_APP)terminal_display.cpp $(CFLAGS) $(INCLUDES) -o $(DIR_O)terminal_display.o

$(DIR_O)terminal_input.o:\
$(DEPS_INTERPRETER)\
$(DIR_CLASS_APP)terminal_input.cpp \
$(DIR_CLASS_APP)terminal_input.h \
$(DIR_CLASS_APP)input_interface.h
	$(COMPILER) -c $(DIR_CLASS_APP)terminal_input.cpp $(CFLAGS) $(INCLUDES) -o $(DIR_O)terminal_input.o

$(DIR_O)drawing_routines.o:\
$(DEPS_INTERPRETER)\
$(DIR_CLASS_APP)drawing_routines.cpp \
$(DIR_CLASS_APP)drawing_routines.h
	$(COMPILER) -c $(DIR_CLASS_APP)drawing_routines.cpp $(CFLAGS) $(INCLUDES) -o $(DIR_O)drawing_routines.o

$(DIR_O)state_title.o:\
$(DEPS_INTERPRETER)\
$(DIR_CLASS_APP)state_title.cpp \
$(DIR_CLASS_APP)state_title.h\
$(DIR_CLASS_APP)state_interface.h\
$(DIR_O)drawing_routines.o
	$(COMPILER) -c $(DIR_CLASS_APP)state_title.cpp $(CFLAGS) $(INCLUDES) -o $(DIR_O)state_title.o

$(DIR_O)state_play.o:\
$(DEPS_INTERPRETER)\
$(DIR_CLASS_APP)state_play.cpp \
$(DIR_CLASS_APP)state_play.h\
$(DIR_CLASS_APP)state_interface.h\
$(DIR_O)drawing_routines.o
	$(COMPILER) -c $(DIR_CLASS_APP)state_play.cpp $(CFLAGS) $(INCLUDES) -o $(DIR_O)state_play.o

$(DIR_O)state_edit.o:\
$(DEPS_INTERPRETER)\
$(DIR_CLASS_APP)state_edit.cpp \
$(DIR_CLASS_APP)state_edit.h\
$(DIR_CLASS_APP)state_interface.h\
$(DIR_O)drawing_routines.o
	$(COMPILER) -c $(DIR_CLASS_APP)state_edit.cpp $(CFLAGS) $(INCLUDES) -o $(DIR_O)state_edit.o

$(DIR_O)driver.o:\
$(DIR_O)terminal_display.o\
$(DIR_O)terminal_input.o\
$(DIR_O)state_edit.o\
$(DIR_O)state_play.o\
$(DIR_O)state_title.o\
$(DEPS_INTERPRETER)\
$(DIR_CLASS_APP)driver.cpp \
$(DIR_CLASS_APP)driver.h
	$(COMPILER) -c $(DIR_CLASS_APP)driver.cpp $(CFLAGS) $(INCLUDES) -o $(DIR_O)driver.o
