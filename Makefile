

# CONFIGURATION:
#    The project directories:
DIRECTORIES=client/ server/ encryption/ utils/
#    The project cpp files:
CPPFILES=main.cpp client/client.cpp utils/printer.cpp utils/utils.cpp
#    The libraries includes (-I):
LIBS_INCLUDES=
#    The libraries (-L and -l):
LIBS=

# Directories
CURRENT_DIRECTORY=./
SRCDIR=$(CURRENT_DIRECTORY)src/
BINDIR=$(CURRENT_DIRECTORY)bin/
OBJDIR=$(CURRENT_DIRECTORY)obj/

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

.PHONY: executable $(DEBUG_MODE) $(CLEAN_MODE) directories

all: executable

#    Debug mode
$(DEBUG_MODE): FLAGS += $(DEBUGFLAGS)
$(DEBUG_MODE): executable

#    Clean mode
$(CLEAN_MODE):
	rm -rf $(OBJDIR)
	
#    Default mode
executable: directories $(OBJ_BUILD)
	@echo -e "\n============================= EDITION DES LIENS ================================\n\n"
	@$(GPP) $(CFLAGS) $(FLAGS) -o $(BIN) $(OBJFILES) $(LIBS)
	@echo -e " ## Edition des liens terminée avec succès !\n"
	@echo -e "\n ####     Exécutable généré : \"$(BIN)\"     #### \n"

#    Ensure the presence of the directories
directories:
	@mkdir -p $(OBJDIRS)
	@mkdir -p $(BINDIR)
	@echo -e "\n================================ COMPILATION ===================================\n"


pre_edl:

post_edl:

$(SRCDIR)%.o: $(SRCDIR)%.cpp
	@echo -e "\n ## Compilation de $*.cpp\n"
	@$(GPP) $(CFLAGS) $(FLAGS) $(INCDIRS) -c -o $(OBJDIR)$*.o $(SRCDIR)$*.cpp
