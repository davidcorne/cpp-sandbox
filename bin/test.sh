#!/bin/bash
# Written by: DGC

set -e

#==============================================================================
test_compiler()
{
  compiler=$1
  compiler_type=$2
  if type $program >/dev/null 2>&1
  then
    echo "Has $compiler"
    make -j 4 COMPILER_TYPE=$compiler_type
    make test COMPILER_TYPE=$compiler_type
    tested_compilers="$tested_compilers $(make COMPILER_TYPE=$compiler_type compiler_description)"
  fi
}

tested_compilers=""

#==============================================================================
if type gcc 2>/dev/null > /dev/null
then
  test_compiler gcc gcc
fi
if type clang 2>/dev/null > /dev/null
then
  test_compiler clang clang
fi
if type cl 2>/dev/null > /dev/null
then
  test_compiler cl vs
fi
echo "Tested with:$tested_compilers"
