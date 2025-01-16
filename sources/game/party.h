#pragma once

#include "game/position.h"
#include "game/estimators/estimation.h"
#include "game/analysis/manager_async.h"

#include <cstdint>
#include <vector>
#include <memory>
#include <thread>


namespace Game {

class Party {
private:
	std::vector<Position> positions;
	std::vector<size_t> turns;
	std::vector<Estimation> estimations;
	size_t estimation_time_ms_target;
	AnalysisManagerAsync analysis_manager;
	std::unique_ptr<std::thread> analysis_thread;
	bool is_analysis_discarded = false;

private:
	static uint8_t getPlayerOfTurn(size_t turn);

public:
	Party(size_t height, size_t width, size_t estimation_time_ms_target);  // время 0 => без оценки
	~Party();
	Party(Party&&) = default;
	Party& operator=(Party&&) = default;
	size_t getHeight() const;
	size_t getWidth() const;
	const Position& getPosition() const;
	bool isTurnPossible(size_t column) const;
	void makeTurn(size_t column);
	uint8_t getPlayerTurn() const;
	uint8_t getOutcome() const;
	const std::vector<Position>& getPositions() const;
	const std::vector<size_t>& getTurns() const;
	const std::vector<Estimation>& getEstimations() const;
	void revertToTurn(size_t index);
	bool processEstimations();
};

}