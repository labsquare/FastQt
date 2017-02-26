#----------------------------------------------------------------
# Generated CMake target import file for configuration "RELEASE".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "KF5::Archive" for configuration "RELEASE"
set_property(TARGET KF5::Archive APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(KF5::Archive PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/libKF5Archive.dll.a"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/libKF5Archive.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS KF5::Archive )
list(APPEND _IMPORT_CHECK_FILES_FOR_KF5::Archive "${_IMPORT_PREFIX}/lib/libKF5Archive.dll.a" "${_IMPORT_PREFIX}/bin/libKF5Archive.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
