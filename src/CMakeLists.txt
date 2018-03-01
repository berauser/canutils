################################################################################
#
# CANUtils library
#
################################################################################

SET( CANUTILS_NAME "canutils" )

SET( CANUTILS_ROOT_DIR    "${CMAKE_CURRENT_SOURCE_DIR}/"          )
SET( CANUTILS_MISC_DIR    "${CMAKE_CURRENT_SOURCE_DIR}/misc/"     )
SET( CANUTILS_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/canutils/" )

SET( CANUTILS_BASIC_DIR   "${CMAKE_CURRENT_SOURCE_DIR}/basic/"    )
SET( CANUTILS_BUFFER_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/buffer/"   )
SET( CANUTILS_LINUX_DIR   "${CMAKE_CURRENT_SOURCE_DIR}/linux/"    )
SET( CANUTILS_WINDOWS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/windows/"  )

SET( CANUTILS_VERSION_FILE_IN "${CMAKE_CURRENT_SOURCE_DIR}/misc/version.h.in" )
SET( CANUTILS_VERSION_FILE    "${CMAKE_CURRENT_SOURCE_DIR}/misc/version.h"    )

SET( CANUTILS_SOURCE_DIR  "" )

SET( CANUTILS_ADDITIONAL_LIBS "" )

################################################################################
#
# platform
#
################################################################################

MESSAGE( STATUS "Platform ${CMAKE_SYSTEM_NAME} detected" )
IF    ( "${CMAKE_SYSTEM_NAME}" STREQUAL "Linux" )
	
	# use linux implementation
	MESSAGE(STATUS "Compiling for Linux...")
	SET( CANUTILS_SOURCE_DIR "${CANUTILS_LINUX_DIR}" )
	
	# build additional libs
	ADD_SUBDIRECTORY( ${CANUTILS_LINUX_DIR}/helper )
	SET	( CANUTILS_ADDITIONAL_LIBS
			${CANUTILS_ADDITIONAL_LIBS}
			netlink
		)
	
ELSEIF( "${CMAKE_SYSTEM_NAME}" STREQUAL "Windows" )
	
	# windows implementation
	MESSAGE(FATAL "Windows is currently not implemented")
	SET( CANUTILS_SOURCE_DIR "${CANUTILS_WINDOWS_DIR}" )
	
ELSE  ()
	
	# unknown platform
	MESSAGE(FATAL_ERROR "Unknown platform: ${CMAKE_SYSTEM_NAME}")
	SET( CANUTILS_SOURCE_DIR "" )
	
ENDIF ()

IF   ( "${CANUTILS_SOURCE_DIR}" EQUAL "" )
	# no suitable implmentation found
	MESSAGE(FATAL_ERROR "No suitable implementation found. Abort." )
	
ENDIF( "${CANUTILS_SOURCE_DIR}" EQUAL "" )

MESSAGE( STATUS "CANUTILS_SOURCE_DIR: ${CANUTILS_SOURCE_DIR}" )

################################################################################
#
# configure files
#
################################################################################
CONFIGURE_FILE	(
			${CANUTILS_VERSION_FILE_IN}
			${CANUTILS_VERSION_FILE} @ONLY
		)
################################################################################
#
# build steps
#
################################################################################

FILE	( GLOB CANUtils_src
		${CANUTILS_INCLUDE_DIR}/*.cpp
		${CANUTILS_BASIC_DIR}/*.cpp
		${CANUTILS_BUFFER_DIR}/*.cpp
		${CANUTILS_SOURCE_DIR}/*.cpp
	)

ADD_LIBRARY	( CANUtils_shared SHARED
			${CANUtils_src}
		)

TARGET_LINK_LIBRARIES	( CANUtils_shared
				pthread
				${CANUTILS_ADDITIONAL_LIBS}
			)

TARGET_INCLUDE_DIRECTORIES	( CANUtils_shared
					PUBLIC    ${CANUTILS_INCLUDE_DIR}
					PRIVATE   ${CANUTILS_BASIC_DIR}
					PRIVATE   ${CANUTILS_MISC_DIR}
					PRIVATE   ${CANUTILS_ROOT_DIR}
				)

SET_TARGET_PROPERTIES	( CANUtils_shared PROPERTIES
		VERSION     ${VERSION_STRING}
		SOVERSION   ${VERSION_STRING}
		OUTPUT_NAME ${CANUTILS_NAME}
	)

################################################################################
#
# install
#
################################################################################

INSTALL	( TARGETS CANUtils_shared
		ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
		LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
		RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR}
	)

INSTALL	( DIRECTORY ${CANUTILS_INCLUDE_DIR} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/canutils/ )
