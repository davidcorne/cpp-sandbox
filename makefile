#==============================================================================
#D makes all of the .cpp files into .exe files using g++
#==============================================================================

COMPILER_TYPE = gcc
-include .config.mk

EXE_DIRECTORY = exe.$(COMPILER_TYPE)
OBJ_DIRECTORY = obj.$(COMPILER_TYPE)
RESULT_DIRECTORY = result.$(COMPILER_TYPE)
EXT = cpp

#==============================================================================
ifeq ($(COMPILER_TYPE), gcc)
  COMPILER = g++
  COMPILER_ARGS = -std=c++0x -g -Wall -Werror -pthread $(shell pkg-config --cflags-only-I unitcpp)
  OUT_EXE_FILE = -o 
  OUT_OBJECT_FILE = -o 
  NO_LINK = -c
  GENERATE_DEPENDENCIES = -MMD
endif

#==============================================================================
ifeq ($(COMPILER_TYPE), clang)
  COMPILER = clang++
  COMPILER_ARGS = -std=c++1y -g -Wall -Werror -pthread $(shell pkg-config --cflags-only-I unitcpp)
  OUT_EXE_FILE = -o 
  OUT_OBJECT_FILE = -o 
  NO_LINK = -c
  GENERATE_DEPENDENCIES = -MMD
endif

#==============================================================================
ifeq ($(COMPILER_TYPE), vs)
  COMPILER = cl
  # a bit of a hack because I know I'm in cygwin if I'm using cl in a makefile.
  INCLUDES = /I.. /I$(shell cygpath -w $$(pkg-config --cflags-only-I unitcpp | sed -e 's:-I::') | sed -e 's:\\:/:g')
  COMPILER_ARGS = $(INCLUDES) /W4 /wd4481 /WX /EHsc
  OUT_EXE_FILE = /Fe
  OUT_OBJECT_FILE = /Fo
  NO_LINK = /c
  GENERATE_DEPENDENCIES = 
endif

SIN_BIN = CoercionByMemberTemplate.exe 


TO_TEST =  $(shell grep -l "\(class *utest_\)\|\(<UnitCpp\)" *.cpp | \
             sed -e 's/\.cpp/\.exe/' \
             $(foreach test, $(SIN_BIN), | grep -v $(test)) \
           )

TEST_RESULTS := $(shell \
  echo $(TO_TEST) |\
  sed -e 's: : $(RESULT_DIRECTORY)/:g' \
      -e 's:^:$(RESULT_DIRECTORY)/:g' \
      -e 's:\.exe:.test_result:g'\
)

#==============================================================================
#D Makes all of the $(EXT) files into exe files using $(CC)
#D Requires: $(EXT), $(CC) and $(CC_OPTS) to be defined.
#------------------------------------------------------------------------------

EXE_FILES = $(shell ls *.$(EXT) | sed -e 's:^:$(EXE_DIRECTORY)/:' -e 's/\.$(EXT)/\.exe/')

#==============================================================================
#D Target depending on all .exe files made from a .hs file so that all of them 
#D will be made.
#------------------------------------------------------------------------------
all: $(EXE_FILES)
	@echo ""
	@echo \
"make: \`all' is up to date with" \
"$(shell ./$(EXE_DIRECTORY)/Compiler.exe)"\
" version "\
"$(shell ./$(EXE_DIRECTORY)/Version.exe)"\
"."
	@echo ""

#==============================================================================
# Rules/Dependencies (all generic)
#------------------------------------------------------------------------------

#==============================================================================
#D Build the executables from each .$(EXT) file
#------------------------------------------------------------------------------
$(EXE_DIRECTORY)/%.exe: $(OBJ_DIRECTORY)/%.obj
	@mkdir -p $(EXE_DIRECTORY)
	$(COMPILER) $(COMPILER_ARGS) $(OUT_EXE_FILE)$@ $<

#==============================================================================
.PRECIOUS: $(OBJ_DIRECTORY)/%.obj

#==============================================================================
$(OBJ_DIRECTORY)/%.obj: %.$(EXT)
	@mkdir -p deps $(OBJ_DIRECTORY)
	@echo ""
	$(COMPILER) $(COMPILER_ARGS) $(NO_LINK) $(GENERATE_DEPENDENCIES) $(OUT_OBJECT_FILE)$@ $<
# vs type compilers don't make the .P files, so 2>/dev/null; true hides the 
# error output and tells make these commands succeeded.
	@cp $(OBJ_DIRECTORY)/$*.d deps/$*.P 2>/dev/null; true
	@sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
        -e '/^$$/ d' -e 's/$$/ :/' < $(OBJ_DIRECTORY)/$*.d >> deps/$*.P 2>/dev/null; true
	@rm -f $(OBJ_DIRECTORY)/$*.d 2>/dev/null; true

#==============================================================================
.DELETE_ON_ERROR: $(RESULT_DIRECTORY)/%.test_result

#==============================================================================
$(RESULT_DIRECTORY)/%.test_result: $(EXE_DIRECTORY)/%.exe
	@mkdir -p $(RESULT_DIRECTORY)
	@chmod +x $<
	@printf "%-50s" $<:
	@./$< 0 > $@
	@echo -e "\e[0;32m Passed.\e[1;37m"

#==============================================================================
test: $(EXE_FILES) $(TEST_RESULTS)
	@echo
	@echo \
"tests passed with" \
"$(shell ./$(EXE_DIRECTORY)/Compiler.exe)"\
" version "\
"$(shell ./$(EXE_DIRECTORY)/Version.exe)"\
"."

#==============================================================================
retest: FRC
	@rm -fr $(RESULT_DIRECTORY)
	@$(MAKE) test

#==============================================================================
#D For deleting all temporary and made files
#------------------------------------------------------------------------------
clean: FRC
	@rm -fr exe.*/ result.* obj.* deps
	@echo "Removed all: objects, executables, and temp files."

#==============================================================================
#D Pseudo target causes all targets that depend on FRC to be remade even in 
#D case a file with the name of the target exists. Works unless there is a file
#D called FRC in the directory.
#------------------------------------------------------------------------------
FRC:

-include deps/*.P
