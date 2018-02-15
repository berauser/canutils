
################################################################################
#
# Netlink library
#
################################################################################

SET( NETLINK_NAME "netlink" )

SET( NETLINK_MAJOR_VERSION 0 )
SET( NETLINK_MINOR_VERSION 1 )
SET( NETLINK_PATCH_VERSION 0 )
SET( NETLINK_VERSION_STRING "${NETLINK_MAJOR_VERSION}.${NETLINK_MINOR_VERSION}.${NETLINK_PATCH_VERSION}" )

################################################################################
#
# build steps
#
################################################################################

FILE	( GLOB NETLINK_pub_header
		${CMAKE_CURRENT_SOURCE_DIR}/*.h
	)

FILE	( GLOB NETLINK_src
		${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	)

ADD_LIBRARY	( netlink STATIC
			${NETLINK_src}
		)

SET_TARGET_PROPERTIES	( netlink PROPERTIES
				VERSION     ${NETLINK_VERSION_STRING}
				SOVERSION   ${NETLINK_VERSION_STRING}
				OUTPUT_NAME ${NETLINK_NAME}
			)

################################################################################
#
# install
#
################################################################################

INSTALL	( TARGETS netlink
		ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
		LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
		RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR}
	)

INSTALL	( FILES ${NETLINK_pub_header} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} )