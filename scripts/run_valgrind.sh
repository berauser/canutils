#!/bin/sh

OUTFILE=""

help() {
	echo ""
	echo "  ./$(basename $0) EXECUTABLE [ OUTPUT_FILE ]"
	echo ""
}

[ "$(which valgrind)" = "" ] && echo "please install valgrind" && exit 1
[ "$1" = "" ] && help && exit 2
EXECUTABLE="$1"
[ "$2" = "" ] && OUTFILE="$(basename $EXECUTABLE).memtest" || OUTFILE="$2"

mkdir -p $(dirname $OUTFILE)

valgrind --leak-check=full --show-leak-kinds=all --xml=yes --xml-file=$OUTFILE $EXECUTABLE

echo ""
echo "Result: $OUTFILE"
echo ""