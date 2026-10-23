#include "estimator_naive.h"


namespace Game {

EstimatorNaive::EstimatorNaive(Position position, uint8_t player_turn, uint16_t depth):
	Estimator(position, player_turn, depth) {}

void EstimatorNaive::estimatePosition() {
	result = estimatePositionImpl(position_start, player_turn_start, depth_max);
}

Estimation EstimatorNaive::estimatePositionImpl(const Position& position, uint8_t player_turn,
		uint16_t depth) {
	++nodes_visited;
	if (depth == 0 || position.getOutcome() != OUTCOME_UNKNOWN)
		return Estimation(position);
	Estimation aggregated;
	bool has_started = false;
	for (uint16_t column = 0; column < position.getWidth(); ++column) {
		if (!position.isTurnPossible(column))
			continue;
		Position position_next = position.makeTurnCopy(column, player_turn);
		Estimation estimation =
			estimatePositionImpl(position_next, nextPlayer(player_turn), depth - 1);
		estimation.column_best = column;
		if (has_started) {
			aggregated =
				aggregateForPlayer(std::move(aggregated), std::move(estimation), player_turn);
		} else {
			aggregated = std::move(estimation);
			has_started = true;
		}
	}
	if (aggregated.outcome != OUTCOME_UNKNOWN)
		++aggregated.turns_till_end;
	return aggregated;
}

std::string EstimatorNaive::getDebugName() const {
	return "Naive recursive estimator";
}

}