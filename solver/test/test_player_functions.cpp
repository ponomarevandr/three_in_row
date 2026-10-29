#include "game/player_functions.h"
#include "game/position.h"

#include <gtest/gtest.h>

#include <sstream>
#include <string>


using namespace ThreeInRow;


TEST(PlayerFunctions, PlayerNext) {
	ASSERT_EQ(playerNext(0), 1);
	ASSERT_EQ(playerNext(1), 2);
	ASSERT_EQ(playerNext(2), 0);
}

TEST(PlayerFunctions, WhoseTurn) {
	std::stringstream in(
		"5 x 5\n"
		".....\n"
		"..x..\n"
		"..v..\n"
		"..ox.\n"
		".vxo.\n"
	);
	Position position;
	position.fromStream(in);
	ASSERT_EQ(whoseTurn(position), 1);
	position.makeTurn(1, 0);
	ASSERT_EQ(whoseTurn(position), 2);
	position.makeTurn(2, 1);
	ASSERT_EQ(whoseTurn(position), 0);
}