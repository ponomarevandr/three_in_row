#pragma once

#include "game/position.h"
#include "game/estimators/estimation.h"

#include <string>
#include <chrono>


namespace Game {

class Estimator {
protected:
	using Clock = std::chrono::steady_clock;

protected:
	static constexpr bool DEBUG = true;
	const Position& position_start;
	uint8_t player_turn_start;
	size_t depth_max;
	Estimation result;
	size_t nodes_visited;
	Clock::time_point time_beginning;
	Clock::time_point time_end;

protected:
	virtual Estimation estimatePosition(Position& position, uint8_t player_turn, size_t depth) = 0;
	virtual std::string getDebugName() const;
	virtual void debugPrint() const;

public:
	Estimator(const Position& position, uint8_t player_turn, size_t depth_max);
	void run();
	const Estimation& getResult() const;
};

}