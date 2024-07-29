#include "estimator.h"


namespace Game {

Estimation::Estimation(const Position& position) {
	std::array<size_t, 3> scores = position.getScores();
	float sum = scores[0] + scores[1] + scores[2];
	for (size_t i = 0; i < 3; ++i) {
		values[i] = scores[i] / sum;
	}
	if (!position.isGameEnded())
		return;
	if (scores[0] == 1 && scores[1] == 1 && scores[2] == 1) {
		player_winning = 0;
	} else {
		for (size_t i = 0; i < 3; ++i) {
			if (scores[i] != 0)
				player_winning = i + 1;
		}
	}
}

Estimation aggregateForPlayer(Estimation&& first, Estimation&& second, uint8_t player) {
	if (first.player_winning == player && second.player_winning == player) {
		if (first.turns_till_end <= second.turns_till_end) {
			return first;
		} else {
			return second;
		}
	}
	if (first.player_winning == player)
		return first;
	if (second.player_winning == player)
		return second;
	if (first.player_winning != 0 && first.player_winning != 4 &&
			second.player_winning != 0 && second.player_winning != 4) {
		if (first.turns_till_end >= second.turns_till_end) {
			return first;
		} else {
			return second;
		}
	}
	if (first.player_winning == 4 || second.player_winning == 4) {
		first.player_winning = second.player_winning = 4;
		first.turns_till_end = second.turns_till_end = 0;
	}
	if (first.values[player - 1] >= second.values[player - 1]) {
		return first;
	} else {
		return second;
	}
}



Estimator::Estimator(const Position& position, uint8_t player_turn):
	position_start(position), player_turn_start(player_turn) {}

void Estimator::run() {
	result = estimatePosition(position_start, player_turn_start, DEPTH_MAX);
}

const Estimation& Estimator::getResult() const {
	return result;
}

Estimation Estimator::estimatePosition(const Position& position, uint8_t player_turn,
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