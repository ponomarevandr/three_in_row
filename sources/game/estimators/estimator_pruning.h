#pragma once

#include "game/position.h"
#include "game/estimators/estimation.h"
#include "game/estimators/estimator_base.h"

#include <array>
#include <string>


namespace Game {

class EstimatorPruning: public Estimator {
protected:
	class Comparator {
	private:
		uint8_t player;

	public:
		explicit Comparator(uint8_t player);
		bool operator()(const Position&, const Position&) const;
	};

protected:
	Estimation estimatePosition(Position& position, uint8_t player_turn, size_t depth) override;
	Estimation estimatePositionPruning(Position& position, uint8_t player_turn, size_t depth,
		const std::array<float, 3>& values_of_max);
	std::string getDebugName() const override;

public:
	EstimatorPruning(const Position& position, uint8_t player_turn, size_t depth_max);
};

}