################################################################################
#
# CANBuffer library
#
################################################################################

SET( CANBUFFER_NAME "CANBuffer" )

SET( CANBUFFER_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/" )
SET( CANBUFFER_MISC_DIR    "${CMAKE_CURRENT_SOURCE_DIR}/misc/"    )

SET( CANBUFFER_BASIC_DIR   "${CMAKE_CURRENT_SOURCE_DIR}/basic/"   )
SET( CANBUFFER_LINUX_DIR   "${CMAKE_CURRENT_SOURCE_DIR}/linux/"   )
SET( CANBUFFER_WINDOWS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/windows/" )

SET( CANBUFFER_SOURCE_DIR  "" )

SET( CANBUFFER_ADDITIONAL_LIBS "" )

################################################################################
#
# platform
#
################################################################################

MESSAGE( STATUS "Platform ${CMAKE_SYSTEM_NAME} detected" )
IF    ( "${CMAKE_SYSTEM_NAME}" STREQUAL "Linux" )
	
	# use linux implementation
	MESSAGE(STATUS "Compiling for Linux...")
	SET( CANBUFFER_SOURCE_DIR "${CANBUFFER_LINUX_DIR}" )
	
	# build additional libs
	ADD_SUBDIRECTORY( ${CANBUFFER_LINUX_DIR}/helper )
	SET	( CANBUFFER_ADDITIONAL_LIBS
			${CANBUFFER_ADDITIONAL_LIBS}
			netlink
		)
	
ELSEIF( "${CMAKE_SYSTEM_NAME}" STREQUAL "Windows" )
	
	# windows implementation
	MESSAGE(FATAL "Windows is currently not implemented")
	SET( CANBUFFER_SOURCE_DIR "${CANBUFFER_WINDOWS_DIR}" )
	
ELSE  ()
	
	# unknown platform
	MESSAGE(FATAL_ERROR "Unknown platform: ${CMAKE_SYSTEM_NAME}")
	SET( CANBUFFER_SOURCE_DIR "" )
	
ENDIF ()

IF   ( "${CANBUFFER_SOURCE_DIR}" EQUAL "" )
	# no suitable implmentation found
	MESSAGE(FATAL_ERROR "No suitable implementation found. Abort." )
	
ENDIF( "${CANBUFFER_SOURCE_DIR}" EQUAL "" )

MESSAGE( STATUS "CANBUFFER_SOURCE_DIR: ${CANBUFFER_SOURCE_DIR}" )
################################################################################
#
# build steps
#
################################################################################

FILE	( GLOB CANBuffer_src
		${CANBUFFER_INCLUDE_DIR}/*.cpp
		${CANBUFFER_BASIC_DIR}/*.cpp
		${CANBUFFER_SOURCE_DIR}/*.cpp
	)

ADD_LIBRARY	( CANBuffer_shared SHARED
			${CANBuffer_src}
		)

TARGET_LINK_LIBRARIES	( CANBuffer_shared
				pthread
				${CANBUFFER_ADDITIONAL_LIBS}
			)

TARGET_INCLUDE_DIRECTORIES	( CANBuffer_shared
					PUBLIC    ${CANBUFFER_INCLUDE_DIR}
					PRIVATE   ${CANBUFFER_BASIC_DIR}
					PRIVATE   ${CANBUFFER_MISC_DIR}
				)

SET_TARGET_PROPERTIES	( CANBuffer_shared PROPERTIES
		VERSION     ${VERSION_STRING}
		SOVERSION   ${VERSION_STRING}
		OUTPUT_NAME ${CANBUFFER_NAME}
	)

################################################################################
#
# install
#
################################################################################

INSTALL	( TARGETS CANBuffer_shared
		ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
		LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
		RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR}
	)

INSTALL	( DIRECTORY ${CANBUFFER_INCLUDE_DIR} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} )
