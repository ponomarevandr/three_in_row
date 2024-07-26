#include "scene_game.h"

#include "interface/application.h"
#include "interface/items/button.h"
#include "interface/items/position_viewer.h"
#include "interface/items/turns_viewer.h"
#include "graphics/geometry.h"
#include "graphics/screen.h"

#include <memory>


namespace Interface {

SceneGame::SceneGame(Application* application): Scene(application), party(7, 13) {
	auto position_viewer = std::make_unique<PositionViewer>(Graphics::Point(0, 0), &party,
		&explored_turn);
	items.push_back(std::move(position_viewer));

	auto turns_viewer = std::make_unique<TurnsViewer>(
		Graphics::Point(Graphics::getScreenWidth() - 19, 1), Graphics::getScreenHeight() - 4,
		&party, &explored_turn);
	items.push_back(std::move(turns_viewer));

	auto button_exit = std::make_unique<Button>(
		Graphics::Point(0, Graphics::getScreenHeight() - 2), Graphics::getScreenWidth() - 1, 0);
	button_exit->setText(L"В меню");
	button_exit->setCallback([this]() {
		this->application->popScene();
	});
	items.push_back(std::move(button_exit));
}

}