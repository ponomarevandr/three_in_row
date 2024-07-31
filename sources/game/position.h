#pragma once

#include "graphics/geometry.h"

#include <array>
#include <vector>


namespace Game {

class Position {
private:
	size_t height = 0;
	size_t width = 0;
	size_t free_cells = 0;
	std::vector<uint64_t> field;
	std::array<size_t, 3> scores;

private:
	static const size_t triple_scores[4];
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
	Position(size_t height, size_t width, std::vector<uint64_t>&& field);
	std::vector<uint64_t> takeField();
	size_t getHeight() const;
	size_t getWidth() const;
	uint8_t getCell(size_t row, size_t column) const;
	void setCell(size_t row, size_t column, uint8_t value);
	bool isTurnPossible(size_t column) const;
	void makeTurn(size_t column, uint8_t player);
	void unmakeTurn(size_t column);
	std::array<size_t, 3> getScores() const;
	bool isGameEnded() const;
	uint8_t getPlayerWon() const;
	bool isCellWinning(size_t row, size_t column) const;
};

}