# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

enable_testing()

# Find gtest package
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add the executable
add_executable(run_tests main.cpp)

# Link gtest libraries
target_link_libraries(run_tests ${GTEST_LIBRARIES} pthread)

# Add a test
add_test(NAME MyTests COMMAND run_tests)
