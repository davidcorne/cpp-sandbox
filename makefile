#==============================================================================
#D makes all of the .cpp files into .exe files using g++
#==============================================================================

#==============================================================================
# disable built in rules
.SUFFIXES:

COMPILER_TYPE := gcc
-include .config.mk

ifndef $(UNITCPP)
  UNITCPP := $(shell pkg-config --cflags-only-I unitcpp | sed -e 's:-I::')

  ifndef $(CYGWIN)
    UNITCPP := $(shell  cygpath -w $(UNITCPP) | sed -e 's:\\:/:g')
  endif
endif

#==============================================================================
ifeq ($(COMPILER_TYPE), gcc)
  COMPILER := g++
  LINKER := g++
  VERSION := $(shell g++ --version | grep "g++" | sed -e 's:.*\([0-9]\+\.[0-9]\+\.[0-9]\+\).*:\1:')
  COMMON_ARGS := -g 
  COMPILER_ARGS := $(COMMON_ARGS) -std=c++1y -Wall -Werror -I $(UNITCPP)
  LINKER_ARGS := $(COMMON_ARGS) -pthread
  OUT_EXE_FILE := -o 
  OUT_OBJECT_FILE := -o 
  NO_LINK := -c
  GENERATE_DEPENDENCIES := -MMD
  DEPENDENCY_DIRECTORY := dependency.$(COMPILER_TYPE).$(VERSION)
  CLEAN_DIRECTORIES := $(EXE_DIRECTORY) $(OBJ_DIRECTORY) $(RESULT_DIRECTORY) $(DEPENDENCY_DIRECTORY)
endif

#==============================================================================
ifeq ($(COMPILER_TYPE), clang)
  COMPILER := clang++
  LINKER := clang++
  VERSION := $(shell clang++ --version | grep "clang" | sed -e 's:[^0-9]*::' -e 's: \+.*::')

  INCLUDES := -I$(UNITCPP)
  COMMON_ARGS:= -g
  COMPILER_ARGS := $(COMMON_ARGS) -std=c++1y -Wall -Werror $(INCLUDES) -fexceptions -Wno-error=microsoft-pure-definition
  LINKER_ARGS := $(COMMON_ARGS) #-pthread 

  OUT_EXE_FILE := -o 
  OUT_OBJECT_FILE := -o 
  NO_LINK := -c
  GENERATE_DEPENDENCIES := -MMD
  DEPENDENCY_DIRECTORY := dependency.$(COMPILER_TYPE).$(VERSION)
endif

#==============================================================================
ifeq ($(COMPILER_TYPE), vs)
  COMPILER := cl
  LINKER := cl
  VERSION := $(shell cl 2>&1 >/dev/null | grep "Version" | sed -e 's:.*Version ::' -e 's:\([0-9][0-9]\)\.\([0-9][0-9]\).*:\1\2:')
  # a bit of a hack because I know I'm in cygwin if I'm using cl in a makefile.
  INCLUDES := /I$(UNITCPP)
  COMMON_ARGS := /nologo /Zi
  COMPILER_ARGS := $(COMMON_ARGS) $(INCLUDES) /W4 /wd4481 /WX /EHsc
  LINKER_ARGS := $(COMMON_ARGS) /MTd

  VERSION_SUPPORTS_FS := $(shell expr `echo $(VERSION)` \>= 1800)
  ifeq "$(VERSION_SUPPORTS_FS)" "1"
    COMPILER_ARGS += /FS
  endif

  OUT_EXE_FILE := /Fe
  OUT_OBJECT_FILE := /Fo
  NO_LINK := /c
  GENERATE_DEPENDENCIES := 
  # use the gcc dependencies.
  DEPENDENCY_DIRECTORY := dependency.gcc.*
  ifeq ($(wildcard $(DEPENDENCY_DIRECTORY)),) 
      # No dependency.gcc files, unset the variable
      DEPENDENCY_DIRECTORY :=
  endif
  CLEAN_DIRECTORIES := $(EXE_DIRECTORY) $(OBJ_DIRECTORY) $(RESULT_DIRECTORY)
endif

ifndef COMPILER
  $(error "COMPILER_TYPE \"$(COMPILER_TYPE)\" unknown.")
endif

COMPILER_DESCRIPTION := $(COMPILER_TYPE).$(VERSION)
EXE_DIRECTORY := exe.$(COMPILER_DESCRIPTION)
OBJ_DIRECTORY := obj.$(COMPILER_DESCRIPTION)
RESULT_DIRECTORY := results.$(COMPILER_DESCRIPTION)
ifneq ($(COMPILER_TYPE), vs)
  CLEAN_DIRECTORIES := $(EXE_DIRECTORY) $(OBJ_DIRECTORY) $(RESULT_DIRECTORY) $(DEPENDENCY_DIRECTORY)
