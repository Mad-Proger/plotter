include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        2.6.1
    FIND_PACKAGE_ARGS COMPONENTS graphics window
)
FetchContent_MakeAvailable(SFML)

set(SOURCES
    Window.cpp
)

add_library(gui STATIC ${SOURCES})
target_include_directories(gui
    PUBLIC ${HEADER_DIR}/GUI
    PUBLIC ${HEADER_DIR}/MarchingSquares
)
target_link_libraries(gui
    PUBLIC sfml-window sfml-system sfml-graphics
)
