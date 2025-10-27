cmake_minimum_required(VERSION 3.20)
project(cachelab CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build unit tests" ON)

add_library(cachelab
    src/metrics.cpp
    src/workload.cpp
    src/factory.cpp
    src/policies/lru.cpp
    src/policies/lfu.cpp
    src/policies/lecar.cpp
)
target_include_directories(cachelab PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(bench bench/bench_main.cpp)
target_link_libraries(bench PRIVATE cachelab)

if(BUILD_TESTS)
  enable_testing()
  add_executable(cachelab_tests tests/cache_tests.cpp)
  target_link_libraries(cachelab_tests PRIVATE cachelab)
  add_test(NAME cachelab_tests COMMAND cachelab_tests)
endif()
