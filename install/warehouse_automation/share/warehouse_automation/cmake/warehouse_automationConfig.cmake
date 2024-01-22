# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_warehouse_automation_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED warehouse_automation_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(warehouse_automation_FOUND FALSE)
  elseif(NOT warehouse_automation_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(warehouse_automation_FOUND FALSE)
  endif()
  return()
endif()
set(_warehouse_automation_CONFIG_INCLUDED TRUE)

# output package information
if(NOT warehouse_automation_FIND_QUIETLY)
  message(STATUS "Found warehouse_automation: 0.0.0 (${warehouse_automation_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'warehouse_automation' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${warehouse_automation_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(warehouse_automation_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "ament_cmake_export_dependencies-extras.cmake")
foreach(_extra ${_extras})
  include("${warehouse_automation_DIR}/${_extra}")
endforeach()
