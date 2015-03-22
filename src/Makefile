BINDIR=bin
OBJDIR=obj

BINNAME=ninetales
BIN=$(BINDIR)/$(BINNAME)
CLEAN=clean

DIR="./"

GPP=g++
CFLAGS=-Wall -Wextra -Wmissing-braces -pedantic -Wunused
INCLUDE=-I"./"


CPPFILES=main.cpp

OBJ=$(CPPFILES:.cpp=.o)
OBJS=$(addprefix $(OBJDIR)/,$(OBJ))

FLAGS=-O2
DEBUGFLAGS=-g3 -gdwarf-2 -g -DDEBUG

LIBS=

all: executable

debug: FLAGS += $(DEBUGFLAGS)
debug: executable

executable: $(OBJS)
	$(GPP) $(CFLAGS) $(FLAGS) -o $(BIN) $(OBJS) $(LIBS)

$(CLEAN):
	rm -f $(OBJS) $(BIN)

$(OBJDIR)/%.o: %.cpp
	$(GPP) $(CFLAGS) $(FLAGS) $(INCLUDE) -c -o $@ $<

