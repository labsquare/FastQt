# https://cmake.org/cmake/help/v3.0/module/CPackDeb.html
# https://cmake.org/Wiki/CMake:CPackPackageGenerators#DEB_.28UNIX_only.29
IF(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")
    INCLUDE(InstallRequiredSystemLibraries)

    # Choose it via cpack -G <variable>
    SET(CPACK_GENERATOR "RPM;DEB")
    SET(CPACK_PROJECT_CONFIG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/dist_package/CPackProjectConfig.txt")

    # Informations
    SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
    # https://www.debian.org/doc/debian-policy/ch-binary.html#s-descriptions
    # https://www.debian.org/doc/debian-policy/ch-controlfields.html#s-f-Description
    # under 80 characters. Do not include the package name
    # Lines starting with a single space are part of a paragraph.
    #Description: <single line synopsis>
    # <extended description over several lines>
    # Do not try to continue the single line synopsis
    SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "GUI quality control tool to analysis genomics fastq datas.
 FastQt is the clone of FastQC application written with Qt5.7.
 It allows user to make several analysis of fastq data from several
 compression format and produce quality plots and tables.")
    SET(CPACK_PACKAGE_CONTACT "Labsquare <sacha@labsquare.org>")

    # Platform specific config
    IF(WIN32 AND NOT UNIX)
        # TODO
        MESSAGE(FATAL_ERROR "Cannot configure CPack to generate packages on non-linux systems.")

    ELSE(WIN32 AND NOT UNIX)

        # Desktop file
        # Creation
        # https://specifications.freedesktop.org/desktop-entry-spec/latest/
        # Entries def:
        # https://specifications.freedesktop.org/desktop-entry-spec/desktop-entry-spec-0.9.8.html
        # Categories:
        # https://specifications.freedesktop.org/menu-spec/latest/apa.html
        file(WRITE "${CMAKE_BINARY_DIR}/${EXECUTABLE_NAME}.desktop"
"[Desktop Entry]
Encoding=UTF-8
Type=Application
Name=${PROJECT_NAME}
GenericName=GUI quality control tool to analysis genomics fastq datas.
Comment=FastQt is the clone of FastQC application ported from Java to C++/Qt5.
TryExec=${EXECUTABLE_NAME}
Exec=${EXECUTABLE_NAME} %F
Terminal=false
Icon=${EXECUTABLE_NAME}
Categories=Education;Science;")
        # Move Desktop file
        install(FILES "${CMAKE_BINARY_DIR}/${EXECUTABLE_NAME}.desktop"
                DESTINATION "share/applications/"
                PERMISSIONS
                OWNER_WRITE OWNER_READ
                GROUP_READ
                WORLD_READ)
        # Move icon
        configure_file("${CMAKE_CURRENT_SOURCE_DIR}/fastqt.png"
                       "${CMAKE_BINARY_DIR}/${EXECUTABLE_NAME}.png")
        install(FILES "${CMAKE_BINARY_DIR}/${EXECUTABLE_NAME}.png"
                DESTINATION "share/pixmaps/"
                PERMISSIONS
                OWNER_WRITE OWNER_READ
                GROUP_READ
                WORLD_READ)


        # License file
        # https://www.debian.org/doc/debian-policy/ch-docs.html#s-copyrightfile
        # Packages should refer to the corresponding files under /usr/share/common-licenses,
        # rather than quoting them in the copyright file.
        file(WRITE "${CMAKE_BINARY_DIR}/copyright"
"Copyright (C) 2016 ${CPACK_PACKAGE_CONTACT}

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

On Debian systems, the complete text of the GNU Lesser General Public
License can be found in `/usr/share/common-licenses/LGPL-3'.")
        install(FILES "${CMAKE_BINARY_DIR}/copyright"
                DESTINATION "share/doc/${EXECUTABLE_NAME}/"
                PERMISSIONS
                OWNER_WRITE OWNER_READ
                GROUP_READ
                WORLD_READ)

        # Architecture
        # https://www.debian.org/doc/debian-policy/ch-controlfields.html#s-f-Architecture
        # Depending on context and the control file used, the Architecture field can include the following sets of values:
        #
        #     - A unique single word identifying a Debian machine architecture as described in Architecture
        #     specification strings, Section 11.1.
        #
        #     - An architecture wildcard identifying a set of Debian machine architectures,
        #     see Architecture wildcards, Section 11.1.1. any matches all Debian machine architectures
        #     and is the most frequently used.
        #
        #     - all, which indicates an architecture-independent package.
        #
        #     - source, which indicates a source package.
        SET(CPACK_DEBIAN_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR}) # Give x86_64, but in control: amd64 != In Package name: x86_64
        SET(CPACK_DEBIAN_PACKAGE_NAME "${EXECUTABLE_NAME}")
        # CPACK_PACKAGE_FILE_NAME: package_version-revision_arch.deb
        # Distro specific => Move to CPACK_PROJECT_CONFIG_FILE
        # SET(CPACK_PACKAGE_FILE_NAME "${CPACK_DEBIAN_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}_amd64")
        SET(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_DEBIAN_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}_source")

        # Misc
        SET(CPACK_DEBIAN_PACKAGE_SECTION "devel") # default
        SET(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
        SET(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/labsquare/fastQt")
        SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Ysard <sacha@labsquare.org>")

        # Version
        # https://wiki.debian.org/DebianMentorsFaq#What_is_the_difference_between_a_native_Debian_package_and_a_non-native_package.3F
        # - Non native: 0.1.1-1: -1 revision number for Debian
        # - Native: 0.1.1
        SET(DEBIAN_PACKAGE_NON_NATIVE_REVISION "1")
        # SET(CPACK_PACKAGE_VERSION_MAJOR "${MAJOR_VERSION}")
        # SET(CPACK_PACKAGE_VERSION_MINOR "${MINOR_VERSION}")
        # SET(CPACK_PACKAGE_VERSION_PATCH "${PATCH_VERSION}")
        SET(CPACK_PACKAGE_VERSION "${VERSION}-${DEBIAN_PACKAGE_NON_NATIVE_REVISION}")

        # Dependencies
        SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libqt5widgets5 (>=5.7.0), libqt5concurrent5 (>=5.7.0), libqt5gui5 (>=5.7.0), libqt5core5a (>=5.7.0), libc6 (>= 2.19), libgcc1 (>= 1:4.9.2), libgl1-mesa-glx (>= 10.3.2), libglib2.0-0 (>= 2.42.1), libpcre3 (>= 2:8.35), libstdc++6 (>= 4.9.2), libx11-6 (>= 2:1.6.2), libxau6 (>= 1:1.0.8), libxcb1 (>= 1.10), libxdmcp6 (>= 1:1.1.1), libxext6 (>= 2:1.3.3), zlib1g (>= 1:1.2.8), libbz2-1.0 (>=1.0.6), liblzma5 (>=5.2.2), libexpat1 (>=2.2.0), libxcb-dri3-0 (>=1.12), libdrm2 (>=2.4.74), libgcc-6-dev (>=6.2.1), libglapi-mesa (>=13.0.2), libkf5archive5 (>=5.27.0), libx11-xcb1 (>=2:1.6.4), libxcb-dri2-0 (>=1.12), libxcb-glx0 (>=1.12), libxcb-present0 (>=1.12), libxcb-sync1 (>=1.12), libxdamage1 (>=1:1.1.4), libxfixes3 (>=1:5.0.3), libxshmfence1 (>=1.2), libxxf86vm1 (>=1:1.1.4), libicu57 (>=57.1)")
        # May be set to ON in order to use dpkg-shlibdeps to generate better package dependency list.
        # You may need set CMAKE_INSTALL_RPATH toi appropriate value if you use this feature,
        # because if you don’t dpkg-shlibdeps may fail to find your own shared libs.
        # https://cmake.org/Wiki/CMake_RPATH_handling
        # https://www.debian.org/doc/debian-policy/ch-sharedlibs.html#s-dpkg-shlibdeps
        #SET(CPACK_DEBIAN_PACKAGE_SHLIBDEPS "ON")

        # Build dependencies
        SET(DEBIAN_PACKAGE_BUILDS_DEPENDS "mesa-common-dev, libz-dev, liblzma-dev, libbz2-dev, libkf5archive-dev")

        # Changelogs
        # This includes modifications made in the Debian package compared to the upstream one as well as other changes and updates to the package. !!
        # https://wiki.debian.org/DebianMentorsFaq#What_is_the_difference_between_a_native_Debian_package_and_a_non-native_package.3F
        # https://www.debian.org/doc/debian-policy/ch-docs.html#s-changelogs
        # - native: debian specific (apt, dpkg, etc.) => /usr/share/doc/pkg/changelog.gz
        # - non native: debian non specific devel => /usr/share/doc/pkg/changelog.Debian.gz.

        # ITP Bug: https://www.debian.org/doc/manuals/developers-reference/ch05.html#newpackage
        # For official package: Please include a Closes: #nnnnn entry in the changelog of the new
        # package in order for the bug report to be automatically closed once the new package is installed in the archive

        # Structure (please respect spaces):
        # https://www.debian.org/doc/debian-policy/ch-source.html#s-dpkgchangelog
        # fact be any series of lines starting with at least two spaces,
        # but conventionally each change starts with an asterisk and a separating
        # space and continuation lines
        #
        # package (version) distribution(s); urgency=urgency
        #     [optional blank line(s), stripped]
        #   * change details
        #     more change details
        #     [blank line(s), included in output of dpkg-parsechangelog]
        #   * even more change details
        #     [optional blank line(s), stripped]
        #  -- maintainer name <email address>[two spaces]  date
        #
        # params
        # - package and version are the source package name and version number.
        # - distribution(s) lists the distributions where this version should be installed when it is uploaded - it is copied
        # to the Distribution field in the .changes file.
        # https://www.debian.org/doc/debian-policy/ch-controlfields.html#s-f-Distribution
        # Ex: unstable, experimental
        # - urgency is the value for the Urgency field in the .changes file for the upload
        # single keyword taking one of the values low, medium, high, emergency, or critical
        # - The date has the following format[19] (compatible and with the same semantics of RFC 2822 and RFC 5322):
        # day-of-week, dd month yyyy hh:mm:ss +zzzz
        # where:
        #     day-of week is one of: Mon, Tue, Wed, Thu, Fri, Sat, Sun
        #
        #     dd is a one- or two-digit day of the month (01-31)
        #
        #     month is one of: Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
        #
        #     yyyy is the four-digit year (e.g. 2010)
        #
        #     hh is the two-digit hour (00-23)
        #
        #     mm is the two-digit minutes (00-59)
        #
        #     ss is the two-digit seconds (00-60)
        #
        #     +zzzz or -zzzz is the the time zone offset from Coordinated Universal Time (UTC).
        #     "+" indicates that the time is ahead of (i.e., east of) UTC and
        #     "-" indicates that the time is behind (i.e., west of) UTC.
        #     The first two digits indicate the hour difference from UTC
        #     and the last two digits indicate the number of additional minutes difference from UTC.
        #     The last two digits must be in the range 00-59.
        #
        # Generate required change log files
        # Native
        # https://code.cor-lab.org/svn/cca/trunk/cca/cpack/CPackDebianConfig.cmake
        # execute_process(COMMAND gzip -9 -c ${CMAKE_CURRENT_SOURCE_DIR}/CHANGELOG
        #                 WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        #                 OUTPUT_FILE "${CMAKE_BINARY_DIR}/changelog.gz")
        # Non native
        # Process file & move it
        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dist_package/CHANGELOG_DEB.in
                       ${CMAKE_CURRENT_BINARY_DIR}/changelog.Debian)
        execute_process(COMMAND gzip -9 -c ${CMAKE_CURRENT_BINARY_DIR}/changelog.Debian
                        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
                        OUTPUT_FILE "${CMAKE_BINARY_DIR}/changelog.Debian.gz")
        install(FILES "${CMAKE_BINARY_DIR}/changelog.Debian.gz"
                    #"${CMAKE_BINARY_DIR}/changelog.gz"
                    DESTINATION "share/doc/${CPACK_DEBIAN_PACKAGE_NAME}")

        # Fedora
        # https://cmake.org/cmake/help/v3.0/module/CPackRPM.html

        # Package naming
        # name-version-release.architecture.rpm
        # kernel-smp-2.6.32.9-3.x86_64.rpm
        # TODO: For a specific platform (ex: Fedora 23) the name must be like
        # "kernel-smp-2.6.32.9-3.fc23.x86_64.rpm" (equiv of {dist} macro: update it !)
        # Distro specific => Move to CPACK_PROJECT_CONFIG_FILE
        # SET(CPACK_PACKAGE_FILE_NAME  "${CPACK_DEBIAN_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}.${CMAKE_SYSTEM_PROCESSOR}")
        SET(CPACK_RPM_PACKAGE_ARCHITECTURE "${CMAKE_SYSTEM_PROCESSOR}")
        SET(CPACK_RPM_PACKAGE_VERSION "${VERSION}")
        SET(CPACK_RPM_PACKAGE_RELEASE "1%{?dist}")
        SET(CPACK_RPM_PACKAGE_SUMMARY "GUI quality control tool to analysis genomics fastq datas")
        SET(CPACK_RPM_PACKAGE_DESCRIPTION "FastQt is the clone of FastQC application written with Qt5.7.
It allows user to make several analysis of fastq data from several
compression format and produce quality plots and tables.")
        SET(CPACK_RPM_PACKAGE_NAME "${EXECUTABLE_NAME}")
        SET(CPACK_RPM_PACKAGE_GROUP "Science")
        SET(CPACK_RPM_PACKAGE_LICENSE "GPLv3")
        SET(CPACK_RPM_PACKAGE_URL ${CPACK_DEBIAN_PACKAGE_HOMEPAGE})
        SET(CPACK_RPM_PACKAGE_REQUIRES "bzip2-libs >= 1.0.6, bzip2-libs >= 1.0.6, expat >= 2.2.0, glib2 >= 2.50.1, glibc >= 2.24, kf5-karchive >= 5.27.0, libX11 >= 1.6.4, libXau >= 1.0.8, libXdamage >= 1.1.4, libXext >= 1.3.3, libXfixes >= 5.0.3, libXxf86vm >= 1.1.4, libdrm >= 2.4.71, libgcc >= 6.2.1, libselinux >= 2.5, libstdc++ >= 6.2.1, libxcb >= 1.12, libxshmfence >= 1.2, mesa-libGL >= 12.0.3, mesa-libglapi >= 12.0.3, pcre >= 8.39, qt5-qtbase >= 5.7.1, qt5-qtbase-gui >= 5.7.1, qt5-qtcharts >= 5.7.1, xz-libs >= 5.2.2, zlib >= 1.2.8")
        SET(CPACK_RPM_PACKAGE_RELOCATABLE "false")
        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dist_package/CHANGELOG_RPM.in
                        ${CMAKE_CURRENT_BINARY_DIR}/changelog)
        SET(CPACK_RPM_CHANGELOG_FILE "${CMAKE_CURRENT_BINARY_DIR}/changelog")
        # Avoid this error "executable-marked-as-config-file /usr/bin/${EXECUTABLE_NAME}"
        # Config flag is automatically set in ${EXECUTABLE_NAME}.spec %files section...
        # %config "/usr/bin/${EXECUTABLE_NAME}"
        # used to explicitly specify %(<directive>) file line in the spec file.
        SET(CPACK_RPM_USER_FILELIST "/usr/bin/${EXECUTABLE_NAME}")

    ENDIF(WIN32 AND NOT UNIX)

    # Lists each of the executables and associated text label to be used to create Start Menu shortcuts.
    # For example, setting this to the list ccmake;CMake will create a shortcut named “CMake”
    # Not all CPack generators use it (at least NSIS, WIX and OSXX11 do).
    SET(CPACK_PACKAGE_EXECUTABLES ${EXECUTABLE_NAME};${PROJECT_NAME})

ENDIF(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")

