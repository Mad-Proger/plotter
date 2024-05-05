set(SOURCES
    Expression.cpp
)

add_library(function ${SOURCES})
target_include_directories(function
    PUBLIC ${HEADER_DIR}/Function
    PUBLIC ${EXTERN_DIR}/expr
)
