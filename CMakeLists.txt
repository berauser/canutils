################################################################################
#
# Makefile
#
# Author: Benjamin Rauser
# Date:   22.09.2017
#
################################################################################

CMAKE_MINIMUM_REQUIRED( VERSION 2.8.11 )
PROJECT( CANBuffer )

################################################################################
#
# cmake options
#
################################################################################

OPTION( BUILD_TEST "Build test"        FALSE )
OPTION( USE_GCOV   "Enable gcov flags" FALSE )

################################################################################
#
# versioning
#
################################################################################

SET( MAJOR_VERSION "0" )
SET( MINOR_VERSION "0" )
SET( PATCH_VERSION "0" )
SET( VERSION_STRING "${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}")

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
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror" )
SET( CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -Werror" )

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

ADD_SUBDIRECTORY( src )
ADD_SUBDIRECTORY( examples )
#ADD_SUBDIRECTORY( test )