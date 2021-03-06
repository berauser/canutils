################################################################################
#
# Makefile
#
# Author: Benjamin Rauser
# Date:   22.09.2017
#
################################################################################

CMAKE_MINIMUM_REQUIRED( VERSION 2.8.11 )
PROJECT( CANUtils )

################################################################################
#
# cmake options
#
################################################################################

OPTION( BUILD_EXAMPLE  "Build exmaples"          FALSE )
OPTION( BUILD_TEST     "Build test"              FALSE )
OPTION( BUILD_DOC      "Create documentation"    FALSE )
OPTION( BUILD_PARANOID "Use paranoid gcc checks" TRUE  )
OPTION( USE_GCOV       "Enable gcov flags"       FALSE )

################################################################################
#
# versioning
#
################################################################################
include(${CMAKE_CURRENT_SOURCE_DIR}/versioning.cmake)
git_version(MAJOR_VERSION MINOR_VERSION PATCH_VERSION CUSTOM_VERSION "release_canutils_")

IF   (CUSTOM_VERSION STREQUAL "")
	SET( VERSION_STRING "${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}")
ELSE (CUSTOM_VERSION STREQUAL "")
	SET( VERSION_STRING "${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}-${CUSTOM_VERSION}")
ENDIF(CUSTOM_VERSION STREQUAL "")

################################################################################
#
# set compiler flags
#
################################################################################

#** check c++11 ****************************************************************
INCLUDE ( CheckCXXCompilerFlag )
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
IF   ( COMPILER_SUPPORTS_CXX11 )
	
	SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
	
ELSE ( COMPILER_SUPPORTS_CXX11 )
	
	MESSAGE(FATAL_ERROR "No c++11 support found")
	
ENDIF( COMPILER_SUPPORTS_CXX11 )

#** set Werror *****************************************************************
IF   ( BUILD_PARANOID )
	SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -Wunreachable-code -Wreturn-type" )
	SET( CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -Werror -Wall -Wextra -Wunreachable-code -Wreturn-type" )
ENDIF( BUILD_PARANOID )

#** gcov ***********************************************************************
IF   ( USE_GCOV )
	MESSAGE( STATUS "Enable gcov flags" )
	SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage --coverage -fPIC" )
	SET( CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -fprofile-arcs -ftest-coverage --coverage -fPIC" )
ENDIF( USE_GCOV )

################################################################################
#
# add sources
#
################################################################################
# set module path for find_package
SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

SET( EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin"  CACHE INTERNAL "" )
SET( LIBRARY_OUTPUT_PATH    "${PROJECT_SOURCE_DIR}/lib"  CACHE INTERNAL "" )

# TODO
# 1. determine lib32/lib64 on Linux
# 2. determine compiling on windows
SET( CMAKE_INSTALL_INCLUDEDIR "include" CACHE PATH "C header files (include)"                              )
SET( CMAKE_INSTALL_BINDIR     "bin"     CACHE PATH "user executables (bin)"                                )
SET( CMAKE_INSTALL_LIBDIR     "lib"     CACHE PATH "object code libraries"                                 )
SET( CMAKE_INSTALL_DATADIR    ""        CACHE PATH "read-only architecture-independent data (DATAROOTDIR)" )
SET( CMAKE_INSTALL_DOCDIR     "doc"     CACHE PATH "documentation root" )
SET( CMAKE_INSTALL_MANDIR     "man"     CACHE PATH "man documentation"  )

ADD_SUBDIRECTORY( src )

IF   ( BUILD_EXAMPLE )
	ADD_SUBDIRECTORY( examples )
ENDIF( BUILD_EXAMPLE )

IF   ( BUILD_TEST )
	ADD_SUBDIRECTORY( test )
ENDIF( BUILD_TEST )

IF   ( BUILD_DOC )
	ADD_SUBDIRECTORY( doc )
ENDIF( BUILD_DOC )

################################################################################
#
# print summary
#
################################################################################
MESSAGE( "" )
MESSAGE( "Summary:" )
MESSAGE( "" )
MESSAGE( "Build type: ${CMAKE_BUILD_TYPE}" )
MESSAGE( "Version:    ${VERSION_STRING}" )
MESSAGE( "" )
MESSAGE( "System:    ${CMAKE_SYSTEM_NAME}" )
MESSAGE( "processor: ${CMAKE_SYSTEM_PROCESSOR}" )
MESSAGE( "" )
MESSAGE( "BUILD_EXAMPLE:  ${BUILD_EXAMPLE}" )
MESSAGE( "BUILD_TEST:     ${BUILD_TEST}" )
MESSAGE( "BUILD_DOC:      ${BUILD_DOC}" )
MESSAGE( "BUILD_PARANOID: ${BUILD_PARANOID}" )
MESSAGE( "USE_GCOV:       ${USE_GCOV}" )
MESSAGE( "" )


