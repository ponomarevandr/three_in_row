#include "estimator_naive.h"


namespace Game {

EstimatorNaive::EstimatorNaive(const Position& position, uint8_t player_turn, size_t depth_max):
	Estimator(position, player_turn, depth_max) {}

Estimation EstimatorNaive::estimatePosition(Position& position, uint8_t player_turn,
		size_t depth) {
	++nodes_visited;
	if (depth == 0 || position.getOutcome() != OUTCOME_UNKNOWN)
		return Estimation(position);
	size_t column = 0;
	Estimation result;
	bool has_started = false;
	while (true) {
		while (!position.isTurnPossible(column) && column < position.getWidth()) {
			++column;
		}
		if (column == position.getWidth())
			break;
		Position position_next = position.makeTurnCopy(column, player_turn);
		Estimation estimation = estimatePosition(position_next, nextPlayer(player_turn), depth - 1);
		if (has_started) {
			result = aggregateForPlayer(std::move(result), std::move(estimation), player_turn);
		} else {
			result = std::move(estimation);
			has_started = true;
		}
		++column;
	}
	if (result.outcome != OUTCOME_UNKNOWN)
		++result.turns_till_end;
	return result;
}

std::string EstimatorNaive::getDebugName() const {
	return "Naive recursive estimator";
}

}