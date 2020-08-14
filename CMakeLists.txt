cmake_minimum_required(VERSION 3.10)
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.12 CACHE STRING "Build for 10.12")

# Use C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS false)

project(saobxf VERSION 0.9.0.0 LANGUAGES CXX)
message( STATUS "Compiler Version is ${CMAKE_CXX_COMPILER_VERSION}" )

add_executable( saobxf )
target_sources( saobxf PRIVATE
  src/main.cpp
  )
target_include_directories( saobxf PRIVATE  src )
