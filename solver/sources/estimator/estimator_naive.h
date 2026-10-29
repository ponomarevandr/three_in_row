#pragma once

#include "estimator/estimator.h"
#include "game/score.h"


namespace ThreeInRow {

class EstimatorNaive: public Estimator {
protected:
	Ratio runImpl(uint8_t player, size_t depth) override;
};

}