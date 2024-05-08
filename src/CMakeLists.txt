add_subdirectory(Function)
add_subdirectory(GUI)
add_subdirectory(MarchingSquares)

add_executable(plotter main.cpp)
target_include_directories(plotter
    PRIVATE ${HEADER_DIR}/GUI
)
target_link_libraries(plotter
    PRIVATE gui
)
