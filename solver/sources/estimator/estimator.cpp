#include "estimator.h"


namespace ThreeInRow {

void Estimator::setup(Position position, uint8_t player_start, size_t depth_max) {
	this->position = std::move(position);
	this->player_start = player_start;
	this->depth_max = depth_max;
}

void Estimator::run() {
	turn_best = position.getWidth();
	result = runImpl(player_start, depth_max);
}

const Ratio& Estimator::getResult() const {
	return result;
}

size_t Estimator::getTurnBest() const {
	return turn_best;
}

}