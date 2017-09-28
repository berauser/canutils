#!/bin/sh
##############################
#
# sudo apt-get install doxygen dot
#

BASE_DIR="$(dirname $(readlink -f "$0"))/.."
DOC_DIR="$BASE_DIR/doc"
DOXYGEN_FILE="$DOC_DIR/canbuffer.doxygen"

[ "X$(which dot)" = "X" ] && echo "Dot not found" && exit 1
[ "X$(which doxygen)" = "X" ] && echo "Doxygen not found" && exit 1

( cd $BASE_DIR && \
	mkdir -p build && \
	doxygen $DOXYGEN_FILE \
)