################################################################################
#
# Example 2 -
#
##############################################################################ää

FILE	( GLOB example2_src
		${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	)

ADD_EXECUTABLE	( example2
			${example2_src}
		)

TARGET_LINK_LIBRARIES	( example2
				CANUtils_shared
			)

TARGET_INCLUDE_DIRECTORIES	( example2
					PRIVATE ${PROJECT_SOURCE_DIR}/src/
				)

INSTALL	( TARGETS example2
		EXPORT CANUtils_example2
		DESTINATION ${CMAKE_INSTALL_BINDIR}
	)
