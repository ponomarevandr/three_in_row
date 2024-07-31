#include "estimator_base.h"


namespace Game {

Estimator::Estimator(const Position& position, uint8_t player_turn, size_t depth_max):
	position_start(position), player_turn_start(player_turn), depth_max(depth_max) {}

void Estimator::run() {
	result = estimatePosition(position_start, player_turn_start, depth_max);
}

const Estimation& Estimator::getResult() const {
	return result;
}

}