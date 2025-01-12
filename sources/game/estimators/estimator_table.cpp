#include "estimator_table.h"

#include <algorithm>


namespace Game {

void TranspositionTable::clear() {
	data.clear();
}

void TranspositionTable::insert(std::vector<uint64_t>&& field, const Estimation& estimation) {
	auto result = data.insert(std::make_pair(std::move(field), estimation));
	if (!result.second)
		result.first->second = estimation;
}

const Estimation* TranspositionTable::get(const std::vector<uint64_t>& field) const {
	auto iterator = data.find(field);
	if (iterator == data.end())
		return nullptr;
	return &iterator->second;
}


EstimatorTable::EstimatorTable(const Position& position, uint8_t player_turn,
	size_t depth_max): Estimator(position, player_turn, depth_max) {}

Estimation EstimatorTable::estimatePosition(Position& position, uint8_t player_turn,
		size_t depth) {
	table.clear();
	return estimatePositionTable(position, player_turn, depth);
}

Estimation EstimatorTable::estimatePositionTable(Position& position, uint8_t player_turn,
		size_t depth) {
	++nodes_visited;
	if (depth == 0 || position.getOutcome() != OUTCOME_UNKNOWN)
		return Estimation(position);
	const Estimation* estimation_table = table.get(position.getField());
	if (estimation_table)
		return *estimation_table;
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
		Estimation estimation = estimatePositionTable(position_next, player_turn % 3 + 1,
			depth - 1);
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
	table.insert(position.takeField(), result);
	return result;
}

std::string EstimatorTable::getDebugName() const {
	return "Estimator with a transposition table";
}

}