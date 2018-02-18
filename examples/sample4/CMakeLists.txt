################################################################################
#
# Example 4 -
#
##############################################################################ää

FILE	( GLOB example4_src
		${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	)

ADD_EXECUTABLE	( example4
			${example4_src}
		)

TARGET_LINK_LIBRARIES	( example4
				CANBuffer_shared
			)

TARGET_INCLUDE_DIRECTORIES	( example4
					PRIVATE ${PROJECT_SOURCE_DIR}/src/
				)

INSTALL	( TARGETS example4
		EXPORT CANBuffer_example4
		DESTINATION ${CMAKE_INSTALL_BINDIR}
	)
