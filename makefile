#==============================================================================
#D makes all of the .cpp files into .exe files using g++
#==============================================================================

#==============================================================================
# disable built in rules
.SUFFIXES:

COMPILER_TYPE := gcc
-include .config.mk

ifndef UNITCPP
  UNITCPP := $(shell pkg-config --cflags-only-I unitcpp | sed -e 's:-I::')
  ifdef CYGWIN
    UNITCPP := $(shell cygpath -w $(UNITCPP) | sed -e 's:\\:/:g')
  endif
endif

ifeq "$(wildcard $(UNITCPP) )" ""
  $(error $$(UNITCPP) directory not found.)
endif

#==============================================================================
ifeq ($(COMPILER_TYPE), gcc)
  COMPILER := g++
  LINKER := g++
  VERSION := $(shell g++ --version | grep "g++" | sed -e 's:.*\([0-9]\+\.[0-9]\+\.[0-9]\+\).*:\1:')
  DEBUG_ARGS := -g -DDEBUG 
  OPTIMISE_ARGS := -O3
  COMMON_ARGS := -std=c++1y -Wall -Werror -I $(UNITCPP)
  LINKER_ARGS := -pthread
  OUT_EXE_FILE := -o 
  OUT_OBJECT_FILE := -o 
  NO_LINK := -c
endif

#==============================================================================
ifeq ($(COMPILER_TYPE), clang)
  COMPILER := clang++
  LINKER := clang++
  VERSION := $(shell clang++ --version | grep "clang" | sed -e 's:[^0-9]*::' -e 's: \+.*::')

  INCLUDES := -I$(UNITCPP)
  DEBUG_ARGS := -g -DDEBUG
  OPTIMISE_ARGS := 
  COMMON_ARGS := -std=c++1y -Wall -Werror $(INCLUDES) -fexceptions -Wno-error=microsoft-pure-definition
  LINKER_ARGS := -pthread

  OUT_EXE_FILE := -o 
  OUT_OBJECT_FILE := -o 
  NO_LINK := -c
endif

#==============================================================================
ifeq ($(COMPILER_TYPE), vs)
  COMPILER := cl
  LINKER := cl
  VERSION := $(shell cl 2>&1 >/dev/null | grep "Version" | sed -e 's:.*Version ::' -e 's:\([0-9][0-9]\)\.\([0-9][0-9]\).*:\1\2:')
  # a bit of a hack because I know I'm in cygwin if I'm using cl in a makefile.
  INCLUDES := /I$(UNITCPP)
  COMMON_ARGS := /nologo
  DEBUG_ARGS = /Zi  /DDEBUG
  OPTIMISE_ARGS := /O2
  COMMON_ARGS := $(COMMON_ARGS) $(INCLUDES) /W4 /wd4481 /WX /EHsc
  LINKER_ARGS := $(COMMON_ARGS) /MTd

  VERSION_SUPPORTS_FS := $(shell expr `echo $(VERSION)` \>= 1800)
  ifeq "$(VERSION_SUPPORTS_FS)" "1"
    DEBUG_ARGS += /FS
  endif

  OUT_EXE_FILE := /Fe
  OUT_OBJECT_FILE := /Fo
  NO_LINK := /c
endif

ifndef COMPILER
  $(error "COMPILER_TYPE \"$(COMPILER_TYPE)\" unknown.")
endif

ifeq ($(OPTIMISED_BUILD), 1)
  BINARY_VARIANT := o
  COMPILER_ARGS := $(OPTIMISE_ARGS) $(COMMON_ARGS)
else
  BINARY_VARIANT := d
  COMPILER_ARGS := $(DEBUG_ARGS) $(COMMON_ARGS)
endif

COMPILER_DESCRIPTION := $(BINARY_VARIANT).$(COMPILER_TYPE).$(VERSION)
EXE_DIRECTORY := exe.$(COMPILER_DESCRIPTION)
OBJ_DIRECTORY := obj.$(COMPILER_DESCRIPTION)
RESULT_DIRECTORY := results.$(COMPILER_DESCRIPTION)
DEPENDENCY_DIRECTORY := dependency
CLEAN_DIRECTORIES := $(EXE_DIRECTORY) $(OBJ_DIRECTORY) $(RESULT_DIRECTORY)

EXT := cpp

TEST_SIN_BIN := $(shell cat sin_bin.txt | grep "^TEST: " | sed -e 's/TEST: //')


