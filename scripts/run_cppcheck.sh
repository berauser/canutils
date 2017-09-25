#!/bin/sh

help() {
	echo ""
	echo "  ./$(basename $0) SOURCE_DIR [ OUTPUT_FILE ]"
	echo ""
}

[ "$(which cppcheck)" = "" ] && echo "please install cppcheck" && exit 1
[ "$1" = "" ] && help && exit 2
SOURCE_DIR=$1

[ "$2" = "" ] && OUTPUT="$(pwd)/cppcheck.xml" || OUTPUT="$(readlink -f $(dirname $2))/$(basename $2)"
mkdir -p $(dirname $OUTPUT)

cppcheck --enable=all --inconclusive --suppress=missingIncludeSystem --check-config --xml --xml-version=2 $SOURCE_DIR 2> $OUTPUT

echo ""
echo "Result: $OUTPUT"
echo ""