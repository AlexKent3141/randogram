project(randogram)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(randogram main.cpp)
target_link_libraries(randogram ${SDL2_LIBRARIES})
