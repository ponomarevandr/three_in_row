#pragma once

#include "game/position.h"
#include "game/estimators/estimation.h"

#include <cstdint>
#include <string>
#include <chrono>


namespace Game {

class Estimator {
protected:
	using Clock = std::chrono::steady_clock;

protected:
	static constexpr bool DEBUG = false;

protected:
	Position position_start;
	uint8_t player_turn_start;
	uint16_t depth_max;
	Estimation result;
	size_t nodes_visited;
	Clock::time_point time_beginning;
	Clock::time_point time_end;

protected:
	virtual void estimatePosition() = 0;
	virtual std::string getDebugName() const;
	virtual void debugPrint() const;

public:
	Estimator(Position position, uint8_t player_turn, uint16_t depth);
	virtual ~Estimator() = default;
	void run();
	const Estimation& getResult() const;
	size_t getTimeMsElapsed() const;
};

}