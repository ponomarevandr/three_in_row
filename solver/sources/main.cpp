#include "game/position.h"

#include <iostream>


using namespace ThreeInRow;

int main() {
	Position position;
	position.initialize(5, 5);
	uint8_t player = 0;
	while (true) {
		size_t i;
		std::cin >> i;
		if (!position.makeTurn(i, player))
			continue;
		auto score = position.getScore();
		std::cout << score.score[0] << " " << score.score[1] << " " << score.score[2];
		std::cout << "   " << static_cast<int>(score.winner) << "\n";
		player = (player + 1) % 3;
	}
	return 0;
}