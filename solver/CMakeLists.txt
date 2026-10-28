cmake_minimum_required(VERSION 3.0)


# ==================== Объявления

project(ThreeInRow)
include(ExternalProject)

set(SOURCES
	sources/game/score.cpp
	sources/game/position.cpp
)

set(TEST_SOURCES
	test/test_array_2d.cpp
	test/test_score.cpp
	test/test_position.cpp
)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Wall)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

include_directories(${PROJECT_SOURCE_DIR}/sources)


# ==================== Внешние репозитории

include(FetchContent)
FetchContent_Declare(
	googletest
	GIT_REPOSITORY	https://github.com/google/googletest
	GIT_TAG			main
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


# ==================== Компиляция

add_executable(three_in_row ${SOURCES} sources/main.cpp)

add_executable(tests ${SOURCES} ${TEST_SOURCES} test/test.cpp)
target_link_libraries(tests gtest gtest_main)