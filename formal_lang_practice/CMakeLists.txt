cmake_minimum_required(VERSION 3.8)
project(formalprac)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        regular.h
        )

add_subdirectory(google_test)
enable_testing()