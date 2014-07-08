#==============================================================================
#D makes all of the .cpp files into .exe files using g++
#==============================================================================

CC = g++
EXT = cpp
CC_OPTS = -std=c++0x -g -Wall -Werror
OBJECTS = *.o *.obj *.ilk *.pdb *.suo *.stackdump

SIN_BIN = CoercionByMemberTemplate.exe 


TO_TEST =  $(shell grep -l "class *utest_" *.cpp | sed -e 's/\.cpp/\.exe/' $(foreach test, $(SIN_BIN), | grep -v $(test)))
TEST_RESULTS := $(shell \
  echo $(TO_TEST) |\
  sed -e 's: : result/:g' \
      -e 's:^:result/:g' \
      -e 's:\.exe:.test_result:g'\
)

#==============================================================================
#D Makes all of the $(EXT) files into exe files using $(CC)
#D Requires: $(EXT), $(CC) and $(CC_OPTS) to be defined.
#------------------------------------------------------------------------------

EXE_FILES = $(shell ls *.$(EXT) | sed -e 's:^:exe/:' -e 's/\.$(EXT)/\.exe/')

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
all: $(EXE_FILES)
	@echo ""
	@echo "make: \`all' is up to date with" $(shell ./exe/gcc_version.exe)"."
	$(REMOVE_OBJECTS)
	$(REMOVE_TEMP_FILES)
	@echo ""

#==============================================================================
# Rules/Dependencies (all generic)
#------------------------------------------------------------------------------

#==============================================================================
#D Build the executables from each .$(EXT) file
#------------------------------------------------------------------------------
exe/%.exe: %.$(EXT)
	@mkdir -p deps exe
	@echo ""
	$(CC) $(CC_OPTS) -MD -o $@ $<
	@cp exe/$*.d deps/$*.P
	@sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
        -e '/^$$/ d' -e 's/$$/ :/' < exe/$*.d >> deps/$*.P
	@rm -f exe/$*.d

#==============================================================================
.DELETE_ON_ERROR: result/%.test_result

#==============================================================================
result/%.test_result: exe/%.exe
	@mkdir -p result
	@chmod +x $<
	@printf "%-45s" $<:
	@./$< > $@
	@echo -e "\e[0;32m Passed.\e[1;37m"

#==============================================================================
test: $(TEST_RESULTS)
	@echo
	@echo "Finished."

#==============================================================================
retest: FRC
	@rm -fr result
	@make test

#==============================================================================
#D For deleting all temporary and made files
#------------------------------------------------------------------------------
clean: FRC
	$(REMOVE_OBJECTS)
	$(REMOVE_TEMP_FILES)
	@rm -fr exe result
	@echo "Removed all: objects, executables, and temp files."

#==============================================================================
#D Pseudo target causes all targets that depend on FRC to be remade even in 
#D case a file with the name of the target exists. Works unless there is a file
#D called FRC in the directory.
#------------------------------------------------------------------------------
FRC:

-include deps/*.P
