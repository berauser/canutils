
################################################################################
#
# variables
#
################################################################################

SET( CANBUFFER_DOC_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/doc" )
SET( CANBUFFER_EXAMPLE_DIR    "${CMAKE_SOURCE_DIR}/example"     )
SET( CANBUFFER_SOURCE_DIR     "${CMAKE_SOURCE_DIR}/src"         )

SET( CANBUFFER_DOXYGEN_CONFIG_FILE_IN "${CMAKE_CURRENT_SOURCE_DIR}/canbuffer.doxygen.in" )
SET( CANBUFFER_DOXYGEN_CONFIG_FILE    "${CMAKE_CURRENT_BINARY_DIR}/canbuffer.doxygen"    )
SET( DOXYGEN_DOCUMENTATION            "${CMAKE_CURRENT_BINARY_DIR}/doxygen.log"          )

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
				${CANBUFFER_DOXYGEN_CONFIG_FILE_IN}
				${CANBUFFER_DOXYGEN_CONFIG_FILE} @ONLY
			)
	
	#** create docu ***
	ADD_CUSTOM_COMMAND	(
					OUTPUT ${DOXYGEN_DOCUMENTATION}
					COMMAND ${CMAKE_COMMAND} -E echo_append "Building documentation..."
					COMMAND ${DOXYGEN_EXECUTABLE} ${CANBUFFER_DOXYGEN_CONFIG_FILE} > ${DOXYGEN_DOCUMENTATION}
					COMMAND ${CMAKE_COMMAND} -E echo "Done."
					WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
					DEPENDS ${CANBUFFER_DOXYGEN_CONFIG_FILE}
				)
	
	ADD_CUSTOM_TARGET(doc ALL DEPENDS ${DOXYGEN_DOCUMENTATION})
	
	INSTALL( DIRECTORY ${CANBUFFER_DOC_OUTPUT_DIR}/html DESTINATION ${CMAKE_INSTALL_DOCDIR} )
	INSTALL( DIRECTORY ${CANBUFFER_DOC_OUTPUT_DIR}/man  DESTINATION ${CMAKE_INSTALL_MANDIR} )
	
ELSE ( DOXYGEN_FOUND )
	
	MESSAGE( SEND_ERROR "Doxygen not found. COntinue without documentation" )
	
ENDIF( DOXYGEN_FOUND )