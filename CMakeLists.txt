cmake_minimum_required(VERSION 3.0)


project(ThreeInRow)

set(SOURCES
	sources/graphics/geometry.cpp
	sources/graphics/screen.cpp
	sources/graphics/primitives.cpp
	sources/debug/output.cpp
	sources/interface/application.cpp
	sources/interface/input.cpp
	sources/interface/scenes/scene_base.cpp
	sources/interface/scenes/scene_main_menu.cpp
	sources/interface/scenes/scene_game.cpp
	sources/interface/scenes/scene_yes_no.cpp
	sources/interface/items/item_base.cpp
	sources/interface/items/button.cpp
	sources/interface/items/position_viewer.cpp
	sources/interface/items/turns_viewer.cpp
	sources/interface/translation.cpp
	sources/game/position.cpp
	sources/game/party.cpp
	sources/game/estimator.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/sources)


add_executable(three_in_row ${SOURCES} sources/main.cpp)
target_link_libraries(three_in_row ncursesw)