# This file is part of CuteVCF.
#
# CuteVCF is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# CuteVCF is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with CuteVCF.  If not, see <http://www.gnu.org/licenses/>.
#
# Copyright 2016 Labsquare <sacha@labsquare.org>

# We require CMake >= 3.0
# Minimal version is needed in order to avoid warnings
cmake_minimum_required(VERSION 3.0)

# Set projectname (must be done AFTER setting configurationtypes)
project(fastQt)
set(VERSION "0.1.0")

# add dependencies
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)


# Libraries & platform specific settings
if(UNIX)
    # In order for find_package to be successful, Qt 5 must be found below the CMAKE_PREFIX_PATH
    # http://doc.qt.io/qt-5/cmake-manual.html
    set(CMAKE_PREFIX_PATH "/media/DATA/Qt5.7.0/5.7/gcc_64/" "/media/DATA/Qt5.7.0/5.7/gcc_64/lib/" "/media/DATA/Qt5.7.0/5.7/gcc_64/lib/cmake/")

    # Set executable name (lower case on GNU/Linux)
    string(TOLOWER "${PROJECT_NAME}" EXECUTABLE_NAME)

else()
    # Set executable name
    set(EXECUTABLE_NAME "${PROJECT_NAME}")
endif()

# Find the QtWidgets library
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Concurrent REQUIRED)
find_package(Qt5Charts REQUIRED)
# Translations
find_package(Qt5LinguistTools REQUIRED)
qt5_add_translation(QM_FILES fastqc_fr.ts)
message(STATUS "Translation files: ${QM_FILES}")

# Compilers FLAGS (c++ 11 & linker options)
if(CMAKE_COMPILER_IS_GNUCXX)
    # For g++/gcc/mingw32 compiler
    # Optimize
    set(CMAKE_CXX_FLAGS "-O3")
    # Strip binary (ps: don't remove comment & note section)
    set(CMAKE_EXE_LINKER_FLAGS "-s")
    # Add flags from dpkg-buildflags
    # https://wiki.debian.org/Hardening
    set(LDFLAGS "-Wl,-z,relro")
    set(CXXFLAGS "-g -O2 -fstack-protector-strong -Wformat -Werror=format-security")
    set(CPPFLAGS "-D_FORTIFY_SOURCE=2")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LDFLAGS} ${CXXFLAGS} ${CPPFLAGS}")

    set(warnings "-Wall -Wextra -Werror")

    # c++11
    MESSAGE(STATUS "Activation of c++11")
    # Other syntax: add_definitions(-std=gnu++0x)
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
    CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
    if(COMPILER_SUPPORTS_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    elseif(COMPILER_SUPPORTS_CXX0X)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
    else()
        message(WARNING "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
    endif()
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # For Visual Studio etc compiler
    # MSVC does not require any special flags for c++11
    set(warnings "/W4 /WX /EHsc")

    # Optimization of linker for static libs
    # Add /LTCG to the command line of the linker
    set(CMAKE_EXE_LINKER_FLAGS "/LTCG" )
    ADD_DEFINITIONS(-D_HAS_ITERATOR_DEBUGGING=0)
endif()

# Executable definition
qt5_add_resources(UI_RESOURCES resources.qrc)
file(GLOB HEADERS_AND_SRCS
    "main.cpp"
    "sequence/*.h"
    "sequence/*.cpp"
    "analysis/*.h"
    "analysis/*.cpp"
    "ui/*.h"
    "ui/*.cpp"
    "model/*.h"
    "model/*.cpp"
    "utils/*.h"
    "utils/*.cpp"
    "QFontIcon/*.h"
    "QFontIcon/*.cpp"
)
add_executable(
    ${EXECUTABLE_NAME} #Target names may not contain slashes. This is not a supported use case.
    ${HEADERS_AND_SRCS}
    ${UI_RESOURCES}
    #${QM_FILES}
)
include_directories( sequence analysis ui model utils QFontIcon)

# Search KF5Archive
# https://api.kde.org/frameworks/karchive/html/classKArchiveDirectory.html
# https://github.com/KDE/extra-cmake-modules/tree/master/find-modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
find_package(KF5 COMPONENTS Archive) # libkf5archive-dev
# Search libz
# https://cmake.org/cmake/help/v3.0/module/FindZLIB.html
find_package(ZLIB REQUIRED) # libz-dev
# karchive deps
#liblzma-dev
#libbz2-dev

if(KF5_FOUND)
    target_link_libraries(
          ${EXECUTABLE_NAME}
          ${ZLIB_LIBRARIES}
          # Use the following modules from Qt 5.
          Qt5::Widgets
          Qt5::Concurrent
          Qt5::Charts
          KF5::Archive
    )
else()
    MESSAGE(WARNING "kf5 library NOT found ! We will download it !")

    find_package(ECM REQUIRED)
    include(ExternalProject)
    # include("${CMAKE_SOURCE_DIR}/extra-cmake-modules/extra-cmake-modules.cmake")
    include("${CMAKE_SOURCE_DIR}/karchive/karchive.cmake")

    include_directories( ${ZLIB_INCLUDE_DIRS} )

    # Use the compiled KF5 library
    target_link_libraries(
        ${EXECUTABLE_NAME}
        ${ZLIB_LIBRARIES}
        # Use the following modules from Qt 5.
        Qt5::Widgets
        Qt5::Concurrent
        Qt5::Charts
        ${karchive_LIB}
    )
    add_dependencies(${EXECUTABLE_NAME} karchive)
endif()

# Build in Release-mode by default if not explicitly set
if( NOT CMAKE_BUILD_TYPE )
  set(CMAKE_BUILD_TYPE "Release")
endif()

# Installation
if(UNIX)
    # Short fix of installation dir...
    # ${CMAKE_INSTALL_PREFIX} : /usr/local/
    set(CMAKE_INSTALL_PREFIX "/usr/")
    INSTALL(TARGETS ${EXECUTABLE_NAME}
            DESTINATION "${CMAKE_INSTALL_PREFIX}bin")

    # Debian package
    # cpack runs
    # it includes CPackConfig.cmake
    # it iterates over the generators listed in that file’s CPACK_GENERATOR list variable
    # (unless told to use just a specific one via -G on the command line...)
    # foreach generator, it then
    #     sets CPACK_GENERATOR to the one currently being iterated
    #     includes the CPACK_PROJECT_CONFIG_FILE
    #     produces the package for that generator
    include(${CMAKE_CURRENT_SOURCE_DIR}/dist_package/CPackConfig.cmake)

endif()

#if(WIN32)
#    INSTALL(TARGETS ${EXECUTABLE_NAME} DESTINATION c:/windows/)
#endif()

include(CPack)

#notes :
#make VERBOSE=1

#CMAKE_EXE_LINKER_FLAGS
#CMAKE_SHARED_LINKER_FLAGS
#CMAKE_MODULE_LINKER_FLAGS
#STATIC_LIBRARY_FLAGS Extra flags to use when linking static libraries