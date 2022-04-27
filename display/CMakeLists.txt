cmake_minimum_required(VERSION 3.16.0)
set(libDisplay "display")

find_package(GLUT REQUIRED)

add_library(${libDisplay} STATIC lib/display/display.cpp )

target_include_directories(${libDisplay} PUBLIC include)
target_link_libraries(${libDisplay} PRIVATE GLUT::GLUT)