project(google_tests)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(regular_test ../regular.cpp ../test_file.cpp)
target_link_libraries(regular_test gtest gtest_main)