cmake_minimum_required(VERSION 3.22.1)

project(bank2bmp)

find_package(SDL2 REQUIRED)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
  include/
)

add_executable(${PROJECT_NAME} src/main.cpp src/Tile.cpp src/Bank.cpp)

target_link_libraries(${PROJECT_NAME}
  SDL2::SDL2
)
