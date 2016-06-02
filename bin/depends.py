#!/usr/bin/env python
# Written by: DGC
# -*- coding: utf-8

# python imports
import copy
import os
import re
import sys

# local imports

# CPP_SANDBOX = os.path.abspath(os.path.join(os.path.dirname(sys.argv[0]), ".."))
# print CPP_SANDBOX
# exit(1)

#==============================================================================
def find_UnitCpp():
    return "D:/cygwin/usr/local/include/unitcpp_2.1.1/UnitCpp.h"

#==============================================================================
def dependencies(path):
    include_expression = re.compile("^#include *")
    sub_expression = re.compile("^.*\"(.*)\".*$")

    #==========================================================================
    def recursive_dependencies(visited, path):
#        print path
        visited.add(path)
        deps = set()
        with open(path, "r") as header:
            for line in header:
                if include_expression.match(line):
                    header = sub_expression.sub("\\1", line)
                    header = header.strip()
                    if "UnitCpp.h" in header:
                        header = find_UnitCpp()
                    if os.path.exists(header):
                        deps.add(header)
                        if not header in visited:
                            # We've not visited this, take a look
                            deps |= recursive_dependencies(visited, header)
        return deps
    return recursive_dependencies(set(), path)

#==============================================================================
def file_name(path):
    """\
Returns the file name without extension without a location.

e.g. C:/Foo/test.cpp returns test.
"""
    return os.path.splitext(os.path.basename(path))[0]
    
#==============================================================================
def makefile_dependencies(header, dependencies):
    to_stringify = [
        "$(OBJ_DIRECTORY)/",
        header,
        ".obj: ",
        header,
        ".cpp "
        ]
    for dep in dependencies:
        to_stringify.append(dep)
        to_stringify.append(" ")
    return "".join(to_stringify)

#==============================================================================
def depends(arguments):
    if len(arguments) != 2:
        print("Should have 1 argument.")
        exit(1)
    path = arguments[1]
    if not os.path.exists(path):
        print("Path {0} not found".format(path))
        exit(1)
    deps = dependencies(path)
    print(makefile_dependencies(file_name(path), deps))

#==============================================================================
if (__name__ == "__main__"):
    depends(sys.argv)
