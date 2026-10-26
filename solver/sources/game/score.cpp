#include "score.h"

#include <algorithm>


namespace ThreeInRow {

Score& Score::operator+=(const Score& other) {
	winner = NO_WINNER;
	for (size_t i = 0; i < 3; ++i) {
		score[i] += other.score[i] - 1;
		if (score[i] > COST[3])
			winner = i;
	}
	return *this;
}

Score& Score::operator-=(const Score& other) {
	winner = NO_WINNER;
	for (size_t i = 0; i < 3; ++i) {
		score[i] -= other.score[i] - 1;
		if (score[i] > COST[3])
			winner = i;
	}
	return *this;
}

Score Score::operator+(const Score& other) const {
	Score result = *this;
	result += other;
	return result;
}

Score Score::operator-(const Score& other) const {
	Score result = *this;
	result -= other;
	return result;
}

Ratio Score::getRatio() const {
	Ratio ratio;
	if (winner != NO_WINNER) {
		ratio.ratio[winner] = 1.0;
		ratio.winner = winner;
		ratio.updateEval();
		return ratio;
	}
	uint32_t sum = score[0] + score[1] + score[2];
	for (size_t i = 0; i < 3; ++i) {
		ratio.ratio[i] = static_cast<float>(score[i]) / sum;
	}
	ratio.updateEval();
	return ratio;
}


void Ratio::updateEval() {
	eval[0] = ratio[0] - std::max(ratio[1], ratio[2]);
	eval[1] = ratio[1] - std::max(ratio[0], ratio[2]);
	eval[2] = ratio[2] - std::max(ratio[0], ratio[1]);
}

}