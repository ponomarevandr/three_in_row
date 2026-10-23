#pragma once

#include "interface/scenes/scene_base.h"
#include "game/game.h"
#include "game/players/player_user.h"

#include <array>
#include <memory>


namespace Interface {

class SceneGame: public Scene {
protected:
	std::array<Game::PlayerUser*, 3> player_users;
	std::unique_ptr<Game::Game> game;
	size_t turn_explored = 0;
	size_t turn_shown = 0;

public:
	explicit SceneGame(Application*);
	void process() override;
};

}