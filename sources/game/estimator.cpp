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
		is_draw = true;
	} else {
		for (size_t i = 0; i < 3; ++i) {
			if (scores[i] != 0)
				player_winning = i + 1;
		}
	}
}


Estimator::Estimator(const Position& position): position_start(position) {}

void Estimator::run() {
	result = Estimation(position_start);
}

const Estimation& Estimator::getResult() const {
	return result;
}

}