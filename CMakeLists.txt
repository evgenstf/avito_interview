cmake_minimum_required(VERSION 2.8.4)
project(frequency_counter)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(frequency_counter "frequency_counter/frequency_counter.cpp")

add_executable(frequency_counter_bin "main.cpp")
target_link_libraries(frequency_counter_bin frequency_counter)
set_target_properties(frequency_counter_bin PROPERTIES OUTPUT_NAME freq)

link_directories(/usr/local/lib)

# Setup testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

if (NOT TARGET tests)
  add_custom_target(tests COMMAND GTEST_COLOR=yes ${CMAKE_CTEST_COMMAND} --verbose)
endif()

file(GLOB TEST_FILES "tests/*.cpp")
add_executable("frequency_counter_tests" EXCLUDE_FROM_ALL ${TEST_FILES})
target_link_libraries("frequency_counter_tests" gtest pthread "frequency_counter")
add_dependencies(tests "frequency_counter_tests")
add_test("frequency_counter_tests" "./frequency_counter_tests")
