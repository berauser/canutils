################################################################################
#
# Example 1 -
#
##############################################################################ää

FILE	( GLOB example1_src
		${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	)

ADD_EXECUTABLE	( example1
			${example1_src}
		)

TARGET_LINK_LIBRARIES	( example1
				CANBuffer_shared
			)

#INSTALL( TARGETS example1 DESTINATION /usr/bin )