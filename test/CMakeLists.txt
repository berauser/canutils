
ADD_EXECUTABLE( canbuffer_test main.cpp )

FIND_LIBRARY( GMOCK SHARED gmock_main )

TARGET_LINK_LIBRARIES( canbuffer_test ${GMOCK} )