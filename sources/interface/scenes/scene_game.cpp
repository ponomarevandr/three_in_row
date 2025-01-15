#include "scene_game.h"

#include "interface/application.h"
#include "interface/items/button.h"
#include "interface/items/position_viewer.h"
#include "interface/items/turns_viewer.h"
#include "interface/scenes/scene_yes_no.h"
#include "interface/turn_translation.h"
#include "graphics/geometry.h"
#include "graphics/screen.h"

#include <string>
#include <memory>


namespace Interface {

SceneGame::SceneGame(Application* application): Scene(application), party(7, 7) {
	auto position_viewer = std::make_unique<PositionViewer>(this,
		Graphics::Point(0, 0),
		&party,
		&explored_turn
	);
	items.push_back(std::move(position_viewer));

	auto turns_viewer = std::make_unique<TurnsViewer>(this,
		Graphics::Point(Graphics::getScreenWidth() - 19, 1),
		Graphics::getScreenHeight() - 4,
		&party,
		&explored_turn
	);
	turns_viewer->setCallbackRevert([this]() {
		auto scene_yes_no = std::make_unique<SceneYesNo>(this->application);
		scene_yes_no->setQuestion(
			L"Откатить партию к ходу " + turnToString(this->explored_turn) + L"?"
		);
		scene_yes_no->setCallback(true, [this]() {
			this->party.revertToTurn(explored_turn);
		});
		this->application->pushScene(std::move(scene_yes_no));
	});
	items.push_back(std::move(turns_viewer));

	auto button_exit = std::make_unique<Button>(this,
		Graphics::Point(0, Graphics::getScreenHeight() - 2),
		Graphics::getScreenWidth() - 1
	);
	button_exit->setText(L"В меню");
	button_exit->setCallback([this]() {
		this->application->popScene();
	});
	items.push_back(std::move(button_exit));
}

}