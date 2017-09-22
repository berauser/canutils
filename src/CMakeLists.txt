################################################################################
#
# CANBuffer library
#
################################################################################

SET( CANBUFFER_NAME "CANBuffer" )

################################################################################
#
# build steps
#
################################################################################

FILE	( GLOB CANBuffer_src 
		${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	)

FILE	( GLOB CANBuffer_hdr
		${CMAKE_CURRENT_SOURCE_DIR}/*.h
	)

ADD_LIBRARY	( CANBuffer_shared SHARED
			${CANBuffer_src}
		)

SET_TARGET_PROPERTIES	( CANBuffer_shared PROPERTIES
		VERSION     ${VERSION_STRING}
		SOVERSION   ${VERSION_STRING}
		OUTPUT_NAME ${CANBUFFER_NAME}
	    )