################################################################################
#
# Example 3 -
#
##############################################################################ää

FILE	( GLOB example3_src
		${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	)

ADD_EXECUTABLE	( example3
			${example3_src}
		)

TARGET_LINK_LIBRARIES	( example3
				CANBuffer_shared
			)

TARGET_INCLUDE_DIRECTORIES	( example3
					PRIVATE ${PROJECT_SOURCE_DIR}/src/
				)

INSTALL	( TARGETS example3
		EXPORT CANBuffer_example3
		DESTINATION ${CMAKE_INSTALL_BINDIR}
	)
