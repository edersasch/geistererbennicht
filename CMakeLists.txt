cmake_minimum_required(VERSION 3.16)
project(geistererbennicht VERSION 0.1 LANGUAGES CXX)

option(GEISTERERBENNICHT_BUILD_TESTS                    "Build unit tests, downloads google test"                   ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include(GNUInstallDirs)

include_directories(src)

add_subdirectory(src)

if(GEISTERERBENNICHT_BUILD_TESTS)
    include(CTest)
    include(AddGoogleTest)
    add_subdirectory(tests)
endif()
