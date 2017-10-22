cmake_minimum_required (VERSION 2.6)
project (Network)

set(CMAKE_CXX_FLAGS " -W -Wall -pedantic -std=c++11")

enable_testing()
add_subdirectory(gtest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


add_executable (Network ../src/Neuron.cpp ../src/Network.cpp ../src/test_buffer.cpp)
add_executable(unittest ../src/Neuron.cpp ../src/Network.cpp ../src/unittest.cpp)

target_link_libraries(unittest gtest gtest_main)
add_test(unittest unittest)
