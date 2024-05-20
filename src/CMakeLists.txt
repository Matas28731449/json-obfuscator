cmake_minimum_required(VERSION 1.0) # version can be different

project(json-obfuscator) # name of your project

enable_testing() # to  discover tests in test explorer 

add_subdirectory(googletest) # add googletest subdirectory

include_directories(googletest/include) # this is so we can #include <gtest/gtest.h>

add_executable(tests tests.cpp) # add this executable

target_link_libraries(tests PRIVATE gtest) # link google test to this executable

include(GoogleTest)
gtest_discover_tests(tests) # discovers tests by asking the compiled test executable to enumerate its tests