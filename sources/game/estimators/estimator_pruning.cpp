#include "estimator_pruning.h"

#include <algorithm>


namespace Game {

EstimatorPruning::EstimatorPruning(const Position& position, uint8_t player_turn,
	size_t depth_max): Estimator(position, player_turn, depth_max) {}

Estimation EstimatorPruning::estimatePosition(Position& position, uint8_t player_turn,
		size_t depth) {
	std::array<float, 3> values_of_max = { 0, 0, 0 };
	return estimatePositionPruning(position, player_turn, depth, values_of_max);
}

EstimatorPruning::Comparator::Comparator(uint8_t player): player(player) {}

std::vector<Position> EstimatorPruning::getPositionsNext(const Position& position,
		uint8_t player_turn) const {
	size_t column = 0;
	std::vector<Position> positions_next;
	while (true) {
		while (!position.isTurnPossible(column) && column < position.getWidth()) {
			++column;
		}
		if (column == position.getWidth())
			break;
		positions_next.push_back(position);
		positions_next.back().makeTurn(column, player_turn);
		++column;
	}
	return positions_next;
}

bool EstimatorPruning::Comparator::operator()(const Position& first,
		const Position& second) const {
	return Estimation(first).values[player - 1] > Estimation(second).values[player - 1];
}

Estimation EstimatorPruning::estimatePositionPruning(const Position& position, uint8_t player_turn,
		size_t depth, const std::array<float, 3>& values_of_max) {
	++nodes_visited;
	if (depth == 0 || position.isGameEnded())
		return Estimation(position);
	std::vector<Position> positions_next = getPositionsNext(position, player_turn);
	std::sort(positions_next.begin(), positions_next.end(), Comparator(player_turn));
	Estimation result;
	bool has_started = false;
	std::array<float, 3> values_of_max_copy = values_of_max;
	for (Position& position_next : positions_next) {
		Estimation estimation = estimatePositionPruning(position_next, player_turn % 3 + 1,
			depth - 1, values_of_max_copy);
		values_of_max_copy[player_turn - 1] = std::max(values_of_max_copy[player_turn - 1],
			estimation.values[player_turn - 1]);
		if (has_started) {
			result = aggregateForPlayer(std::move(result), std::move(estimation), player_turn);
		} else {
			result = std::move(estimation);
			has_started = true;
		}
		if (values_of_max[player_turn % 3] + result.values[player_turn - 1] > 1.0)
			break;
		if (values_of_max[(player_turn + 1) % 3] + result.values[player_turn - 1] > 1.0)
			break;
	}
	if (result.player_winning != 4)
		++result.turns_till_end;
	return result;
}

std::string EstimatorPruning::getDebugName() const {
	return "Estimator with triple alpha-beta pruning";
}

}