cmake_minimum_required(VERSION 3.27)
project(final)

set(CMAKE_CXX_STANDARD 11)

add_executable(final
        main.cpp
        mainGuy.h
        Textures.cpp
        Textures.h
        Leaderboard.cpp
        Leaderboard.h
        Board.cpp
        Board.h
        Cell.cpp
        Cell.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)
target_link_libraries(final sfml-system sfml-window sfml-graphics sfml-audio)
