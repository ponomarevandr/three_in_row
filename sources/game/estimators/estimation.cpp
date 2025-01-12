#include "estimation.h"


namespace Game {

Estimation::Estimation(const Position& position) {
	std::array<size_t, 3> scores = position.getScores();
	float sum = scores[0] + scores[1] + scores[2];
	for (size_t i = 0; i < 3; ++i) {
		values[i] = scores[i] / sum;
	}
	outcome = position.getOutcome();
	if (outcome == OUTCOME_UNKNOWN)
		return;
	if (outcome != OUTCOME_DRAW) {
		values[0] = values[1] = values[2] = 0;
		values[outcome - 1] = 1.0f;
	}
}

Estimation aggregateForPlayer(Estimation&& first, Estimation&& second, uint8_t player) {
	if (first.outcome == player && second.outcome == player) {
		if (first.turns_till_end <= second.turns_till_end) {
			return first;
		} else {
			return second;
		}
	}
	if (first.outcome == player)
		return first;
	if (second.outcome == player)
		return second;
	if (first.outcome != OUTCOME_DRAW && first.outcome != OUTCOME_UNKNOWN &&
			second.outcome != OUTCOME_DRAW && second.outcome != OUTCOME_UNKNOWN) {
		if (first.turns_till_end >= second.turns_till_end) {
			return first;
		} else {
			return second;
		}
	}
	if (first.outcome == OUTCOME_UNKNOWN || second.outcome == OUTCOME_UNKNOWN) {
		first.outcome = second.outcome = OUTCOME_UNKNOWN;
		first.turns_till_end = second.turns_till_end = 0;
	}
	if (first.values[player - 1] >= second.values[player - 1]) {
		return first;
	} else {
		return second;
	}
}

bool Estimation::operator==(const Estimation& other) const {
	return values == other.values && outcome == other.outcome &&
		turns_till_end == other.turns_till_end;
}

bool Estimation::operator!=(const Estimation& other) const {
	return !(*this == other);
}

}