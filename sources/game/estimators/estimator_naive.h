#pragma once

#include "game/position.h"
#include "game/estimators/estimation.h"
#include "game/estimators/estimator_base.h"


namespace Game {

class EstimatorNaive: public Estimator {
protected:
	Estimation estimatePosition(const Position& position, uint8_t player_turn,
		size_t depth) override;

public:
	EstimatorNaive(const Position& position, uint8_t player_turn, size_t depth_max);
};

}