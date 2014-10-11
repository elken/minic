project(minic CXX)
cmake_minimum_required(VERSION 2.8.5)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(minic src/main.cpp)
target_link_libraries(minic ${GTKMM_LIBRARIES})
