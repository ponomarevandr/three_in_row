#pragma once

#include "interface/scenes/scene_base.h"
#include "game/party.h"


namespace Interface {

class SceneGame: public Scene {
protected:
	Game::Party party;

public:
	explicit SceneGame(Application*);
};

}