TO_TEST :=  $(shell grep -l "<UnitCpp" *.cpp | \
              sed -e 's/\.cpp/\.exe/' \
              $(foreach test, $(TEST_SIN_BIN), | grep -v $(test)) \
            )

DEPENDS_SOURCE := $(shell ls depends.dev/*.$(EXT))
DEPENDS_DIR := depends.dev/$(EXE_DIRECTORY)
DEPENDS_SPECIFIC := $(DEPENDS_DIR)/depends.exe
DEPENDS := ./bin/depends.exe

DEPENDENCY_SOURCE := $(shell ls *.$(EXT) | \
                       sed -e 's:^:$(DEPENDENCY_DIRECTORY)/:' \
                           -e 's/\.$(EXT)/\.P/' \
                     )
TEST_RESULTS := $(shell echo $(TO_TEST) | \
                  sed -e 's: : $(RESULT_DIRECTORY)/:g' \
                      -e 's:^:$(RESULT_DIRECTORY)/:g' \
                      -e 's:\.exe:.test_result:g' \
                )

#==============================================================================
#D Makes all of the $(EXT) files into exe files using $(CC)
#D Requires: $(EXT), $(CC) and $(CC_OPTS) to be defined.
#------------------------------------------------------------------------------

BUILD_SIN_BIN := $(shell cat sin_bin.txt |\
                         grep "^BUILD: " | sed -e 's/BUILD: //'\
                 )

EXE_FILES := $(shell ls *.$(EXT) | \
               sed -e 's:^:$(EXE_DIRECTORY)/:' \
                   -e 's/\.$(EXT)/\.exe/' \
               $(foreach test, $(BUILD_SIN_BIN), | grep -v $(test)) \
             )

#==============================================================================
.PHONY: all retest clean uberclean compiler_description depends

#==============================================================================
#D Target depending on all .exe files made from a .hs file so that all of them 
#D will be made.
#------------------------------------------------------------------------------
all: $(EXE_FILES) $(DEPENDS_SPECIFIC)
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
	$(LINKER) $(COMPILER_ARGS) $(LINKER_ARGS) $< $(OUT_EXE_FILE)$@
	@echo ""

#==============================================================================
.PRECIOUS: $(OBJ_DIRECTORY)/%.obj $(DEPENDENCY_DIRECTORY)/%.P

#==============================================================================
$(OBJ_DIRECTORY)/%.obj: $(DEPENDENCY_DIRECTORY)/%.P
	@mkdir -p $(OBJ_DIRECTORY)
	$(COMPILER) $(COMPILER_ARGS) $(NO_LINK) $(subst $(DEPENDENCY_DIRECTORY)/,, $(subst .P,.$(EXT),$<)) $(OUT_OBJECT_FILE)$@

#==============================================================================
$(DEPENDENCY_DIRECTORY)/%.P: %.$(EXT) $(DEPENDS)
	@mkdir -p $(DEPENDENCY_DIRECTORY)
	$(DEPENDS) $< > $@

#==============================================================================
$(DEPENDS): $(DEPENDS_SOURCE)
	$(COMPILER) $(OPTIMISE_ARGS) $(COMMON_ARGS) $< $(OUT_EXE_FILE)$@

#==============================================================================
$(DEPENDS_SPECIFIC): $(DEPENDS_SOURCE)
	@mkdir -p $(DEPENDS_DIR)
	$(COMPILER) $(COMPILER_ARGS) $< $(OUT_EXE_FILE)$@

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
retest:
	@rm -fr $(RESULT_DIRECTORY)
	@$(MAKE) test

#==============================================================================
#D For deleting all temporary and made files
#------------------------------------------------------------------------------
clean:
	@rm -fr $(CLEAN_DIRECTORIES)
	@echo "Removed: $(CLEAN_DIRECTORIES)"

#==============================================================================
#D For deleting all temporary and made files
#------------------------------------------------------------------------------
uberclean:
	@rm -fr exe.* results.* obj.* $(DEPENDENCY_DIRECTORY) $(DEPENDS)
	@echo "Removed all: objects, executables, and dependency files."

#==============================================================================
#D Getting the compiler you are using.
#------------------------------------------------------------------------------
compiler_description:
	@echo "$(COMPILER_DESCRIPTION)"

#==============================================================================
#D Make all of the dependency files
#------------------------------------------------------------------------------
depends:
	@$(MAKE) $(DEPENDENCY_SOURCE)

-include $(DEPENDENCY_DIRECTORY)/*
