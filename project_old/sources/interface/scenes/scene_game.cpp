#include "scene_game.h"

#include "interface/application.h"
#include "interface/items/button.h"
#include "interface/items/position_viewer.h"
#include "interface/items/estimation_viewer.h"
#include "interface/items/turns_viewer.h"
#include "interface/scenes/scene_yes_no.h"
#include "interface/turn_translation.h"
#include "graphics/geometry.h"
#include "graphics/screen.h"
#include "game/players/player_base.h"
#include "game/party.h"

#include <string>


namespace Interface {

SceneGame::SceneGame(Application* application): Scene(application) {
	std::array<std::unique_ptr<Game::Player>, 3> players = {
		std::make_unique<Game::PlayerUser>(),
		std::make_unique<Game::PlayerUser>(),
		std::make_unique<Game::PlayerUser>()
	};
	for (size_t i = 0; i < 3; ++i) {
		player_users[i] = static_cast<Game::PlayerUser*>(players[i].get());
	}
	game = std::make_unique<Game::Game>(7, 7, 5000, std::move(players));
	const Game::Party& party = game->getParty();

	auto position_viewer = std::make_unique<PositionViewer>(this,
		Graphics::Point(1, 1),
		&party,
		&turn_explored,
		&turn_shown
	);
	position_viewer->setCallbackMakeTurn([this](size_t turn_column) {
		this->player_users[this->game->getParty().getPlayerTurn() - 1]->setTurnColumn(turn_column);
	});
	items.push_back(std::move(position_viewer));

	auto estimation_viewer = std::make_unique<EstimationViewer>(this,
		Graphics::Point(2, party.getHeight() + 6),
		&party,
		&turn_shown
	);
	items.push_back(std::move(estimation_viewer));

	auto turns_viewer = std::make_unique<TurnsViewer>(this,
		Graphics::Point(Graphics::getScreenWidth() - 19, 1),
		Graphics::getScreenHeight() - 4,
		&party,
		&turn_explored
	);
	turns_viewer->setCallbackRevert([this]() {
		auto scene_yes_no = std::make_unique<SceneYesNo>(this->application);
		scene_yes_no->setQuestion(
			L"Откатить партию к ходу " + turnToString(this->turn_explored) + L"?"
		);
		//scene_yes_no->setCallback(true, [this]() {
		//	this->game->getParty().revertToTurn(turn_explored);
		//});
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

void SceneGame::process() {
	if (game->processEstimations())
		application->redrawNeeded();
	if (game->processTurn()) {
		turn_explored = game->getParty().getColumns().size();
		application->redrawNeeded();
	}
	Scene::process();
}

}