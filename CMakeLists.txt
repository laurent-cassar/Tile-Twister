cmake_minimum_required(VERSION 3.10)
project(mon_projet LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Sources
file(GLOB_RECURSE SOURCES
    src/*.cpp
)

add_executable(main ${SOURCES})

# SDL2
find_package(SDL2 REQUIRED)

# Includes (PROJET + SDL)
target_include_directories(main PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${SDL2_INCLUDE_DIRS}
    C:/msys64/mingw64/include/SDL2
)

# Libs (ordre important sous Windows)
target_link_libraries(main PRIVATE
    SDL2::SDL2main
    SDL2::SDL2
    SDL2_ttf
)
