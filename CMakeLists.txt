cmake_minimum_required(VERSION 3.10)
project(StudentSurvivalGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(StudentSurvivalGame
    main.cpp
    student.cpp
    game.cpp
    events.cpp
)