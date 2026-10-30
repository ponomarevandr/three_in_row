#include "game/position.h"
#include "game/player_functions.h"
#include "game/score.h"
#include "estimator/estimator_naive.h"

#include <cstdlib>
#include <iostream>


using namespace ThreeInRow;

int main() {
	Position position;
	position.initialize(6, 5);
	uint8_t player = 0;
	EstimatorNaive estimator;
	while (true) {
		system("clear");
		position.toStream(std::cout);
		estimator.setup(position, player, 10);
		estimator.run();
		Ratio ratio = estimator.getResult();
		std::cout << ratio.getRatio()[0] << " " << ratio.getRatio()[1] << " " << ratio.getRatio()[2] << "\n";
		std::cout << ratio.getEval()[0] << " " << ratio.getEval()[1] << " " << ratio.getEval()[2] << "\n";
		if (ratio.getWinner() != Ratio::NO_WINNER)
			std::cout << "till end: " << ratio.getTurnsTillEnd() << "\n";
		std::cout << "best: " << estimator.getTurnBest() << "\n";
		std::cout << "xov"[player] << ": ";
		size_t turn;
		std::cin >> turn;
		if (!position.makeTurn(player, turn))
			continue;
		player = playerNext(player);
	}
	return 0;
}