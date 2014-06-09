#==============================================================================
#D makes all of the .cpp files into .exe files using g++
#==============================================================================

CC = cl
EXT = cpp
CC_OPTS = /EHsc /Z7 /nologo
OBJECTS = *.obj
TO_TEST = MemoryLeakDetector.exe

EXE_DIR = exe
OBJ_DIR = obj

#==============================================================================
#D Makes all of the $(EXT) files into exe files using $(CC)
#D Requires: $(EXT), $(CC) and $(CC_OPTS) to be defined.
#------------------------------------------------------------------------------

SOURCE = $(shell find -name "*.$(EXT)" | sed -e 's/\.$(EXT)/\.exe/' -e 's:\./:$(EXE_DIR)/:')

OS = $(shell uname -o)

ifeq ($(OS), GNU/Linux)
  CC_ESCAPE = -
endif
ifeq ($(OS), Cygwin)
  CC_ESCAPE = /
endif

# common commands
REMOVE_OBJECTS = @rm -fr obj exe
REMOVE_TEMP_FILES = @rm -f *.stackdump *~ \#*\# 

#==============================================================================
#D Target depending on all .exe files made from a .hs file so that all of them 
#D will be made.
#------------------------------------------------------------------------------
all: $(SOURCE)
	@echo "make: \`all' is up to date."
	@echo ""

#==============================================================================
# Rules/Dependencies (all generic)
#------------------------------------------------------------------------------

#==============================================================================
#D Build the executables from each .obj file
#------------------------------------------------------------------------------
$(EXE_DIR)/%.exe: $(OBJ_DIR)/%.obj
	@mkdir -p $(EXE_DIR)
	$(CC) $(CC_OPTS) /Fe$@ $< 
	@echo ""

#==============================================================================
#D Build the objects from each .$(EXT) file
#------------------------------------------------------------------------------
$(OBJ_DIR)/%.obj: %.$(EXT)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CC_OPTS) /c /Fo$@ $< 
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
	@rm -f *.exe *.ilk *.suo *.pdb
	@echo "Removed all: objects, executables, and temp files."

#==============================================================================
#D Pseudo target causes all targets that depend on FRC to be remade even in 
#D case a file with the name of the target exists. Works unless there is a file
#D called FRC in the directory.
#------------------------------------------------------------------------------
FRC:
