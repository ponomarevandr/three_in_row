#include "game/score.h"

#include <gtest/gtest.h>

#include <array>


using namespace ThreeInRow;


TEST(Score, Addition) {
	Score first;
	first.addForPlayer(0, 1);
	first.addForPlayer(0, 2);
	first.addForPlayer(2, 2);
	Score second;
	second.addForPlayer(0, 2);
	second.addForPlayer(1, 1);
	Score result = first + second;
	ASSERT_EQ(result.getScore(), (std::array<uint32_t, 3>({
		1 + Score::COST[1] + Score::COST[2] + Score::COST[2],
		1 + Score::COST[1],
		1 + Score::COST[2]
	})));
	uint8_t no_winner_copy = Score::NO_WINNER;
	ASSERT_EQ(result.getWinner(), no_winner_copy);
}

TEST(Score, Subtraction) {
	Score first;
	first.addForPlayer(0, 1);
	first.addForPlayer(0, 2);
	first.addForPlayer(0, 3);
	first.addForPlayer(1, 2);
	first.addForPlayer(2, 1);
	ASSERT_EQ(first.getWinner(), 0);
	Score second;
	second.addForPlayer(0, 2);
	second.addForPlayer(0, 3);
	second.addForPlayer(2, 1);
	Score result = first - second;
	ASSERT_EQ(result.getScore(), (std::array<uint32_t, 3>({
		1 + Score::COST[1],
		1 + Score::COST[2],
		1
	})));
}

TEST(Score, Ratio) {
	Score score;
	score.addForPlayer(0, 1);
	score.addForPlayer(0, 2);
	score.addForPlayer(0, 2);
	score.addForPlayer(1, 2);
	score.addForPlayer(2, 1);
	Ratio ratio = score.createRatio();
	uint32_t sum = 3 + 2 * Score::COST[1] + 3 * Score::COST[2];
	float first = (1.0 + Score::COST[1] + 2 * Score::COST[2]) / sum;
	float second = (1.0 + Score::COST[2]) / sum;
	float third = (1.0 + Score::COST[1]) / sum;
	ASSERT_EQ(ratio.getRatio(), (std::array<float, 3>({ first, second, third })));
	uint8_t no_winner_copy = Score::NO_WINNER;
	ASSERT_EQ(ratio.getWinner(), no_winner_copy);
	ASSERT_EQ(ratio.getEval(), (std::array<float, 3>({
		first - second,
		second - first,
		third - first
	})));
}