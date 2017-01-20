set(karchive_PREFIX "${CMAKE_BINARY_DIR}/karchive/karchive-prefix")
set(karchive_INSTALL "${CMAKE_BINARY_DIR}/karchive/karchive-install")

if (CMAKE_GENERATOR STREQUAL "Unix Makefiles")
    # when using the makefile generator, use the special variable $(MAKE) to invoke make
    # this enables the jobserver to work correctly
    set(MAKE_COMMAND "$(MAKE)")
else()
    # invoke make explicitly
    # in this case, we assume the parent build system is running in parallel already so no -j flag is added
    find_program(MAKE_COMMAND NAMES make gmake)
endif()

ExternalProject_Add(
    karchive
    #DOWNLOAD_DIR ${EXTERNALS_DOWNLOAD_DIR}
    URL http://download.kde.org/Attic/frameworks/5.24/karchive-5.24.0.zip
    URL_MD5 739843accfe9bd85ab2f1582722cf01e
    INSTALL_DIR ${karchive_INSTALL}
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${karchive_INSTALL}
                -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
                #-DCMAKE_SYSTEM_PREFIX_PATH="/media/DATA/Qt5.7.0/5.7/gcc_64/lib/cmake"
                #-DQT_INSTALL_PREFIX="/media/DATA/Qt5.7.0/5.7/gcc_64/bin"
                -DBUILD_TESTING=false
    #DEPENDS ext_extra_cmake_modules
)

include_directories(${karchive_INSTALL}/include/KF5/KArchive)
set(karchive_LIB "${karchive_INSTALL}/lib/${CMAKE_CXX_LIBRARY_ARCHITECTURE}/libKF5Archive.so")
