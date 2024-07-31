#pragma once

#include "game/position.h"

#include <array>


namespace Game {

struct Estimation {
	std::array<float, 3> values;
	uint8_t player_winning = 4;
	size_t turns_till_end = 0;
	Estimation() = default;
	explicit Estimation(const Position&);
};

Estimation aggregateForPlayer(Estimation&& first, Estimation&& second, uint8_t player);

}