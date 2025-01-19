#pragma once

#include "game/position.h"
#include "game/estimators/estimation.h"
#include "game/estimators/estimator_base.h"

#include <string>


namespace Game {

class EstimatorNaive: public Estimator {
protected:
	void estimatePosition() override;
	std::string getDebugName() const override;
	Estimation estimatePositionImpl(const Position& position, uint8_t player_turn, uint16_t depth);

public:
	EstimatorNaive(Position position, uint8_t player_turn, uint16_t depth);
};

}