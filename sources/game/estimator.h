#pragma once

#include "game/position.h"

#include <array>


namespace Game {

struct Estimation {
	std::array<float, 3> values;
	uint8_t player_winning = 4;
	size_t turns_till_end = 0;
	Estimation() = default;
	explicit Estimation(const Position&);
};

Estimation aggregateForPlayer(Estimation&& first, Estimation&& second, uint8_t player);


class Estimator {
private:
	static constexpr size_t DEPTH_MAX = 5;
	const Position& position_start;
	uint8_t player_turn_start;
	Estimation result;

private:
	Estimation estimatePosition(const Position& position, uint8_t player_turn, size_t depth);

public:
	Estimator(const Position& position, uint8_t player_turn);
	void run();
	const Estimation& getResult() const;
};

}