#pragma once

#include "interface/scenes/scene_base.h"
#include "game/party.h"


namespace Interface {

class SceneGame: public Scene {
protected:
	Game::Party party;
	size_t turn_explored = 0;
	size_t turn_shown = 0;

public:
	explicit SceneGame(Application*);
	void process() override;
};

}