cmake_minimum_required(VERSION 3.26)
project(mancalaGame)

set(CMAKE_CXX_STANDARD 17)

add_executable(mancalaGame main.cpp
        MancalaGame.cpp
        MancalaGame.h)
