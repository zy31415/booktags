cmake_minimum_required(VERSION 3.2)
project(mutithreading_sqlite3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)



find_library(SQLITE3_LIBRARY sqlite3)

find_package(Boost 1.54.0 COMPONENTS thread system REQUIRED)


include_directories(${Boost_INCLUDE_DIRS})
add_executable(mutithreading_sqlite3 ${SOURCE_FILES})
target_link_libraries(mutithreading_sqlite3 ${SQLITE3_LIBRARY} ${Boost_LIBRARIES})
