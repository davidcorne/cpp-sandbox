#==============================================================================
#D makes all of the .cpp files into .exe files using g++
#==============================================================================

CC = g++
EXT = cpp
CC_OPTS = -std=c++0x -o $@

include $(DROPBOX)/Coding/MakeFiles/all.mk
