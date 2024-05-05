include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        2.6.1
)
FetchContent_MakeAvailable(SFML)

set(SOURCES
    main.cpp
    Window.cpp
)

add_executable(plotter ${SOURCES})
target_include_directories(plotter
    PUBLIC ${HEADER_DIR}/GUI
)
target_link_libraries(plotter
    PRIVATE sfml-window sfml-system sfml-graphics
)
