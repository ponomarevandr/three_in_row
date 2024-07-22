#include "scene_game.h"

#include "interface/application.h"
#include "interface/items/position_viewer.h"
#include "graphics/geometry.h"

#include <memory>


namespace Interface {

SceneGame::SceneGame(Application* application): Scene(application) {
	auto position_viewer = std::make_unique<PositionViewer>(Graphics::Point(1, 1));
	items.push_back(std::move(position_viewer));
}

}