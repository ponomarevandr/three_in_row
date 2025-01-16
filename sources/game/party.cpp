#include "party.h"

#include "game/analysis/manager.h"

#include "debug/output.h"


namespace Game {

Party::Party(size_t height, size_t width, size_t estimation_time_ms_target):
		estimation_time_ms_target(estimation_time_ms_target) {
	positions.emplace_back(height, width);
	if (estimation_time_ms_target > 0) {
		analysis_thread = std::make_unique<std::thread>([this]() {
			this->analysis_manager.run();
		});
	}
}

Party::~Party() {
	if (!analysis_thread)
		return;
	analysis_manager.waitReady();
	analysis_manager.terminate();
	analysis_thread->join();
}

size_t Party::getHeight() const {
	return positions.back().getHeight();
}

size_t Party::getWidth() const {
	return positions.back().getWidth();
}

const Position& Party::getPosition() const {
	return positions.back();
}

bool Party::isTurnPossible(size_t column) const {
	return positions.back().isTurnPossible(column);
}

void Party::makeTurn(size_t column) {
	uint8_t player = getPlayerTurn();
	positions.push_back(positions.back().makeTurnCopy(column, player));
	turns.push_back(column);
}

uint8_t Party::getPlayerOfTurn(size_t turn) {
	return turn % 3 + 1;
}

uint8_t Party::getPlayerTurn() const {
	return getPlayerOfTurn(positions.size() - 1);
}

uint8_t Party::getOutcome() const {
	return positions.back().getOutcome();
}

const std::vector<Position>& Party::getPositions() const {
	return positions;
}

const std::vector<size_t>& Party::getTurns() const {
	return turns;
}

const std::vector<Estimation>& Party::getEstimations() const {
	return estimations;
}

void Party::revertToTurn(size_t index) {
	positions.resize(index + 1);
	turns.resize(index);
	if (index + 1 < estimations.size())
		estimations.resize(index + 1);
	is_analysis_discarded = true;
}

bool Party::processEstimations() {
	if (
		estimation_time_ms_target == 0 ||
		!analysis_manager.isReady() ||
		estimations.size() == positions.size()
	) {
		return false;
	}
	bool is_updated = false;
	if (analysis_manager.isResultPending()) {
		if (is_analysis_discarded) {
			analysis_manager.getResult();
		} else {
			estimations.push_back(analysis_manager.getResult());
			is_updated = true;
		}
	}
	is_analysis_discarded = false;
	if (estimations.size() < positions.size()) {
		analysis_manager.setup(
			positions[estimations.size()],
			getPlayerOfTurn(estimations.size()),
			estimation_time_ms_target
		);
		analysis_manager.nextAction();
	}
	return is_updated;
}

}