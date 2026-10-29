#pragma once

#include "game/position.h"
#include "game/score.h"


namespace ThreeInRow {

class Estimator {
protected:
	Position position;
	uint8_t player_start = 0;
	size_t depth_max = 0;
	Ratio result;
	size_t turn_best;

public:
	Estimator() = default;
	virtual ~Estimator() = default;
	void setup(Position position, uint8_t player_start, size_t depth_max);
	void run();
	const Ratio& getResult() const;
	size_t getTurnBest() const;

protected:
	virtual Ratio runImpl(uint8_t player, size_t depth) = 0;
};

}