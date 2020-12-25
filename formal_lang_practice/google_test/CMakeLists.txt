project(google_tests)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_library(main_lib STATIC ../regular.cpp)
add_executable(test_file ../test_file.cpp)
target_link_libraries(test_file gtest gtest_main main_lib)
