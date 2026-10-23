#pragma once

#include "game/position.h"
#include "game/estimators/estimation.h"
#include "game/estimators/estimator_base.h"

#include <string>
#include <map>


namespace Game {

class TranspositionTable {
private:
	std::map<std::vector<uint64_t>, Estimation> data;

public:
	TranspositionTable() = default;
	void clear();
	void insert(std::vector<uint64_t>&& field, const Estimation& estimation);
	const Estimation* get(const std::vector<uint64_t>& field) const;
};


class EstimatorTable: public Estimator {
protected:
	TranspositionTable table;

protected:
	Estimation estimatePosition(Position& position, uint8_t player_turn, size_t depth) override;
	Estimation estimatePositionTable(Position& position, uint8_t player_turn, size_t depth);
	std::string getDebugName() const override;

public:
	EstimatorTable(const Position& position, uint8_t player_turn, size_t depth_max);
};

}