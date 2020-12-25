cmake_minimum_required(VERSION 3.8)
project(formalprac)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(google_test)
add_executable(main main.cpp)
target_link_libraries(main main_lib)

enable_testing()
