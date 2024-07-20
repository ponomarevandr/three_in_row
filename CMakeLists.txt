cmake_minimum_required(VERSION 3.0)


project(ThreeInRow)

set(SOURCES
	sources/graphics/geometry.cpp
	sources/graphics/screen.cpp
	sources/graphics/primitives.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/sources)


add_executable(three_in_row ${SOURCES} sources/main.cpp)
target_link_libraries(three_in_row ncursesw)