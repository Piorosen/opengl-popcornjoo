set(PROGRAM_NAME "nyanya-ai")
PROJECT(${PROGRAM_NAME})
cmake_minimum_required(VERSION 3.16.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(spdlog CONFIG REQUIRED)
find_package(GLUT REQUIRED)

FILE(COPY resources/ DESTINATION "${CMAKE_BINARY_DIR}/resources")
MESSAGE(STATUS "RESOURCE PATH : " ${CMAKE_BINARY_DIR}/resources)

# Add Dependecy Library Directory
ADD_EXECUTABLE(${PROGRAM_NAME}
				main.cpp)

add_subdirectory(Display display/)

# target_link_libraries(${PROGRAM_NAME} display)
target_link_libraries(${libGraphic} GLUT::GLUT)
target_link_libraries(${PROGRAM_NAME} PRIVATE spdlog::spdlog spdlog::spdlog_header_only)
