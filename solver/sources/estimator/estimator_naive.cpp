#include "estimator_naive.h"

#include "game/player_functions.h"


namespace ThreeInRow {

Ratio EstimatorNaive::runImpl(uint8_t player, size_t depth) {
	const Score& score = position.getScore();
	if (depth == 0 || score.getWinner() != Score::NO_WINNER)
		return score.createRatio();
	size_t turn_best = position.getWidth();
	Ratio ratio_best = score.createRatio();
	for (size_t i = 0; i < position.getWidth(); ++i) {
		if (!position.makeTurn(player, i))
			continue;
		Ratio ratio_current = runImpl(playerNext(player), depth - 1);
		if (
			turn_best == position.getWidth() ||
			ratio_current.getEval()[player] > ratio_best.getEval()[player]
		) {
			turn_best = i;
			ratio_best = ratio_current;
		}
		position.retractTurn();
	}
	if (depth == depth_max)
		this->turn_best = turn_best;
	return ratio_best;
}

}