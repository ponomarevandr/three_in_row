#include "game/position.h"
#include "game/score.h"

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <array>


using namespace ThreeInRow;


/*
.....
.x...
.oo..
.xvv.
*/
TEST(Position, Turns) {
	Position position;
	position.initialize(5, 4);
	position.makeTurn(0, 1);
	position.makeTurn(1, 1);
	position.makeTurn(2, 2);
	position.makeTurn(0, 1);
	position.makeTurn(1, 2);
	position.makeTurn(2, 3);
	Score score = position.getScore();
	ASSERT_EQ(score.getScore(), (std::array<uint32_t, 3>({
		1 + 3 * Score::COST[1],
		1 + 5 * Score::COST[1] + 2 * Score::COST[2],
		1 + 2 * Score::COST[1] + 1 * Score::COST[2]
	})));
	position.makeTurn(0, 1);
	ASSERT_FALSE(position.makeTurn(1, 1));
	ASSERT_FALSE(position.makeTurn(2, 1));
	position.retractTurn();
	score = position.getScore();
	ASSERT_EQ(score.getScore(), (std::array<uint32_t, 3>({
		1 + 3 * Score::COST[1],
		1 + 5 * Score::COST[1] + 2 * Score::COST[2],
		1 + 2 * Score::COST[1] + 1 * Score::COST[2]
	})));
	position.makeTurn(1, 3);
	score = position.getScore();
	ASSERT_EQ(score.getWinner(), 1);
}

/*
"......"
"..ox.."
"..xv.."
"xoov.v"
*/
TEST(Position, Stream) {
	std::stringstream in(
		"6 x 4\n"
		"\n"
		"..ox..\n"
		"..xv.\n"
		"xoov.v\n"
	);
	Position position;
	position.fromStream(in);
	Score score = position.getScore();
	ASSERT_EQ(score.getScore(), (std::array<uint32_t, 3>({
		1 + 5 * Score::COST[1] + 1 * Score::COST[2],
		1 + 4 * Score::COST[1],
		1 + 4 * Score::COST[1] + 1 * Score::COST[2]
	})));
	position.makeTurn(0, 5);
	std::stringstream out;
	position.toStream(out);
	ASSERT_EQ(out.str(), std::string(
		"6 x 4\n"
		"......\n"
		"..ox..\n"
		"..xv.x\n"
		"xoov.v\n"
	));
}

/*
".v."
".o."
".x."
*/
TEST(Position, RetractOnTop) {
	Position position;
	position.initialize(3, 3);
	position.makeTurn(0, 1);
	position.makeTurn(1, 1);
	position.makeTurn(2, 1);
	ASSERT_FALSE(position.makeTurn(0, 1));
	position.retractTurn();
	std::stringstream out;
	position.toStream(out);
	ASSERT_EQ(out.str(), std::string(
		"3 x 3\n"
		"...\n"
		".o.\n"
		".x.\n"
	));
}