#include "party.h"

#include "game/estimators/estimator_naive.h"


namespace Game {

Party::Party(size_t height, size_t width) {
	history.emplace_back(height, width);
	turns.push_back(1 << 20);
	EstimatorNaive estimator(history.back(), getPlayerTurn(), ESTIMATION_DEPTH);
	estimator.run();
	estimations.push_back(estimator.getResult());
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
	size_t player_turn = getPlayerTurn();
	history.push_back(history.back());
	history.back().makeTurn(column, player_turn);
	turns.push_back(column);
	EstimatorNaive estimator(history.back(), getPlayerTurn(), ESTIMATION_DEPTH);
	estimator.run();
	estimations.push_back(estimator.getResult());
}

uint8_t Party::getPlayerTurn() const {
	return (turns.size() + 1 + !history.back().isGameEnded()) % 3 + 1;
}

bool Party::isGameEnded() const {
	return history.back().isGameEnded();
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