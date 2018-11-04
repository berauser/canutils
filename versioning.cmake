

function(git_version _major _minor _patch _dirty _matches)

    # Get the current tag
    execute_process(
      COMMAND git describe --match=${_matches}* --tags
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
      OUTPUT_VARIABLE version
      OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    message("version: ${version}")
    if(NOT version)
        set(${_major} "0" PARENT_SCOPE)
        set(${_minor} "0" PARENT_SCOPE)
        set(${_patch} "0" PARENT_SCOPE)
        set(${_dirty} ""  PARENT_SCOPE)
        return()
    endif(NOT version)

    string(REGEX REPLACE "^${_matches}([0-9]+)\\..*" "\\1" version_major "${version}")
    string(REGEX REPLACE "^${_matches}[0-9]+\\.([0-9]+).*" "\\1" version_minor "${version}")
    string(REGEX REPLACE "^${_matches}[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" version_patch "${version}")
    string(REGEX REPLACE "^${_matches}[0-9]+\\.[0-9]+\\.[0-9]+(.*)" "\\1" version_git_dirty "${version}")
    string(REGEX REPLACE "^-[0-9]-g+(.*)" "\\1" version_dirty "${version_git_dirty}")
message("${version} --> ${version_git_dirty} --> ${version_dirty}")

    set(${_major} "${version_major}" PARENT_SCOPE)
    set(${_minor} "${version_minor}" PARENT_SCOPE)
    set(${_patch} "${version_patch}" PARENT_SCOPE)
    set(${_dirty} "${version_dirty}" PARENT_SCOPE)
    message("MAJOR --> ${_major} --> ${version_major}")

endfunction()