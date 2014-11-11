#!/bin/sh
# Written by: DGC

set -e

tested_compilers=""

declare -A commands=(["clang"]="clang" ["vs"]="cl" ["gcc"]="g++")
broken=()

for key in "${!commands[@]}"
do
  program=${commands[$key]}
  if $(command -v $program >/dev/null 2>&1)
  then
    echo "Has $program"
    this_broken=0
    for b in ${broken[@]}
    do
      if [ "$b" == "$key" ]
      then
        this_broken=1
      fi
    done
    if [ $this_broken -eq 1 ] 
    then
      echo "$program broken."
    else
      make -j 4 COMPILER_TYPE=$key
      make test COMPILER_TYPE=$key
      tested_compilers="tested_compilers $key"
    fi
  fi
done
exit 
