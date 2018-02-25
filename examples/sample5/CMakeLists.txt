################################################################################
#
# Example 5 -
#
##############################################################################ää

FILE	( GLOB example5_src
		${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	)

ADD_EXECUTABLE	( example5
			${example5_src}
		)

TARGET_LINK_LIBRARIES	( example5
				CANBuffer_shared
			)

TARGET_INCLUDE_DIRECTORIES	( example5
					PRIVATE ${PROJECT_SOURCE_DIR}/src/
				)

INSTALL	( TARGETS example5
		EXPORT CANBuffer_example5
		DESTINATION ${CMAKE_INSTALL_BINDIR}
	)
