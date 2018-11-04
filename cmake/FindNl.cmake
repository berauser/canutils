# - Find libnl-3
# Find the native libnl-3/libnl-route-3 includes and libraries
#
#  NL_INCLUDE_DIR - where to find netlink.h, etc.
#  NL_LIBRARIES   - List of libraries when using libnl-3.
#  NL_FOUND       - True if libnl-3 and libnl-route-3 found.

if(NL_INCLUDE_DIR)
    # Already in cache, be silent
    set(NL_FIND_QUIETLY TRUE)
endif(NL_INCLUDE_DIR)

find_path(NL_INCLUDE_DIR netlink/netlink.h
    PATH_SUFFIXES libnl3
)

find_library(NL_LIBRARY NAMES nl nl-3)
find_library(NL_ROUTE_LIBRARY NAMES nl-route nl-route-3)

# Handle the QUIETLY and REQUIRED arguments and set NL_FOUND to TRUE if
# all listed variables are TRUE.
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(NL DEFAULT_MSG NL_LIBRARY NL_ROUTE_LIBRARY NL_INCLUDE_DIR)

if(NL_FOUND)
    set(NL_LIBRARIES ${NL_LIBRARY} ${NL_ROUTE_LIBRARY})
    message("Found netlink libraries:  ${NL_LIBRARIES}")
    message("Found netlink includes: ${NL_INCLUDE_DIR}")
else(NL_FOUND)
    set(NL_LIBRARIES)
    message("Netlink version 3 development packages cannot be found.")
    message("In Debian/Ubuntu, they may be called:")
    message("libnl-3 libnl-route-3 libnl-3-dev")
    message(FATAL_ERROR "Could not find netlink library.")
endif(NL_FOUND)

mark_as_advanced(NL_INCLUDE_DIR NL_LIBRARY)
