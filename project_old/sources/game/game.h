#pragma once

#include "game/party.h"
#include "game/players/player_base.h"

#include <array>
#include <memory>


namespace Game {

class Game {
private:
	using Players = std::array<std::unique_ptr<Player>, 3>;

private:
	Party party;
	Players players;

public:
	Game(size_t height, size_t width, size_t estimation_time_ms_target, Players&& players);
	bool processEstimations();
	bool processTurn();
	const Party& getParty() const;
};

}