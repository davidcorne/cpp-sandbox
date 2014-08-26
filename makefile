#==============================================================================
#D makes all of the .cpp files into .exe files using g++
#==============================================================================

COMPILER_TYPE = gcc
EXE_DIRECTORY = exe.$(COMPILER_TYPE)
EXT = cpp

#==============================================================================
ifeq ($(COMPILER_TYPE), gcc)
  COMPILER = g++
  COMPILER_ARGS = -std=c++0x -g -Wall -Werror -pthread $(shell pkg-config --cflags-only-I unitcpp)
  OUT_OBJECT_FILE = -o
  OUT_EXE_FILE = -o
  NO_LINK = -c
endif

#==============================================================================
ifeq ($(COMPILER_TYPE), clang)
  COMPILER = clang++
  COMPILER_ARGS = -std=c++11 -g -Wall -Werror -pthread $(shell pkg-config --cflags-only-I unitcpp)
  OUT_OBJECT_FILE = -o
  OUT_EXE_FILE = -o
  NO_LINK = -c
endif

SIN_BIN = CoercionByMemberTemplate.exe 


TO_TEST =  $(shell grep -l "\(class *utest_\)\|\(<UnitCpp\)" *.cpp | \
             sed -e 's/\.cpp/\.exe/' \
             $(foreach test, $(SIN_BIN), | grep -v $(test)) \
           )

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

EXE_FILES = $(shell ls *.$(EXT) | sed -e 's:^:$(EXE_DIRECTORY)/:' -e 's/\.$(EXT)/\.exe/')

OS = $(shell uname -o)

ifeq ($(OS), GNU/Linux)
  CC_ESCAPE = -
endif
ifeq ($(OS), Cygwin)
  CC_ESCAPE = /
endif

#==============================================================================
#D Target depending on all .exe files made from a .hs file so that all of them 
#D will be made.
#------------------------------------------------------------------------------
all: $(EXE_FILES)
	@echo ""
	@echo "make: \`all' is up to date with" $(shell ./$(EXE_DIRECTORY)/gcc_version.exe)"."
	$(REMOVE_OBJECTS)
	$(REMOVE_TEMP_FILES)
	@echo ""

#==============================================================================
# Rules/Dependencies (all generic)
#------------------------------------------------------------------------------

#==============================================================================
#D Build the executables from each .$(EXT) file
#------------------------------------------------------------------------------
$(EXE_DIRECTORY)/%.exe: %.$(EXT)
	@mkdir -p deps $(EXE_DIRECTORY)
	@echo ""
	$(COMPILER) $(COMPILER_ARGS) -MMD -o $@ $<
	@cp $(EXE_DIRECTORY)/$*.d deps/$*.P
	@sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
        -e '/^$$/ d' -e 's/$$/ :/' < $(EXE_DIRECTORY)/$*.d >> deps/$*.P
	@rm -f $(EXE_DIRECTORY)/$*.d

#==============================================================================
.DELETE_ON_ERROR: result/%.test_result

#==============================================================================
result/%.test_result: $(EXE_DIRECTORY)/%.exe
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
	@$(MAKE) test

#==============================================================================
#D For deleting all temporary and made files
#------------------------------------------------------------------------------
clean: FRC
	@rm -fr exe.*/ result obj deps
	@echo "Removed all: objects, executables, and temp files."

#==============================================================================
#D Pseudo target causes all targets that depend on FRC to be remade even in 
#D case a file with the name of the target exists. Works unless there is a file
#D called FRC in the directory.
#------------------------------------------------------------------------------
FRC:

-include deps/*.P
