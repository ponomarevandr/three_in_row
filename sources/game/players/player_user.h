#pragma once

#include "game/players/player_base.h"


namespace Game {

class PlayerUser: public Player {
public:
	PlayerUser() = default;
	void setTurnColumn(size_t turn_column);
};

}