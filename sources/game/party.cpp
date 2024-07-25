#include "party.h"


namespace Game {

Party::Party(size_t height, size_t width) {
	history.emplace_back(height, width);
	turns.push_back(1 << 20);
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
	history.back().makeTurn(column, (turns.size() + 2) % 3 + 1);
	turns.push_back(column);
}

uint8_t Party::getTurnPlayer() const {
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

void Party::revertToTurn(size_t index) {
	history.resize(index);
	turns.resize(index);
}

}