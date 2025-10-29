cmake_minimum_required(VERSION 3.16)
project(cache_lab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(CACHELAB_BUILD_TESTS "Build unit tests" ON)
option(CACHELAB_BUILD_BENCH "Build benchmark runner" ON)

add_library(cachelab
    src/factory.cpp
    src/workload.cpp
    src/policies/lru.cpp
    src/policies/lfu.cpp
    src/policies/lecar.cpp
)
target_include_directories(cachelab PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(CACHELAB_BUILD_BENCH)
  add_executable(bench src/bench_main.cpp)
  target_link_libraries(bench PRIVATE cachelab)
endif()

if(CACHELAB_BUILD_TESTS)
  add_executable(cache_tests tests/cache_tests.cpp)
  target_link_libraries(cache_tests PRIVATE cachelab)
  enable_testing()
  add_test(NAME cache_unit COMMAND cache_tests)
endif()
