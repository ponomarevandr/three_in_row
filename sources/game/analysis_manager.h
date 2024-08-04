#pragma once

#include "game/position.h"
#include "game/estimators/estimation.h"

#include <chrono>


namespace Game {

class AnalysisManager {
private:
	using Clock = std::chrono::steady_clock;

private:
	static constexpr bool DEBUG = true;
	const Position& position;
	uint8_t player_turn;
	size_t time_ms_target;
	Estimation result;
	Clock::time_point time_beginning;
	Clock::time_point time_end;
	std::vector<size_t> times_ms_runs;

private:
	size_t getNextTimeMsApproximate() const;
	void debugPrint() const;

public:
	AnalysisManager(const Position& position, uint8_t player_turn, size_t time_ms_target);
	void run();
	const Estimation& getResult() const;
	size_t getTimeMsElapsed() const;
};

}