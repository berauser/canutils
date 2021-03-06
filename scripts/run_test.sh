#!/bin/sh

BASE_DIR="$(dirname $(readlink -f "$0"))/.."
BUILD_DIR="$BASE_DIR/build"

# 3. run test
( cd $BASE_DIR && \
    $BASE_DIR/bin/canutils_test \
	--gtest_output=xml:$BASE_DIR/canutilsTestResult.xml \
)