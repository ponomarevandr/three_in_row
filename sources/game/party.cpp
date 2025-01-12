#include "party.h"

#include "game/analysis_manager.h"


namespace Game {

Party::Party(size_t height, size_t width) {
	history.emplace_back(height, width);
	turns.push_back(1 << 20);
	AnalysisManager analysis_manager(history.back(), getPlayerTurn(), 500);
	analysis_manager.run();
	estimations.push_back(analysis_manager.getResult());
}

const Position& Party::getPosition() const {
	return history.back();
}

size_t Party::getHeight() const {
	return history.back().getHeight();
}

size_t Party::getWidth() const {
	return history.back().getWidth();
}

bool Party::isTurnPossible(size_t column) const {
	return history.back().isTurnPossible(column);
}

void Party::makeTurn(size_t column) {
	history.push_back(history.back());
	history.back().makeTurn(column, getPlayerTurn());
	turns.push_back(column);
	AnalysisManager analysis_manager(history.back(), getPlayerTurn(), 500);
	analysis_manager.run();
	estimations.push_back(analysis_manager.getResult());
}

uint8_t Party::getPlayerTurn() const {
	return (turns.size() + 2) % 3 + 1;
}

bool Party::isGameEnded() const {
	return history.back().getOutcome() != OUTCOME_UNKNOWN;
}

uint8_t Party::getPlayerWon() const {
	return history.back().getOutcome();
}

const std::vector<size_t>& Party::getTurns() const {
	return turns;
}

const Position& Party::getPositionOfTurn(size_t index) const {
	return history[index];
}

const Estimation& Party::getEstimation() const {
	return estimations.back();
}

const Estimation& Party::getEstimationOfTurn(size_t index) const {
	return estimations[index];
}

void Party::revertToTurn(size_t index) {
	history.resize(index + 1);
	turns.resize(index + 1);
	estimations.resize(index + 1);
}

}