#pragma once

#include "game/position.h"
#include "game/estimators/estimation.h"


namespace Game {

class Estimator {
protected:
	const Position& position_start;
	uint8_t player_turn_start;
	size_t depth_max;
	Estimation result;

protected:
	virtual Estimation estimatePosition(const Position& position, uint8_t player_turn,
		size_t depth) = 0;

public:
	Estimator(const Position& position, uint8_t player_turn, size_t depth_max);
	void run();
	const Estimation& getResult() const;
};

}