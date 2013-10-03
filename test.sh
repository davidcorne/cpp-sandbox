#!/bin/sh
# Written by: DGC

set -e

# make sure everything is made
make -B
chmod +x *.exe
./LinkedList.exe
