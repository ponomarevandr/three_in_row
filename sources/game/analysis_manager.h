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
	std::vector<size_t> times_ms_pruning;
	std::vector<size_t> times_ms_table;
	bool is_pruning_running;
	bool is_table_running;

private:
	static size_t getNextTimeMsApproximate(const std::vector<size_t>& times_ms);
	void debugPrint() const;

public:
	AnalysisManager(const Position& position, uint8_t player_turn, size_t time_ms_target);
	void run();
	const Estimation& getResult() const;
	size_t getTimeMsElapsed() const;
};

}