else
  CLEAN_DIRECTORIES := $(EXE_DIRECTORY) $(OBJ_DIRECTORY) $(RESULT_DIRECTORY)
endif
EXT := cpp

TEST_SIN_BIN := $(shell cat sin_bin.txt | grep "^TEST: " | sed -e 's/TEST: //')


TO_TEST :=  $(shell grep -l "<UnitCpp" *.cpp | \
             sed -e 's/\.cpp/\.exe/' \
             $(foreach test, $(TEST_SIN_BIN), | grep -v $(test)) \
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

BUILD_SIN_BIN := $(shell cat sin_bin.txt | grep "^BUILD: " | sed -e 's/BUILD: //')

EXE_FILES := $(shell \
  ls *.$(EXT) | \
  sed -e 's:^:$(EXE_DIRECTORY)/:' \
      -e 's/\.$(EXT)/\.exe/' \
  $(foreach test, $(BUILD_SIN_BIN), | grep -v $(test)) \
)

#==============================================================================
#D Target depending on all .exe files made from a .hs file so that all of them 
#D will be made.
#------------------------------------------------------------------------------
all: $(EXE_FILES)
	@echo ""
	@echo \
"make: \`all' is up to date with $(COMPILER_DESCRIPTION)."
	@echo ""

#==============================================================================
# Rules/Dependencies (all generic)
#------------------------------------------------------------------------------

#==============================================================================
#D Build the executables from each .$(EXT) file
#------------------------------------------------------------------------------
$(EXE_DIRECTORY)/%.exe: $(OBJ_DIRECTORY)/%.obj
	@mkdir -p $(EXE_DIRECTORY)
	$(LINKER) $(LINKER_ARGS) $< $(OUT_EXE_FILE)$@

#==============================================================================
.PRECIOUS: $(OBJ_DIRECTORY)/%.obj

#==============================================================================
$(OBJ_DIRECTORY)/%.obj: %.$(EXT)
	@mkdir -p $(OBJ_DIRECTORY) $(DEPENDENCY_DIRECTORY)
	@echo ""
	$(COMPILER) $(COMPILER_ARGS) $(NO_LINK) $(GENERATE_DEPENDENCIES) $< \
        $(OUT_OBJECT_FILE)$@ || (rm -f $(OBJ_DIRECTORY)/$*.d && exit 1)
# vs type compilers don't make the .P files, so make this part conditional
ifneq ($(COMPILER_TYPE), vs)
	@cp $(OBJ_DIRECTORY)/$*.d $(DEPENDENCY_DIRECTORY)/$*.P
	@sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
         -e '/^$$/ d' -e 's/$$/ :/' < $(OBJ_DIRECTORY)/$*.d >> $(DEPENDENCY_DIRECTORY)/$*.P
	@sed -i -e "s/$(OBJ_DIRECTORY)/\$$(OBJ_DIRECTORY)/" $(DEPENDENCY_DIRECTORY)/$*.P
	@rm -f $(OBJ_DIRECTORY)/$*.d
endif

#==============================================================================
.DELETE_ON_ERROR: $(RESULT_DIRECTORY)/%.test_result

#==============================================================================
$(RESULT_DIRECTORY)/%.test_result: $(EXE_DIRECTORY)/%.exe
	@mkdir -p $(RESULT_DIRECTORY)
	@./bin/run_test.sh $< $@

#==============================================================================
test: $(EXE_FILES) $(TEST_RESULTS)
	@echo
	@echo \
"Tests passed with $(COMPILER_DESCRIPTION)."

#==============================================================================
retest: FRC
	@rm -fr $(RESULT_DIRECTORY)
	@$(MAKE) test

#==============================================================================
#D For deleting all temporary and made files
#------------------------------------------------------------------------------
clean: FRC
	@rm -fr $(CLEAN_DIRECTORIES)
	@echo "Removed: $(CLEAN_DIRECTORIES)"

#==============================================================================
#D For deleting all temporary and made files
#------------------------------------------------------------------------------
uberclean: FRC
	@rm -fr exe.* results.* obj.* dependency.*
	@echo "Removed all: objects, executables, and dependency files."

#==============================================================================
#D Getting the compiler you are using.
#------------------------------------------------------------------------------
compiler_description: FRC
	@echo "$(COMPILER_DESCRIPTION)"

#==============================================================================
#D Pseudo target causes all targets that depend on FRC to be remade even in 
#D case a file with the name of the target exists. Works unless there is a file
#D called FRC in the directory.
#------------------------------------------------------------------------------
FRC:

-include $(DEPENDENCY_DIRECTORY)/*.P
