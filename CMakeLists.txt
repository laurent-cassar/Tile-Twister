cmake_minimum_required(VERSION 3.10)
project(2048_Game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Trouver SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} include)

# Sources principales
set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/Grid.cpp
    src/Tile.cpp
    src/GameState.cpp
    src/Window.cpp
    src/Renderer.cpp
    src/GameObject.cpp
    src/TileSprite.cpp
)

# Exécutable principal
add_executable(2048_game ${SOURCES})
target_link_libraries(2048_game ${SDL2_LIBRARIES} SDL2_ttf)

# Tests
enable_testing()

# Sources communes pour les tests (sans main.cpp)
set(TEST_COMMON_SOURCES
    src/Game.cpp
    src/Grid.cpp
    src/Tile.cpp
    src/GameState.cpp
    src/Window.cpp
    src/Renderer.cpp
    src/GameObject.cpp
    src/TileSprite.cpp
)

# Test Grid
add_executable(test_grid tests/test_grid.cpp ${TEST_COMMON_SOURCES})
target_link_libraries(test_grid ${SDL2_LIBRARIES} SDL2_ttf)
add_test(NAME TestGrid COMMAND test_grid)

# Test Game
add_executable(test_game tests/test_game.cpp ${TEST_COMMON_SOURCES})
target_link_libraries(test_game ${SDL2_LIBRARIES} SDL2_ttf)
add_test(NAME TestGame COMMAND test_game)

# Test Movements
add_executable(test_movements tests/test_movements.cpp ${TEST_COMMON_SOURCES})
target_link_libraries(test_movements ${SDL2_LIBRARIES} SDL2_ttf)
add_test(NAME TestMovements COMMAND test_movements)