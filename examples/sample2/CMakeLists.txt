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
				CANBuffer_shared
			)

TARGET_INCLUDE_DIRECTORIES	( example2 PUBLIC
					${PROJECT_SOURCE_DIR}/src/
				)

#INSTALL( TARGETS example2 DESTINATION /usr/bin )