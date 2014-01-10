#==============================================================================
#D makes all of the .cpp files into .exe files using g++
#==============================================================================

CC = g++
EXT = cpp
CC_OPTS = -std=c++0x -g -Wall -Werror
OBJECTS = *.o *.obj *.ilk *.pdb *.suo *.stackdump

TO_TEST = LinkedList.exe PointerOffset.exe ClassToStructCast.exe \
          OddArrayAccess.exe Closure.exe

#==============================================================================
#D Makes all of the $(EXT) files into exe files using $(CC)
#D Requires: $(EXT), $(CC) and $(CC_OPTS) to be defined.
#------------------------------------------------------------------------------

SOURCE = $(shell ls *.$(EXT) | sed -e 's/\.$(EXT)/\.exe/')

OS = $(shell uname -o)

ifeq ($(OS), GNU/Linux)
  CC_ESCAPE = -
endif
ifeq ($(OS), Cygwin)
  CC_ESCAPE = /
endif

# common commands
REMOVE_OBJECTS = @rm -f $(OBJECTS)
REMOVE_TEMP_FILES = @rm -f *~ \#*\#

#==============================================================================
#D Target depending on all .exe files made from a .hs file so that all of them 
#D will be made.
#------------------------------------------------------------------------------
all: $(SOURCE)
	@echo "make: \`all' is up to date."
	$(REMOVE_OBJECTS)
	$(REMOVE_TEMP_FILES)
	@echo ""

#==============================================================================
# Rules/Dependencies (all generic)
#------------------------------------------------------------------------------

#==============================================================================
#D Build the executables from each .$(EXT) file
#------------------------------------------------------------------------------
%.exe: %.$(EXT) UnitTest.h
	$(CC) $(CC_OPTS) -o $@ $<
	@echo ""

#==============================================================================
test: all
	@chmod +x $(TO_TEST)
	$(foreach test, $(TO_TEST), ./$(test);)

#==============================================================================
#D For deleting all temporary and made files
#------------------------------------------------------------------------------
clean: FRC
	$(REMOVE_OBJECTS)
	$(REMOVE_TEMP_FILES)
	@rm -f *.exe
	@echo "Removed all: objects, executables, and temp files."

#==============================================================================
#D Pseudo target causes all targets that depend on FRC to be remade even in 
#D case a file with the name of the target exists. Works unless there is a file
#D called FRC in the directory.
#------------------------------------------------------------------------------
FRC:
