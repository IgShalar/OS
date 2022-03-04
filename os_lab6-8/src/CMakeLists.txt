cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 14)

add_executable(main main.cpp)
add_executable(calc calc.cpp)
target_link_libraries(main zmq)
target_link_libraries(calc zmq)