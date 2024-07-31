#include "estimator_naive.h"


namespace Game {

EstimatorNaive::EstimatorNaive(const Position& position, uint8_t player_turn, size_t depth_max):
	Estimator(position, player_turn, depth_max) {}

Estimation EstimatorNaive::estimatePosition(const Position& position, uint8_t player_turn,
		size_t depth) {
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
		Position position_next = position;
		position_next.makeTurn(column, player_turn);
		Estimation current = estimatePosition(position_next, player_turn % 3 + 1, depth - 1);
		if (has_started) {
			result = aggregateForPlayer(std::move(result), std::move(current), player_turn);
		} else {
			result = std::move(current);
			has_started = true;
		}
		++column;
	}
	if (result.player_winning != 4)
		++result.turns_till_end;
	return result;
}

}