# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_static_frame_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED static_frame_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(static_frame_FOUND FALSE)
  elseif(NOT static_frame_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(static_frame_FOUND FALSE)
  endif()
  return()
endif()
set(_static_frame_CONFIG_INCLUDED TRUE)

# output package information
if(NOT static_frame_FIND_QUIETLY)
  message(STATUS "Found static_frame: 0.0.0 (${static_frame_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'static_frame' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${static_frame_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(static_frame_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${static_frame_DIR}/${_extra}")
endforeach()
