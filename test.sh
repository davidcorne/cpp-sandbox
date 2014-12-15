#!/bin/bash
# Written by: DGC

set -e

#==============================================================================
test_compiler()
{
  compiler=$1
  compiler_type=$2
  if $(command -v $program >/dev/null 2>&1)
  then
    echo "Has $compiler"
    make -j 4 COMPILER_TYPE=$compiler_type
    make test COMPILER_TYPE=$compiler_type
    tested_compilers="$tested_compilers $compiler_type"
  fi
}

tested_compilers=""

#==============================================================================
test_compiler clang clang
test_compiler gcc gcc
if type vc10x64 2>/dev/null > /dev/null
then
  vc10x64
  test_compiler cl vs
fi
if type vc11x64 2>/dev/null > /dev/null
then
  vc11x64
  test_compiler cl vs
fi
if type vc12x64 2>/dev/null > /dev/null
then
  vc12x64
  test_compiler cl vs
fi
echo "Tested with:$tested_compilers"
