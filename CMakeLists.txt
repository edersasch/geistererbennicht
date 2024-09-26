cmake_minimum_required(VERSION 3.16)
project(geistererbennicht VERSION 0.1.0 LANGUAGES CXX)
set(PROJECT_RELEASE_YEAR    2024)
set(PROJECT_RELEASE_MONTH   99)
set(PROJECT_RELEASE_DAY     99)

option(GEISTERERBENNICHT_BUILD_TESTS                    "Build unit tests, downloads google test"                   ON)

configure_file (
    "${CMAKE_SOURCE_DIR}/src/version.hpp.in"
    "${CMAKE_BINARY_DIR}/include/version.hpp"
    )

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include(GNUInstallDirs)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

find_program(PANDOC pandoc)
if(PANDOC)
    configure_file (
        "${CMAKE_SOURCE_DIR}/docs/manuals/footer.md.in"
        "${CMAKE_BINARY_DIR}/docs/manuals/footer.md"
        )
    # see https://cmake.org/pipermail/cmake/2011-June/044651.html
    # and https://stackoverflow.com/questions/38293535/generic-rule-from-makefile-to-cmake
    file(GLOB MANUALS_MD ${CMAKE_SOURCE_DIR}/docs/manuals/*.md)
    set(MANUALS_HTML)
    foreach(f IN LISTS MANUALS_MD)
        if(NOT IS_ABSOLUTE "${f}")
            set(f "${CMAKE_CURRENT_SOURCE_DIR}/${f}")
        endif()
        get_filename_component(fn "${f}" NAME_WE)
        set(o "${CMAKE_CURRENT_BINARY_DIR}/${fn}.html")
        add_custom_command(OUTPUT "${o}"
            COMMAND ${PANDOC} -o "${o}" -s --embed-resources "${f}" ${CMAKE_BINARY_DIR}/docs/manuals/footer.md
            DEPENDS "${f}"
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/docs/manuals
            COMMENT "Generating ${o}"
            VERBATIM
            )
        list(APPEND MANUALS_HTML "${o}")
        install(FILES "${o}" DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/doc/${PROJECT_NAME})
    endforeach()
    add_custom_target(manuals ALL
        DEPENDS "${MANUALS_HTML}"
        COMMENT "Generated HTML manuals with pandoc"
        VERBATIM
        )
endif()

include_directories(src)
include_directories(${PROJECT_BINARY_DIR}/include)

add_subdirectory(src)

if(GEISTERERBENNICHT_BUILD_TESTS)
    include(CTest)
    include(AddGoogleTest)
    add_subdirectory(tests)
endif()

install (FILES ${CMAKE_SOURCE_DIR}/LICENSE DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/doc/${PROJECT_NAME} RENAME License.txt)
FILE(DOWNLOAD https://raw.githubusercontent.com/qt/qt5/5.15.2/LICENSE.LGPLv3 ${CMAKE_BINARY_DIR}/docs/License_Qt.txt
    EXPECTED_HASH SHA256=5ceb37d1c7c1d92878b82af3c0fd5558087f3d5a08a3a4d43850bad4ad265a52
    )
install (FILES ${CMAKE_BINARY_DIR}/docs/License_Qt.txt DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/doc/${PROJECT_NAME})
