#pragma once

#include "game/position.h"

#include <cstdint>
#include <array>


namespace Game {

struct Estimation {
	std::array<float, 3> values;
	uint8_t outcome = OUTCOME_UNKNOWN;
	uint16_t turns_till_end = 0;
	uint16_t column_best = 0;
	Estimation() = default;
	explicit Estimation(const Position&);
	bool operator==(const Estimation&) const;
	bool operator!=(const Estimation&) const;
};

// При агрегировании состояний по заданному игроку неизбежно остается доля случайности
// для двух других! Максимум не учитывает разницу в значениях побочных игроков.
Estimation aggregateForPlayer(Estimation first, Estimation second, uint8_t player);

}