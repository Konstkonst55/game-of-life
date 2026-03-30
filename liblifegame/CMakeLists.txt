project(liblifegame)

file(GLOB SOURCE_FILE src/*.cpp)
add_library(liblifegame ${SOURCE_FILE})

target_include_directories(liblifegame
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PRIVATE ${PROJECT_SOURCE_DIR}/src
)