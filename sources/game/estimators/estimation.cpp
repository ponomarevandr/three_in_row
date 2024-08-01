#include "estimation.h"


namespace Game {

Estimation::Estimation(const Position& position) {
	std::array<size_t, 3> scores = position.getScores();
	float sum = scores[0] + scores[1] + scores[2];
	for (size_t i = 0; i < 3; ++i) {
		values[i] = scores[i] / sum;
	}
	if (!position.isGameEnded())
		return;
	player_winning = position.getPlayerWon();
	if (player_winning != 0) {
		values[0] = values[1] = values[2] = 0;
		values[player_winning - 1] = 1.0f;
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

}