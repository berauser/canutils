
FILE	( GLOB canbuffer_test_src
		${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	)

ADD_EXECUTABLE	( canbuffer_test
			${canbuffer_test_src}
		)

FIND_LIBRARY	( GMOCK
			gmock_main
		)

TARGET_INCLUDE_DIRECTORIES	( canbuffer_test PUBLIC
					${PROJECT_SOURCE_DIR}/src/
				)

TARGET_LINK_LIBRARIES	( canbuffer_test
				${GMOCK}
				CANBuffer_shared
			)