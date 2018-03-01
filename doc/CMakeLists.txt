
################################################################################
#
# variables
#
################################################################################

SET( CANUTILS_DOC_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/doc" )
SET( CANUTILS_EXAMPLE_DIR    "${CMAKE_SOURCE_DIR}/example"     )
SET( CANUTILS_SOURCE_DIR     "${CMAKE_SOURCE_DIR}/src"         )

SET( CANUTILS_DOXYGEN_CONFIG_FILE_IN "${CMAKE_CURRENT_SOURCE_DIR}/canutils.doxygen.in" )
SET( CANUTILS_DOXYGEN_CONFIG_FILE    "${CMAKE_CURRENT_BINARY_DIR}/canutils.doxygen"    )
SET( DOXYGEN_DOCUMENTATION           "${CMAKE_CURRENT_BINARY_DIR}/doxygen.log"         )

################################################################################
#
# build documentation
#
################################################################################

FIND_PACKAGE(Doxygen)

IF   ( DOXYGEN_FOUND )
	
	IF   ( DOXYGEN_DOT_EXECUTABLE )
		SET( DOXYGEN_HAVE_DOT "YES" )
	ELSE ( DOXYGEN_DOT_EXECUTABLE )
		MESSAGE( WARNING "Dot not found. Continue without dot..." )
		SET( DOXYGEN_HAVE_DOT "NO" )
	ENDIF( DOXYGEN_DOT_EXECUTABLE )
	
	CONFIGURE_FILE	(
				${CANUTILS_DOXYGEN_CONFIG_FILE_IN}
				${CANUTILS_DOXYGEN_CONFIG_FILE} @ONLY
			)
	
	#** create docu ***
	ADD_CUSTOM_COMMAND	(
					OUTPUT ${DOXYGEN_DOCUMENTATION}
					COMMAND ${CMAKE_COMMAND} -E echo_append "Building documentation..."
					COMMAND ${DOXYGEN_EXECUTABLE} ${CANUTILS_DOXYGEN_CONFIG_FILE} > ${DOXYGEN_DOCUMENTATION}
					COMMAND ${CMAKE_COMMAND} -E echo "Done."
					WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
					DEPENDS ${CANUTILS_DOXYGEN_CONFIG_FILE}
				)
	
	ADD_CUSTOM_TARGET(doc ALL DEPENDS ${DOXYGEN_DOCUMENTATION})
	
	INSTALL( DIRECTORY ${CANUTILS_DOC_OUTPUT_DIR}/html DESTINATION ${CMAKE_INSTALL_DOCDIR} )
	INSTALL( DIRECTORY ${CANUTILS_DOC_OUTPUT_DIR}/man  DESTINATION ${CMAKE_INSTALL_MANDIR} )
	
ELSE ( DOXYGEN_FOUND )
	
	MESSAGE( SEND_ERROR "Doxygen not found. Continue without documentation" )
	
ENDIF( DOXYGEN_FOUND )