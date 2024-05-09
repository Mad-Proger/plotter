set(SOURCES
    PlotParameters.cpp
)

add_library(marching-squares STATIC ${SOURCES})
target_include_directories(marching-squares
    PUBLIC ${HEADER_DIR}/MarchingSquares
)
