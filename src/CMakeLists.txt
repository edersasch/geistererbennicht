project(geistererbennicht)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_LIST)
list(APPEND SRC_LIST "${CMAKE_SOURCE_DIR}/data/pics.qrc")

if(WIN32)
    include(DeployQt)
    windeployqt(${PROJECT_NAME})
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE true)
endif()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${SRC_LIST}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
        set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(${PROJECT_NAME}
            ${SRC_LIST}
        )
    endif()
endif()

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(PRIVATEOPTS -Wall -Wextra -Werror -Wshadow)
    if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
        set(PRIVATELINKOPTS LINKER:-s)
    endif()
    #if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    #    set(PRIVATEOPTS ${PRIVATEOPTS} -fsanitize=address)
    #    set(PRIVATELINKOPTS ${PRIVATELINKOPTS} -fsanitize=address)
    #endif()
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(PRIVATEOPTS /W3)
endif()
target_compile_options(${PROJECT_NAME} PRIVATE ${PRIVATEOPTS})
target_link_options(${PROJECT_NAME} PRIVATE ${PRIVATELINKOPTS})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.${PROJECT_NAME})
endif()
#set_target_properties(${PROJECT_NAME} PROPERTIES
#    ${BUNDLE_ID_OPTION}
#    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#    MACOSX_BUNDLE TRUE
#    WIN32_EXECUTABLE TRUE
#)

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()
