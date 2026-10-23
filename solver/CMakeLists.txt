cmake_minimum_required(VERSION 3.0)


project(ThreeInRow)

set(SOURCES
	#
)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Wall)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

include_directories(${PROJECT_SOURCE_DIR}/sources)

add_executable(three_in_row ${SOURCES} sources/main.cpp)