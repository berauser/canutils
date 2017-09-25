#!/bin/sh
##############################
#
# sudo apt-get install lcov
#

BASE_DIR="$(dirname $(readlink -f "$0"))/.."
BUILD_DIR="$BASE_DIR/build"
OUTPUT_DIR="$BUILD_DIR/coverage/"
OUTPUT_DIR_HTML="$BUILD_DIR/coverage/html/"
OUTPUT_DIR_XML="$BUILD_DIR/coverage/xml/"
COVERAGE_INFO="$OUTPUT_DIR/coverage.info"
XML_RESULT="$OUTPUT_DIR_XML/coverage.xml"

( cd $BASE_DIR && \
    make -C $BASE_DIR && \
    $BASE_DIR/bin/canbuffer_test \
) || ( echo "Failed to run tests..."; exit 1 )

( cd $BUILD_DIR/ && \
    mkdir -p $OUTPUT_DIR && \
    lcov --capture --directory . --output-file $COVERAGE_INFO.unfiltered && \
    lcov --remove $COVERAGE_INFO.unfiltered '/usr/include/*' -o $COVERAGE_INFO \
) || ( echo "Failed to run lcov..."; exit 2 )

( cd $BUILD_DIR/ && \
    mkdir -p $OUTPUT_DIR_HTML && \
    genhtml $COVERAGE_INFO --output-directory $OUTPUT_DIR_HTML \
) || ( echo "Failed to run genhtml..." )

( cd $BUILD_DIR/ && \
    mkdir -p $OUTPUT_DIR_XML && \
    gcovr -v -s -r $BASE_DIR --xml -o $XML_RESULT \
) || ( echo "Failed to run gcovr..." )