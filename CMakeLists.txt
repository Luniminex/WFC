cmake_minimum_required(VERSION 3.26)
project(WaveFunctionCollapse)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g -lSDL2_ttf -lSDL2_image")
find_package(SDL2 REQUIRED SDL2)

add_executable(WaveFunctionCollapse main.cpp
        TextureWrap.cpp
        TextureWrap.h
        Game.cpp
        Game.h
        Handle.cpp
        Handle.h
        FileHandler.cpp
        FileHandler.h
        WFC.cpp
        WFC.h
        Tile.cpp
        Tile.h
        TileManager.cpp
        TileManager.h
        TileGrid.cpp
        TileGrid.h)

target_link_libraries(WaveFunctionCollapse PRIVATE SDL2)