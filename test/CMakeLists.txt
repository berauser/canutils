
SET( CANUTILS_TEST_NAME "canutils_test" )

FILE	( GLOB canutils_test_src
		${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	)

ADD_EXECUTABLE	( canutils_test
			${canutils_test_src}
		)

FIND_LIBRARY	( GMOCK
			gmock_main
		)

TARGET_INCLUDE_DIRECTORIES	( canutils_test PUBLIC
					${PROJECT_SOURCE_DIR}/src/include/
					${PROJECT_SOURCE_DIR}/src/basic/
				)

TARGET_LINK_LIBRARIES	( canutils_test
				${GMOCK}
				CANUtils_shared
			)

INSTALL	( TARGETS canutils_test
		EXPORT ${CANUTILS_TEST_NAME}
		DESTINATION ${CMAKE_INSTALL_BINDIR}
	)