#pragma once

#include "game/position.h"

#include <cstdint>
#include <array>


namespace Game {

struct Estimation {
	std::array<float, 3> values;
	uint8_t outcome = OUTCOME_UNKNOWN;
	size_t turns_till_end = 0;
	Estimation() = default;
	explicit Estimation(const Position&);
	bool operator==(const Estimation&) const;
	bool operator!=(const Estimation&) const;
};

Estimation aggregateForPlayer(Estimation first, Estimation second, uint8_t player);

}