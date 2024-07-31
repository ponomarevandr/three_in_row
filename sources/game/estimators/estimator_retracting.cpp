#include "estimator_retracting.h"


namespace Game {

EstimatorRetracting::EstimatorRetracting(const Position& position, uint8_t player_turn,
	size_t depth_max): Estimator(position, player_turn, depth_max) {}

Estimation EstimatorRetracting::estimatePosition(Position& position, uint8_t player_turn,
		size_t depth) {
	++nodes_visited;
	if (depth == 0 || position.isGameEnded())
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
		position.makeTurn(column, player_turn);
		Estimation estimation = estimatePosition(position, player_turn % 3 + 1, depth - 1);
		position.unmakeTurn(column);
		if (has_started) {
			result = aggregateForPlayer(std::move(result), std::move(estimation), player_turn);
		} else {
			result = std::move(estimation);
			has_started = true;
		}
		++column;
	}
	if (result.player_winning != 4)
		++result.turns_till_end;
	return result;
}

std::string EstimatorRetracting::getDebugName() const {
	return "Retracting estimator (no position copying)";
}

}