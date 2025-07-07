cmake_minimum_required(VERSION 3.16)
project(langfact LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic)

include_directories(include)
file(GLOB_RECURSE SOURCES "src/*.cpp")
list(FILTER SOURCES EXCLUDE REGEX ".*main.cpp") 
add_library(langfact_lib ${SOURCES})
add_executable(langfact src/main.cpp)
target_link_libraries(langfact langfact_lib)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/52eb8108c5bdec04579160ae17225d66034bd723.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()
file(GLOB_RECURSE TEST_SOURCES "tests/*cpp")
add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests langfact_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)
