cmake_minimum_required(VERSION 3.15)
project(TODO)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES
    src/main.cpp
    src/fileCMD.cpp
    src/todoProcess.cpp
)

include_directories(include)

add_executable(TODO ${SOURCES})

