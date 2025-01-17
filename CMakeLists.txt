cmake_minimum_required(VERSION 3.0)


project(ThreeInRow)

set(SOURCES
	sources/graphics/geometry.cpp
	sources/graphics/screen.cpp
	sources/graphics/primitives.cpp
	sources/graphics/players.cpp
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
	sources/interface/items/estimation_viewer.cpp
	sources/interface/items/turns_viewer.cpp
	sources/interface/turn_translation.cpp
	sources/game/position.cpp
	sources/game/party.cpp
	sources/game/estimators/estimation.cpp
	sources/game/estimators/estimator_base.cpp
	sources/game/estimators/estimator_naive.cpp
	sources/game/estimators/estimator_retracting.cpp
	sources/game/estimators/estimator_pruning.cpp
	sources/game/estimators/estimator_table.cpp
	sources/game/analysis/manager.cpp
	sources/game/analysis/manager_async.cpp
	sources/game/game.cpp
	sources/game/players/player_base.cpp
	sources/game/players/player_user.cpp
	sources/thread/worker.cpp
)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Wall)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/sources)


add_executable(three_in_row ${SOURCES} sources/main.cpp)
target_link_libraries(three_in_row ncursesw)