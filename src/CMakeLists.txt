find_package(SDL2 REQUIRED)

include_directories(
  ${SDL2_INCLUDE_DIRS})

add_executable(
  randogram
    prng.c
    randogram.c
    main.c)

target_link_libraries(
  randogram
    m
    ${SDL2_LIBRARIES}
    SDL2_image)

target_compile_options(
  randogram
  PUBLIC
    -Wall
    -Wextra
    -Wpedantic
    -Werror)
