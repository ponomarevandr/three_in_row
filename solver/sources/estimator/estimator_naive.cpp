#include "estimator_naive.h"

#include "game/player_functions.h"


namespace ThreeInRow {

Ratio EstimatorNaive::runImpl(uint8_t player, size_t depth) {
	const Score& score = position.getScore();
	if (depth == 0 || position.isGameEnded()) {
		Ratio ratio = score.createRatio();
		if (position.isGameEnded() && score.getWinner() == Score::NO_WINNER)
			ratio.declareDraw();
		return ratio;
	}
	size_t turn_best = position.getWidth();
	Ratio ratio_best;
	for (size_t i = 0; i < position.getWidth(); ++i) {
		if (!position.makeTurn(player, i))
			continue;
		Ratio ratio_current = runImpl(playerNext(player), depth - 1);
		ratio_current.incTurnsTillEnd();
		if (
			turn_best == position.getWidth() ||
			isRatioBetter(ratio_best, ratio_current, player)
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