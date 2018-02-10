
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
					${PROJECT_SOURCE_DIR}/src/include/
					${PROJECT_SOURCE_DIR}/src/basic/
				)

TARGET_LINK_LIBRARIES	( canbuffer_test
				${GMOCK}
				CANBuffer_shared
			)

INSTALL	( TARGETS canbuffer_test
		EXPORT CANBuffer_test
		DESTINATION ${CMAKE_INSTALL_BINDIR}
	)