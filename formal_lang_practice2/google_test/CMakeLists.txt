project(Google_tests)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_library(main_lib STATIC ../Solution.cpp)
add_executable(main_test ../main_test.cpp)
add_executable(second_test ../second_test.cpp)
target_link_libraries(main_test gtest gtest_main main_lib)
target_link_libraries(second_test gtest gtest_main main_lib)
