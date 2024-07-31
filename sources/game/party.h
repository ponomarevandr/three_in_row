#pragma once

#include "game/position.h"
#include "game/estimators/estimation.h"

#include <array>
#include <vector>


namespace Game {

class Party {
private:
	static constexpr size_t ESTIMATION_DEPTH = 5;
	std::vector<Position> history;
	std::vector<size_t> turns;
	std::vector<Estimation> estimations;

public:
	Party(size_t height, size_t width);
	const Position& getPosition() const;
	size_t getHeight() const;
	size_t getWidth() const;
	bool isTurnPossible(size_t column) const;
	void makeTurn(size_t column);
	uint8_t getPlayerTurn() const;
	bool isGameEnded() const;
	const std::vector<size_t>& getTurns() const;
	const Position& getPositionOfTurn(size_t index) const;
	const Estimation& getEstimation() const;
	const Estimation& getEstimationOfTurn(size_t index) const;
	void revertToTurn(size_t index);
};

}