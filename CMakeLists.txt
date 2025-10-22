cmake_minimum_required(VERSION 3.10) 
project(Couchbot CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(CouchControl test.cpp)

include(FetchContent)

FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG f732014
)
FetchContent_MakeAvailable(yaml-cpp)

target_link_libraries(CouchControl PUBLIC yaml-cpp::yaml-cpp) # The library or executable that require yaml-cpp library
