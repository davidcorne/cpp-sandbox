#!/bin/sh
# Written by: DGC

#==============================================================================
usage() {
  cat <<EOF
Usage: $(basename $0) <options> test-executable result-file

Runs the test and creates a result file if it succeeds.

Options:
-h                 Display this message.
EOF
}

#==============================================================================
# Main
while getopts ":h?" option
do
  case $option in
    h)
      usage
      exit 0
      ;;
    \?)
      echo -e "Invalid option: -$OPTARG \n"
      usage
      exit 1
      ;;
  esac
done

test_file=$1
if [ -z $test_file ]
then
  usage
  exit 1
fi

if [ ! -f $test_file ]
then
  echo "$test_file is not a file."
  exit 1
fi

result_file=$2
if [ -z $result_file ]
then
  usage
  exit 1
fi

chmod +x $test_file
result=$(./$test_file 0)
exit_value=$?
printf "%-60s " $test_file
if [ $exit_value -eq 0 ]
then
  echo -e "\e[0;32mPassed.\e[1;37m"
  echo "$result" > $result_file
else
  echo -e "\e[0;31mFailed.\e[1;37m"
  echo "$result"
  exit 1
fi
