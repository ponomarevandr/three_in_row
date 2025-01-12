#pragma once

#include "graphics/geometry.h"

#include <cstdint>
#include <array>
#include <vector>


namespace Game {

static constexpr uint8_t OUTCOME_DRAW = 0;
static constexpr uint8_t OUTCOME_UNKNOWN = 4;

class Position {
private:
	size_t height = 0;
	size_t width = 0;
	size_t free_cells = 0;
	std::vector<uint64_t> field;
	std::array<size_t, 3> scores;

private:
	static constexpr uint8_t NO_PLAYER = 0;
	static constexpr uint8_t SEVERAL_PLAYERS = 4;
	static constexpr uint8_t INVALID_TRIPLE = 5;

private:
	static const size_t combination_scores[4];
	static const std::vector<Graphics::Vector> triples_center;
	static const std::vector<Graphics::Vector> triples_all;

private:
	size_t getIndexOuter(size_t row, size_t column) const;
	size_t getIndexInner(size_t column) const;
	void getQuantityOfTriple(const Graphics::Point& start,
		const std::vector<Graphics::Vector>& triples, size_t index,
		uint8_t& player,size_t& quantity) const;
	void calculateScores();

public:
	Position() = default;
	Position(size_t height, size_t width);
	std::vector<uint64_t> takeField();
	const std::vector<uint64_t>& getField() const;
	size_t getHeight() const;
	size_t getWidth() const;
	uint8_t getCell(size_t row, size_t column) const;
	void setCell(size_t row, size_t column, uint8_t value);
	bool isTurnPossible(size_t column) const;
	void makeTurn(size_t column, uint8_t player);
	Position makeTurnCopy(size_t column, uint8_t player) const;
	void unmakeTurn(size_t column);
	std::array<size_t, 3> getScores() const;
	uint8_t getOutcome() const;
	bool isCellWinning(size_t row, size_t column) const;
};

}