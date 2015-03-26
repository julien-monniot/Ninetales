

# CONFIGURATION:
#    The project directories:
DIRECTORIES=client/ server/ encryption/ utils/
#    The project cpp files:
CPPFILES=main.cpp client/client.cpp
#    The libraries includes (-I):
LIBS_INCLUDES=
#    The libraries (-L and -l):
LIBS=

# Directories
CURRENT_DIRECTORY=./
SRCDIR=$(CURRENT_DIRECTORY)src/
BINDIR=$(CURRENT_DIRECTORY)src/bin/
OBJDIR=$(CURRENT_DIRECTORY)src/obj/

SRCDIRS=$(DIRECTORIES:%=$(SRCDIR)%)
OBJDIRS=$(DIRECTORIES:%=$(OBJDIR)%)
INCDIRS=$(DIRECTORIES:%=-I"$(CURRENT_DIRECTORY)%") \
	-I"$(CURRENT_DIRECTORY)" $(LIBS_INCLUDES)

# Objects
OBJFILES=$(CPPFILES:%.cpp=$(OBJDIR)%.o)
OBJ_BUILD=$(CPPFILES:%.cpp=$(SRCDIR)%.o)

# Binary informations
BINNAME=ninetales
BIN=$(BINDIR)$(BINNAME)

# Modes
CLEAN_MODE=clean
DEBUG_MODE=debug

# Compiler options
GPP=g++
DEBUGFLAGS=-g3 -gdwarf-2 -g -DDEBUG
CFLAGS=-Wall -Wextra -Wmissing-braces -pedantic -Wunused
FLAGS=-O2

# Rules

all: executable

#    Debug mode
$(DEBUG_MODE): FLAGS += $(DEBUGFLAGS)
$(DEBUG_MODE): executable

#    Default mode
executable: $(OBJ_BUILD)
	$(GPP) $(CFLAGS) $(FLAGS) -o $(BIN) $(OBJFILES) $(LIBS)

#    Clean mode
$(CLEAN_MODE):
	rm -rf $(OBJDIR)

$(SRCDIR)%.o: $(SRCDIR)%.cpp
	$(GPP) $(CFLAGS) $(FLAGS) $(INCDIRS) -c -o $(OBJDIR)$*.o $(SRCDIR)$*.cpp

#    Ensure the presence of the directories
all:
	mkdir -p $(OBJDIRS)
	mkdir -p $(BINDIR)
