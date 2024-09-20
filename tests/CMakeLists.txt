project(geistererbennicht_test)
list(APPEND SRC_LIST "${CMAKE_SOURCE_DIR}/src/letterselector.cpp")
include(prjtest)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)
