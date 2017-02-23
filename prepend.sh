#!/bin/bash
#
# prepend line to file
if (( $# < 1 ))
then
    echo "Usage: $0 file"
    exit 1
fi

file="$1"
line="#include <stack_chk.h>"
tmp="/tmp/out"

echo $line | cat - $file > $tmp && mv $tmp $file 
