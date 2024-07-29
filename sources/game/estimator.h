#pragma once

#include "game/position.h"

#include <array>


namespace Game {

struct Estimation {
	std::array<float, 3> values;
	uint8_t player_winning = 0;
	bool is_draw = false;
	Estimation() = default;
	explicit Estimation(const Position&);
};


class Estimator {
private:
	const Position& position_start;
	Estimation result;

public:
	explicit Estimator(const Position&);
	void run();
	const Estimation& getResult() const;
};

}